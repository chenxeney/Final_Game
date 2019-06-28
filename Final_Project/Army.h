#ifndef ARMY_HPP
#define ARMY_HPP
#include <allegro5/base.h>
#include <list>
#include <string>
#include "Turret.hpp"
#include "Enemy.hpp"
#include "Sprite.hpp"


class Army : public Turret, public Enemy  {
	Army(std::string imgBase, std::string imgTurret, float x, float y, float radius, int price,
		float coolDown, float speed, float hp);
};

#endif
