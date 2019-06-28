#include <allegro5/color.h>

#include "GameEngine.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "ArmyButton.h"

PlayScene* ArmyButton::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
ArmyButton::ArmyButton(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite Army, float x, float y, int money) :
	ImageButton(img, imgIn, x, y), money(money), Base(Base), Army(Army) {
}
void ArmyButton::Update(float deltaTime) {
	ImageButton::Update(deltaTime);
	if (getPlayScene()->GetMoney() >= money) {
		Enabled = true;
		Base.Tint = Army.Tint = al_map_rgba(255, 255, 255, 255);
	} else {
		Enabled = false;
		Base.Tint = Army.Tint = al_map_rgba(0, 0, 0, 160);
	}
}
void ArmyButton::Draw() const {
	ImageButton::Draw();
	Base.Draw();
	Army.Draw();
}
