#include <allegro5/base.h>
#include <cmath>
#include <string>
#include "AudioHelper.hpp"
#include "FireBullet.hpp"
#include "Group.hpp"
#include "NewTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

const int NewTurret::Price = 50;
NewTurret::NewTurret(float x, float y) :
	// TODO 2 (2/8): You can imitate the 2 files: 'MachineGunTurret.hpp', 'MachineGunTurret.cpp' to create a new turret.
	Turret("play/dino-3-big.png", "play/turret-7.png", x, y, 300, Price, 0.5) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void NewTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new FireBullet(Position + normalized * 36, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
