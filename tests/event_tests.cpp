#include <functional>
#include <SDL.h>
#include <core/game.h>
#include <event/event_handler.h>
#include <event/event_system.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

using namespace rhythm_typer::core;
using namespace rhythm_typer::event;

bool quit = false;
bool event_handled = false;
bool deconstructor_called = false;
int read_data = -1;
int handle_count = 0;

class TestRunListener : public Catch::EventListenerBase {
	using Catch::EventListenerBase::EventListenerBase;

	void testRunStarting(const Catch::TestRunInfo& test_info) override {
		SDL_Init(SDL_INIT_EVENTS);
	}

	void sectionStarting(const Catch::SectionInfo& section_info) override {
		quit = false;
		event_handled = false;
		deconstructor_called = false;
		read_data = -1;
		handle_count = 0;
	}

	void testRunEnded(const Catch::TestRunStats& test_info) override {
		SDL_Quit();
	}
};

class TestEvent {
public:
	TestEvent(int data) : data_{ data }
	{}

	int GetData() { return data_; }

	~TestEvent() {
		deconstructor_called = true;
	}
private:
	int data_;
};

void HandleQuit(EventInfo& event_info, SDL_Event event) {
	INFO("Quit handler called.");
	quit = true;
}

void HandleTestEvent(EventInfo& event_info, SDL_Event event) {
	event_handled = true;
	handle_count++;
	read_data = static_cast<TestEvent*>(event.user.data1)->GetData();
	event_info.SetCancelled(true);
}

CATCH_REGISTER_LISTENER(TestRunListener);

TEST_CASE("Event Handler ID tests", "[event_system]") {
	const EventHandlerId id1{ 1, 2 };
	const EventHandlerId id2{ 1, 2 };

	SECTION("Two event handler keys with identical ids have same hashes") {
		REQUIRE(std::hash<EventHandlerId>{}(id1) == std::hash<EventHandlerId>{}(id2));
	}
}

TEST_CASE("Event System tests", "[event_system]") {
	EventSystem system{};

	REQUIRE(system.ForceInitialize());
	system.ForceStart();

	SECTION("SDL Events are handled correctly.") {
		system.RegisterHandler(SDL_QUIT, HandleQuit, false);

		SDL_Event event{};
		SDL_zero(event);
		event.type = SDL_QUIT;
		event.quit.type = SDL_QUIT;
		event.quit.timestamp = SDL_GetTicks();
		REQUIRE(SDL_PushEvent(&event));

		system.ForceUpdate(0);
		REQUIRE(quit);
	}

	SECTION("Custom events are handled correctly.") {
		system.RegisterHandler<TestEvent>(HandleTestEvent, false);

		system.PushCustomEvent(TestEvent{ 1 });
		system.ForceUpdate(0);

		REQUIRE(event_handled);
		REQUIRE(read_data == 1);
		REQUIRE(deconstructor_called);
	}

	SECTION("Custom event handlers can be removed.") {
		EventHandlerId event_handler_id = system.RegisterHandler<TestEvent>(HandleTestEvent, false);

		system.PushCustomEvent(TestEvent{ 1 });
		system.ForceUpdate(0);
		system.PushCustomEvent(TestEvent{ 1 });
		system.ForceUpdate(0);

		system.RemoveHandler(event_handler_id);
		system.PushCustomEvent(TestEvent{ 1 });
		system.ForceUpdate(0);

		REQUIRE(handle_count == 2);
	}

	SECTION("Once argument works.") {
		system.RegisterHandler<TestEvent>(HandleTestEvent, true);

		system.PushCustomEvent(TestEvent{ 1 });
		system.ForceUpdate(0);
		system.PushCustomEvent(TestEvent{ 1 });
		system.ForceUpdate(0);

		REQUIRE(handle_count == 1);
	}
}