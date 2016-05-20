#pragma once
#include "GameSystem.h"

/*
ClientSystem class
Inherit from GameSystem.
Handles and manages the game as a client.
*/
namespace Gameplay
{
	
	class ClientSystem : public GameSystem
	{
	private:

	public:
		ClientSystem(Configuration& config, std::unique_ptr<StartInfo>& startInfo);
	};
}