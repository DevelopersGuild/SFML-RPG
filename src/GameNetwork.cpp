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
			std::string playerName;
			std::string direction;
			package.packet >> playerName >> direction;
			if (direction == "right")
				system->movePlayer(playerName, Character::Direction::right);
			else if(direction == "left")
				system->movePlayer(playerName, Character::Direction::left);
			else if(direction == "up")
				system->movePlayer(playerName, Character::Direction::up);
			else if(direction == "down")
				system->movePlayer(playerName, Character::Direction::down);
            
            //if this is server, forward the move signal to other player
            if(isServer())
            {
                sf::Packet packet;
                packet << playerName << "move" << direction;
                boardCast_excpet(playerName, packet);
            }
		}
		else if (signal == "changeMap")
		{
			std::string mapName;
			std::string location;
			package.packet >> mapName >> location;
			system->addPlayertoMap(playerName_Tree.at(package.ip), mapName, location);
            
            //if this is server, forward the move signal to other player
            if(isServer())
            {
                sf::Packet packet;
                packet << "changeMap" << mapName << location;
                boardCast_excpet(playerName_Tree.at(package.ip), packet);
            }
		}
		else if (signal == "setPosition")
		{
			std::string playerName;
			float x, y;
			package.packet >> playerName >> x >> y;
			sf::Vector2f position(x, y);
			system->setPlayerPosition(playerName, position);
            
            //if this is server, forward the move signal to other player
            if(isServer())
            {
                sf::Packet packet;
                packet << "setPosition" << x << y;
                boardCast_excpet(playerName, packet);
            }
		}
        connection.pop();
	}
}

void Gameplay::GameNetwork::boardCast(sf::Packet& packet)
{
    //only server can call this function
    assert(isServer());
    
    for(auto& it : playerName_Tree)
    {
        connection.send(it.first, packet);
    }
}

void Gameplay::GameNetwork::boardCast_excpet(const std::string &playerName, sf::Packet &packet)
{
    //only server can call this function
    assert(isServer());
    
    for(auto& it : playerName_Tree)
    {
        if(it.second != playerName)
        {
            connection.send(it.first, packet);
        }
    }
}