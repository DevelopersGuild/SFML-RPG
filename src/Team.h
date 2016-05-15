#ifndef TEAM_H
#define TEAM_H

namespace Gameplay
{
	/*
	Team of player
	*/
	class Team
	{
	private:

	public:
		Team();
		Team(const Team& newTeam);				//copy constructor
		Team& operator=(const Team& newTeam);	//copy assignment constructor
	};
}
#endif