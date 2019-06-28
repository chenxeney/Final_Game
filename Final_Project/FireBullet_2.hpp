#ifndef FIREBULLET_2_HPP
#define FIREBULLET_2_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
	struct Point;
}  // namespace Engine

class FireBullet_2 : public Bullet {
public:
	explicit FireBullet_2 (Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
};
#endif // FIREBULLET_HPP
