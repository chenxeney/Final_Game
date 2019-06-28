#ifndef TURRET_2_HPP
#define TURRET_2_HPP
#include "Turret.hpp"

class Turret_2 : public Turret {
public:
	static const int Price;
	Turret_2(float x, float y);
	void CreateBullet() override;
};
#endif // MACHINEGUNTURRET_HPP
