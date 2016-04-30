#include "Connection.h"
#include <iostream>

Connection::Connection()
{
	isListening = true;
	socket.bind(DEFAULT_PORT);
    socket.setBlocking(false);
    //start listening
    listenThreadPtr.reset(new std::thread(&Connection::listen, this));
    
}

void Connection::listen()
{
    while(isListening)
    {
		Package package;
        unsigned short port;
        if(socket.receive(package.packet, package.ip, port) == sf::Socket::Status::Done)
        {
            mutex.lock();
            packetQueue.push(std::move(package));
            mutex.unlock();
        }
    }
}

Connection::~Connection()
{
    isListening = false;
    if(listenThreadPtr->joinable())
    {
        listenThreadPtr->join();
    }
    listenThreadPtr.reset();
	socket.unbind();
}

sf::Socket::Status Connection::send(const sf::IpAddress& ip, sf::Packet& packet)
{
    if(ip == sf::IpAddress::None)
    {
        return sf::Socket::Status::Error;
    }
    if(sizeof(packet) >= sf::UdpSocket::MaxDatagramSize)
    {
        std::cout << "Error: the packet is bigger than maxDatagram size!" << std::endl;
        return sf::Socket::Status::Error;
    }
    return socket.send(packet, ip, DEFAULT_PORT);
}