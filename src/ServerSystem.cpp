#include "ServerSystem.h"

Gameplay::ServerSystem::ServerSystem(Configuration & config, std::unique_ptr<StartInfo>& startInfoPtr) :
	GameSystem::GameSystem(config, startInfoPtr)
{

}
