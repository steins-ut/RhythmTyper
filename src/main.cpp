#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <utility>
#include <vector>
#include <cassert>


struct Point {
    int x;
    int y;
    Point(int x, int y) { this->x = x; this->y = y; }
};


struct RectSize {
    int w;
    int h;
    RectSize(int w, int h) { this->w = w; this->h = h; }
};


class Letter {
private:
    std::string letter{};
    SDL_Renderer* renderer{};
    TTF_Font* font{};
    SDL_Color color{};
    SDL_Rect rect{};
    SDL_Texture* texture{};

public:
    Letter(SDL_Renderer* renderer, std::string letter, SDL_Color color, TTF_Font* font) : renderer(renderer), letter(std::move(letter)), color(color), font(font) {
        updateTexture();
    }
    ~Letter() {
        // Free the letter texture
        SDL_DestroyTexture(texture);
    }

    void render() {
        // Render the letter texture
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }

    void setPosition(int x, int y) {
        // Set the position of the letter
        rect.x = x;
        rect.y = y;
    }

    [[nodiscard]] RectSize getSize() const {
        // Get the size of the letter
        return {rect.w, rect.h};
    }

    [[nodiscard]] std::string getLetter() const {
        // Get the letter as a string
        return letter;
    }

    void setColor(SDL_Color newColor) {
        // Set the color of the letter
        this->color = newColor;
        // We need to update the texture to reflect the new color
        updateTexture();
    }

    void updateTexture() {
        // Update the texture of the letter
        SDL_Surface* surface = TTF_RenderUTF8_Solid(font, letter.c_str(), color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        // Update the rect size
        // Surface automatically sets the letter size
        rect = {rect.x, rect.y, surface->w, surface->h};
        // Free the surface
        SDL_FreeSurface(surface);
    }
};


class Word {
    // A word is a collection of letters
private:
    std::vector<Letter*> letters{};
    SDL_Renderer* renderer{};
    TTF_Font* defaultFont{};
    SDL_Color defaultColor{};
    int x{};
    int y{};
    int letterSpacing{};
    int currentLetterIndex = 0;

public:
    Word(const std::string & word, SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, int x, int y, int letterSpacing) : defaultFont(font), defaultColor(color), x(x), y(y), letterSpacing(letterSpacing) {
        for (char letter : word) {
            letters.push_back(new Letter(renderer, &letter, defaultColor, defaultFont));
        }
        fixLetterPositions();
    }

    ~Word() {
        letters.clear();
    }

    void render() {
        for (Letter* letter : letters) {
            letter->render();
        }
    }

    void fixLetterPositions() {
        // Normally all the letters are rendered starting on the same pixel, so we need to fix their positions
        int currentX = x;
        for (Letter* letter : letters) {
            letter->setPosition(currentX, y);
            currentX += letter->getSize().w + letterSpacing;
        }
    }

    Letter* getCurrentLetter() {
        if (currentLetterIndex >= letters.size()) return nullptr;
        return letters[currentLetterIndex];
    }

    void nextLetter() {
        currentLetterIndex++;
    }

    void move(int newX, int newY) {
        this->x = newX;
        this->y = newY;
        for(Letter* letter : letters) {
            letter->setPosition(newX, newY);
        }
    }

    [[nodiscard]] Point getPosition() const{
        return {x, y};
    }

};


class Map {
    // Map is a collection of words
private:
    std::vector<Word*> words;
    int currentWordIndex;

public:
    Map() {
        currentWordIndex = 0;
    }

    ~Map() {
        for (Word* word : words) {
            delete word;
        }
    }

    void addWord(Word* word) {
        words.push_back(word);
    }

    Word* getCurrentWord() {
        if (currentWordIndex >= words.size()) return nullptr;
        return words[currentWordIndex];
    }

    void nextWord() {
        currentWordIndex++;
    }

};


int main(int argc, char* argv[]) { // NOLINT(cert-err58-cpp)
    int WINDOW_WIDTH = 640;
    int WINDOW_HEIGHT = 480;

    // Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
    // SDL_INIT_EVERYTHING does not contain SDL_TTF
    TTF_Init();

    // Create a window
    SDL_Window* window = SDL_CreateWindow("RhythmTyper",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    // Create a renderer, not giving any flags defaults to SDL_RENDERER_ACCELERATED, it's better to be explicit.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load a font
    TTF_Font* font = TTF_OpenFont("../res/fonts/Ubuntu-Bold.ttf", 24);
    // If the font is not found, exit the program
    assert(font != nullptr);

    // Default text color
    SDL_Color white = {255, 255, 255, 255};

    // Create a map
    Map map;
    // Adding words to the map
    map.addWord(new Word("Undertale", renderer, font, white, 100, 100, 0));
    map.addWord(new Word("Sans", renderer, font, white, 100, 100, 0));
    map.addWord(new Word("Megalovania", renderer, font, white, 100, 100, 0));
    map.addWord(new Word("Crack", renderer, font, white, 100, 100, 0));
    map.addWord(new Word("Bruh", renderer, font, white, 100, 100, 0));

    SDL_Keysym key;

    // Main loop
    bool isRunning = true;
    while (isRunning) {
        key = SDL_Keysym{};

        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;

                case SDL_KEYDOWN: // If *ANY* key press was recorded
                    key = event.key.keysym;
                    break;

                default:
                    break;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the word
        map.getCurrentWord()->render();

        // Update the screen
        SDL_RenderPresent(renderer);

        // Check if the key pressed corresponds to the current letter that needs to be pressed
        // We need to expand on this to allow multiple letters that need to be pressed at the same time.
        if(key.sym == tolower(map.getCurrentWord()->getCurrentLetter()->getLetter()[0])) {
            // Change the color of the letter to red
            map.getCurrentWord()->getCurrentLetter()->setColor({255, 0, 0, 255});

            // Increment the current letter index
            map.getCurrentWord()->nextLetter();

            // If the current letter is null, go to the next word
            if (map.getCurrentWord()->getCurrentLetter() == nullptr) {
                map.nextWord();
            }
            // If the current word is null, stop the game since map is finished
            if(map.getCurrentWord() == nullptr) {
                isRunning = false;
            }
        }
    }
    // Quit the program
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
	return 0;
}