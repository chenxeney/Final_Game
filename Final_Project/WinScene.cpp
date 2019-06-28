#include "WinScene.hpp"
#include "Label.hpp"
#include "AudioHelper.hpp"
#include "PlayScene.hpp"
#include <iostream>
#include "thread"
void WinScene::thread_task() {
    /*std::this_thread::sleep_for(std::chrono::seconds(3));*/
    std::cout << "hello thread " << std::endl;
    return;
}
void WinScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	Engine::Image *background;
	background = new Engine::Image("win/win.jpg", 0, 0);
	AddNewObject(background);
	AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 2, 255, 255, 255, 255, 0.5, 0.5));
	AddNewObject(new Engine::Label("The difficulty is harder!", "pirulen.ttf", 48, halfW-50, halfH / 2+150, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
	AudioHelper::PlayAudio("win.wav");
}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		AudioHelper::PlayBGM("happy.ogg");
	}
}
void WinScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
