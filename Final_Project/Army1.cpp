#include <allegro5/base.h>
#include <random>
#include <string>

#include "Point.hpp"
#include "Army1.h";
#include "PlayScene.hpp"
#define H 832
#define W 1600
Army1::Army1(int x, int y) : Army("play/dino-3.png", W-5*PlayScene::BlockSize, H-9*PlayScene::BlockSize, 0, 100, -20, 50),
head("play/dino-3.png", x, y), targetRotation(0) {
}
void Army1::Draw() const {
	Army::Draw();
	head.Draw();
}
void Army1::Update(float deltaTime) {
	Army::Update(deltaTime);
	head.Position = Position;
	// Choose arbitrary one.
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<> dist(0.0f, 4.0f);
	float rnd = dist(rng);
	if (rnd < deltaTime) {
		// Head arbitrary rotation.
		/*std::uniform_real_distribution<> distRadian(-ALLEGRO_PI, ALLEGRO_PI);
		targetRotation = distRadian(rng);*/
		head.Rotation = 0;
	}
	/*head.Rotation = (head.Rotation + deltaTime * targetRotation) / (1 + deltaTime);*/
}
