#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED
#include <allegro5/base.h>
#include <list>
#include <string>
#include "IObject.hpp"
#include "Sprite.hpp"

class Enemy;
class PlayScene;

class Animation{
protected:
public:
	float reload = 0;
	int sprite_now_index = 0;
	StartScene* getStartScene();
	// Reference: Design Patterns - Factory Method.
    Animation(std::string img0, std::string img1, std::string img2, std::string img3, std::string img4, float x, float y);
    void CreateBITMAP();
    void Update(float deltaTime);
    void Draw();
    ALLEGRO_BITMAP *sprite[5];
};
#endif // ANIMATION_H_INCLUDED
