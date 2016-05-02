#ifndef GameInterface_h
#define GameInterface_h

#include "GameSystem.h"
#include "Configuration.h"

namespace Gameplay
{
	/*
	GameInterface class
	Handles inputs from this computer
	*/
	class GameInterface : public sf::Drawable
	{
	private:
		Gameplay::GameSystem* system;	//the interface calls system's function.
	public:
		GameInterface(GameSystem* system);

		//draw the game screen on the window.
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
	};
}


#endif /* GameInterface_h */
