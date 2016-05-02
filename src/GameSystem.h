#ifndef GameSystem_h
#define GameSystem_h

#include "GameData.h"

namespace Gameplay
{
	//forward declaration of GameNetwork
	class GameNetwork;

	//forward declaration of GameInterface
	class GameInterface;

	/*
	GameSystem class
	Base class for processing and managing game data.
	*/
	class GameSystem
	{
		friend GameInterface;
	private:
		GameNetwork* networkPtr;
	protected:
		GameData gameData;
		
	public:
		GameSystem(Configuration& config);
		GameSystem(const GameSystem&) = delete;
		GameSystem operator=(const GameSystem&) = delete;
		GameSystem(const GameSystem&&) = delete;

		void setNetworkPtr(GameNetwork* ptr) { networkPtr = ptr; }

		void moveCharacter(const float& x, const float& y)
		{
			gameData.moveCharacter(x, y);
		}
	};
}
#endif /* GameSystem_h */
