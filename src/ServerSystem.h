#pragma once
#include "GameSystem.h"

/*
ServerSystem
Inherit from GameSystem.
Handles and manages the game as a server.
*/

namespace Gameplay
{
	class ServerSystem : public GameSystem
	{
	private:

	public:
		ServerSystem(Configuration& config) : GameSystem::GameSystem(config)
		{

		}
	};
}