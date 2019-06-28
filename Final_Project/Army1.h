#ifndef ARMY1_H_INCLUDED
#define ARMY1_H_INCLUDED
#include "Turret.hpp"

#include "Army.h"
#include "Sprite.hpp"

class Army1 : public Army {
private:
	Sprite head;
	float targetRotation;
public:
	Army1(int x, int y);
	void Draw() const override;
	void Update(float deltaTime) override;
};
#endif // TANKENEMY_HPP

