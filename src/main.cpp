#include <iostream>
#include <game.h>
#include <event_system.h>

#ifndef NDEBUG
#include <debug_system.h>
#endif

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

using namespace rhythm_typer::core;
using namespace rhythm_typer::event;

void HandleQuit(EventSystem& system, SDL_Event evt) {
	std::cout << "Quitting... Timestamp: " << std::endl;
	system.CancelEvent();
	RTGame::GetInstance().Stop();
}

int main(int argc, char* argv[])
{
	RTGame& game = RTGame::GetInstance();

	EventSystem& event_system = game.AddSystem<EventSystem>();
#ifndef NDEBUG
	rhythm_typer::debug::DebugSystem& debug_system = game.AddSystem<rhythm_typer::debug::DebugSystem>();
#endif // !NDEBUG

	if (!game.Initialize()) {
		std::cout << "Could not initialize game.";
		return -1;
	}

	event_system.RegisterHandler(SDL_QUIT, HandleQuit, true);

	game.Start();
	return 0;
}