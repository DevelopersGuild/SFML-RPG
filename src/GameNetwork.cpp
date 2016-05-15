#include "GameNetwork.h"

using namespace Gameplay;

GameNetwork::GameNetwork(GameSystem* newSystem, std::unique_ptr<StartInfo>& info) : system(newSystem)
{
	//set server's IP
	serverIP = info->serverIP;

	//initializing the player's name tree
	for (StartInfo::Player& player : info->playerList)
	{
		playerName_Tree.emplace(player.ip, player.name);
	}
}

sf::Socket::Status Gameplay::GameNetwork::send(sf::IpAddress & ip, sf::Packet & packet)
{
	return connection.send(ip, packet);
}

void Gameplay::GameNetwork::update()
{
	if (!connection.empty())
	{
		Package& package = connection.front();
		std::string signal;
		package.packet >> signal;
		if (signal == "ready")
		{
			sf::Packet packet;
			packet << "start";
			send(package.ip, packet);
			system->setReady(playerName_Tree.at(package.ip), true);
		}
		else if (signal == "move")
		{
			std::string direction;
			package.packet >> direction;
			if (direction == "right")
				system->movePlayer(playerName_Tree.at(package.ip), Character::Direction::right);
			else if(direction == "left")
				system->movePlayer(playerName_Tree.at(package.ip), Character::Direction::left);
			else if(direction == "up")
				system->movePlayer(playerName_Tree.at(package.ip), Character::Direction::up);
			else if(direction == "down")
				system->movePlayer(playerName_Tree.at(package.ip), Character::Direction::down);
		}
		else if (signal == "changeMap")
		{
			std::string mapName;
			std::string location;
			package.packet >> mapName >> location;
			system->addPlayertoMap(playerName_Tree.at(package.ip), mapName, location);
		}
        connection.pop();
	}
}
