#include <functional>
#include <string>
#include "AudioHelper.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "StartScene.hpp"
#include "Group.hpp"
#include "Point.hpp"
#include "Image.hpp"
void StartScene::Initialize() {
	// TODO 1 (2/2): You can imitate the 2 files: 'StartScene.hpp', 'StartScene.cpp' to implement your start scene.
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	Engine::ImageButton* btn;
	Engine::Image *background;
	background = new Engine::Image("stage-select/start.png", 0, 0);
	AddNewObject(background);
	btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&StartScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Start", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
	AudioHelper::PlayAudio("start.ogg");
}
void StartScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
