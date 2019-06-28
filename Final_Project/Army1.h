#ifndef ARMY1_H_INCLUDED
#define ARMY1_H_INCLUDED

#include "Army.h"

class Army1 : public Army {

public:
	Army1(std::string imgBase, std::string imgTurret, float x, float y, float radius, int price, 
		float coolDown, float speed, float hp);
};
#endif 

