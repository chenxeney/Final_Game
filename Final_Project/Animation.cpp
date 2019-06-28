#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>
#include <memory>
#include <iostream>
#include "Enemy.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "Startscene.hpp"
#include "Point.hpp"
#include "Animation.h"

StartScene* Animation::getStartScene() {
	return dynamic_cast<StartScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Animation::CreateBITMAP(){
    return;
}
Animation::Animation(std::string img0, std::string img1, std::string img2, std::string img3, std::string img4, float x, float y){
    sprite[0] = al_load_bitmap("play/sprite0.png");
    sprite[1] = al_load_bitmap("play/sprite1.png");
    sprite[2] = al_load_bitmap("play/sprite2.png");
    sprite[3] = al_load_bitmap("play/sprite3.png");
    sprite[4] = al_load_bitmap("play/sprite4.png");
}
void Animation::Update(float deltaTime) {
	sprite_now_index++;
    sprite_now_index = sprite_now_index%6;
    return;
}
void Animation::Draw(){
	al_draw_bitmap(sprite[sprite_now_index], 300, 300, 0);
}

