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
        sf::Packet packet;
        sf::IpAddress ip;
        unsigned short port;
        if(socket.receive(packet, ip, port) == sf::Socket::Status::Done)
        {
            mutex.lock();
            packetQueue.push(std::move(packet));
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
    listenThreadPtr.release();
}

sf::Socket::Status Connection::send(const sf::IpAddress& ip, sf::Packet& packet)
{
    if(sizeof(packet) >= sf::UdpSocket::MaxDatagramSize)
    {
        std::cout << "Error: the packet is bigger than maxDatagram size!" << std::endl;
        return sf::Socket::Status::Error;
    }
    return socket.send(packet, ip, DEFAULT_PORT);
}