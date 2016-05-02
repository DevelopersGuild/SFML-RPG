#ifndef GameNetwork_h
#define GameNetwork_h

#include "GameSystem.h"
#include "Connection.h"
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
	public:
		GameNetwork(GameSystem* system);
		sf::Socket::Status send(sf::IpAddress& ip, sf::Packet& packet);

		//get and implement the incoming packet
		void update();
	};
}

#endif /* GameNetwork_h */
