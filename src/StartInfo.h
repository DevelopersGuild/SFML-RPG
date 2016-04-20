#pragma once
#include <SFML/Network.hpp>
#include <vector>

/*
StartInfo class
this class contains all necessary informations for the main game to start up.
The menu class fill in and return this class, then passed into Ingame class for initialization.
if the menu leaves, the type will be "exit".
*/
class StartInfo
{
private:
	enum TYPE{client, server, exit} type;
public:
	StartInfo();
};