#ifndef ARMYBUTTON_H_INCLUDED
#define ARMYBUTTON_H_INCLUDED

#include <string>

#include "ImageButton.hpp"
#include "Sprite.hpp"

class PlayScene;

class ArmyButton : public Engine::ImageButton {
protected:
    PlayScene* getPlayScene();
public:
	int money;
	Engine::Sprite Base;
	Engine::Sprite Army;
	ArmyButton(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite Army, float x, float y, int money);
	void Update(float deltaTime) override;
	void Draw() const override;
};


#endif // ARMYBUTTON_H_INCLUDED
