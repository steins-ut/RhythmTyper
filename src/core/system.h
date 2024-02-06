#ifndef RTSYSTEM_H_
#define RTSYSTEM_H_

namespace rhythm_typer {
	namespace core {
		//Base class for game systems.
		class ISystem {
		public:
			ISystem() = default;

			//These functions are public variations of the normal
			//system functions and are mostly for debugging/testing purposes.
			//It is not advised to call any of these in actual game code.
			bool ForceInitialize();
			void ForceStart();
			void ForceUpdate(float delta_time = 0);

			virtual ~ISystem() = 0;
		protected:
			friend class RTGame;

			//Will be called when the game is initialized, or immediately
			//after being added to the game if the loop has already started.
			//It is not advised to have much functionality in this function
			//if the system is to be added later.
			virtual bool Initialize();

			//Will be called only once when the game loop starts, or
			//immediately after being added if the loop has already started.
			virtual void Start();

			//Will be called every frame in the game loop.
			//Argument delta_time is in seconds.
			virtual void Update(float delta_time = 0);

		};
	}
}

#endif