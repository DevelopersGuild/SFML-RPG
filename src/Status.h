#ifndef STATUS_H
#define STATUS_H
#include "Character.h"

namespace Gameplay
{
	class Status
	{
	private:
		Character* character;
		bool isPoisoned;
		bool isStunned;
		bool lowHealth;

	public:
		Status(bool poisoned, bool stunned, bool lowHealth);
	};
}
#endif