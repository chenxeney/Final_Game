#ifndef FIREBULLET_HPP
#define FIREBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class FireBullet : public Bullet {
public:
	explicit FireBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void Update(float deltaTime);
	void OnExplode(Enemy* enemy) override;
    const float rotateRadian = 2 * ALLEGRO_PI;
	std::list<Bullet*>::iterator lockedBulletIterator;
};
#endif // FIREBULLET_HPP
