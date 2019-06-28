#ifndef ARMY_H_INCLUDED
#define ARMY_H_INCLUDED

#include <list>
#include <vector>
#include <string>

#include "Point.hpp"
#include "Sprite.hpp"

class Bullet;
class PlayScene;
class Turret;

class Army : public Engine::Sprite {
protected:
	std::vector<Engine::Point> path;
	float speed;
	float hp;
	PlayScene* getPlayScene();
	virtual void OnExplode();
public:
    int Price;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Army(std::string img, float x, float y, float radius, float speed, float hp, int money);
	int Return_Price();
	void Hit(float damage);
	void UpdatePath(const std::vector<std::vector<int>>& mapDistance);
	void Update(float deltaTime) override;
	void Draw() const override;
};
#endif // Army_HPP
