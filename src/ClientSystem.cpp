#include "ClientSystem.h"

Gameplay::ClientSystem::ClientSystem(Configuration & config, std::unique_ptr<StartInfo>& startInfo) :
	GameSystem(config, startInfo)
{
}
