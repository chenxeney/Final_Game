#include <allegro5/base.h>
#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "FireBullet_2.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

class Turret;

FireBullet_2::FireBullet_2(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/bullet-2.png", 500, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}

void FireBullet_2::OnExplode(Enemy* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-2.png", dist(rng), enemy->Position.x, enemy->Position.y));
}
