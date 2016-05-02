#include "GameNetwork.h"

using namespace Gameplay;

GameNetwork::GameNetwork(GameSystem* newSystem) : system(newSystem)
{
	
}

sf::Socket::Status Gameplay::GameNetwork::send(sf::IpAddress & ip, sf::Packet & packet)
{
	return connection.send(ip, packet);
}

void Gameplay::GameNetwork::update()
{
	if (!connection.empty())
	{

	}
}
