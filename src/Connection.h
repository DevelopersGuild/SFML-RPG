#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <queue>

/*
Connection class
Handles the internet connection of the game.
*/
class Connection
{
private:
	//the socket for receving packets
	sf::UdpSocket receive;

	//the thread of listening packets (check the socket and enqueue packet only, nothing else)
	//std::thread listen;
	
	//the queue of packets (the Connection class 'USE' queue)
	std::queue<sf::Packet> queue;

	//is this a server? (server boardcasts packets to all client, while client sends packets to server only)
	bool isServer;

	//a 'check' packet must be sent for a certain of time in order to make sure there is no disconnection
	//sf::Clock sec_sinceLastCheck;

	//the thread to perform checking
	//std::thread handShakeThread;


public:
	Connection() = delete;
	Connection(const Connection&) = delete;
	Connection operator=(const Connection&) = delete;

	//the constructor must decide whether this computer is server or client
	//Connection(bool isServer);

	//the STATE of the connection
	enum STATE{not_ready, inGame};


};