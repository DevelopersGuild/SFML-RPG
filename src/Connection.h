#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <queue>
#include <mutex>
#include <vector>

//the default port
#define DEFAULT_PORT 41420
/*
Package struct
Contains packet and source IP address
*/
struct Package
{
	sf::Packet packet;
	sf::IpAddress ip;
};

/*
Connection class
Handles the internet connection of the game.
Note: The class receive the packet only. It does not handle the packet becuase it is the responbility of client or server.
*/
class Connection
{
private:
	//the socket for receving packets
	sf::UdpSocket socket;

	//the thread of listening packets (check the socket and enqueue packet only, nothing else)
    std::unique_ptr<std::thread> listenThreadPtr;
    std::mutex mutex;
    void listen();
    
	//true at anytime until this class is about to be deleted;
	bool isListening;
	
	//the queue of packets (the Connection class 'USE' queue)
	std::queue<Package> packetQueue;

	//a 'check' packet must be sent for a certain of time in order to make sure there is no disconnection
	sf::Clock sec_sinceLastCheck;
    
public:
	Connection();
	Connection(const Connection&) = delete;
	Connection operator=(const Connection&) = delete;
    
    //in the destructor, set isListening to false to terminate the thread
    ~Connection();
    
    //send a packet to target ip
    sf::Socket::Status send(const sf::IpAddress& ip, sf::Packet& packet);    
    
    //Connection "Use" queue
    //is the queue empty?
    bool empty(){return packetQueue.empty();}
    
    //remove the first packet
    void pop(){packetQueue.pop();}
    
    //get the first packet
	Package& front(){return packetQueue.front();}

	//return the number of packet in the queue
	int getSize() { return packetQueue.size(); }
};
 
