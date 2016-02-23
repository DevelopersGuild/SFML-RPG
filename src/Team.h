#ifndef TEAM_H
#define TEAM_H

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
#endif