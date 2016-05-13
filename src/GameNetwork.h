#ifndef GameNetwork_h
#define GameNetwork_h

#include "GameSystem.h"
#include "Connection.h"
#include "StartInfo.h"
#include <SFML/Network.hpp>

namespace Gameplay
{
	/*
	GameNetwork class
	Handles inputs from the internet
	*/
	class GameNetwork
	{
	private:
		GameSystem* system;	//the network call system's function
		Connection connection;
		std::map<sf::IpAddress, std::string> playerName_Tree;	//for converting sf::Ipaddress to player's name
		sf::IpAddress serverIP;	//server'IP. Invalid if this computer is server.
	public:
		GameNetwork(GameSystem* system, std::unique_ptr<StartInfo>& info);
		sf::Socket::Status send(sf::IpAddress& ip, sf::Packet& packet);

		//get and implement the incoming packet
		void update();

		//get server's ip, invalid if this computer is server
		sf::IpAddress getServerIP() { return serverIP; }
	};
}

#endif /* GameNetwork_h */
