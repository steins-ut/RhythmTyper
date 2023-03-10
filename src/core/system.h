#ifndef _RTSYSTEM_H_
#define _RTSYSTEM_H_

#include <cstdint>

namespace rhythm_typer {
	namespace core {
		//Base class for game systems.
		class ISystem {
		public:
			//Will be called when the game is initialized, or immediately
			//after being added if the loop has already started.
			//It is not advised to have much functionality in this function
			//if the system is to be added later.
			virtual bool Initialize();

			//Will be called only once when the game loop starts, or
			//immediately after being added if the loop has already started.
			virtual void Start() = 0;

			//Will be called every frame in the game loop.
			//Argument delta_time is in nanoseconds.
			virtual void Update(uint64_t delta_time) = 0;

			virtual ~ISystem() = 0;
		};
	}
}

#endif