#include <iostream>
#include <core/game.h>
#include <event/event_handler.h>
#include <event/event_system.h>
#include <graphic/render_system.h>

#ifndef NDEBUG
#include <debug/debug_system.h>
#endif

#ifdef WIN32
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

using namespace rhythm_typer::core;
using namespace rhythm_typer::event;
using namespace rhythm_typer::graphic;

void HandleQuit(EventInfo& event_info, SDL_Event event) {
	std::cout << "Quitting..." << std::endl;
	event_info.SetCancelled(true);
	RTGame::GetInstance().Stop();
}

int main(int argc, char* argv[]) {
	RTGame& game = RTGame::GetInstance();

	EventSystem& event_system = game.AddSystem<EventSystem>();
#ifndef NDEBUG
	rhythm_typer::debug::DebugSystem& debug_system = game.AddSystem<rhythm_typer::debug::DebugSystem>();
#endif // !NDEBUG
	RenderSystem& render_system = game.AddSystem<RenderSystem>();

	if (!game.Initialize()) {
		std::cout << "Could not initialize game.";
		return -1;
	}

	event_system.RegisterHandler(SDL_QUIT, HandleQuit, true);

	game.Start();
	return 0;
}