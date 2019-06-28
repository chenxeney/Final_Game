#include <allegro5/base.h>
#include <random>
#include <string>

#include "GameEngine.hpp"
#include "Army1.h";


Army1 ::Army1(std::string imgBase, std::string imgTurret, float x, float y, float radius, int price,
			float coolDown, float speed, float hp) {
	Engine::Sprite(imgTurret, x, y); 
	speed = speed;
	hp = hp;
	price = price;
	coolDown = coolDown;
	Engine::Sprite::CollisionRadius = radius;
}
Army1::CreateBullet() {



}