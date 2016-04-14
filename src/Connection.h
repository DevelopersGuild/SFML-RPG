#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <queue>
#include <vector>

#define PORT 41420

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
	//true at anytime until this class is about to be deleted;
	bool isListening;
	
	//the queue of packets (the Connection class 'USE' queue)
	std::queue<sf::Packet> packetQueue;

	//a 'check' packet must be sent for a certain of time in order to make sure there is no disconnection
	sf::Clock sec_sinceLastCheck;
public:
	Connection();
	Connection(const Connection&) = delete;
	Connection operator=(const Connection&) = delete;
};