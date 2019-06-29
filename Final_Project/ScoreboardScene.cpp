#include "WinScene.hpp"
#include "Label.hpp"
#include "AudioHelper.hpp"
#include "PlayScene.hpp"
#include "ScoreboardScene.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
void ScoreboardScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	Engine::Image *background;
	background = new Engine::Image("play/scoreboard.jpg", 0, 0);
	AddNewObject(background);
    fstream file;
    string s;
    stringstream ss;
    int scores;
    file.open("scoreboard.txt", ios::in);
    do{
        getline(file, s);
        ss << s;
        ss >> scores;
        ss.clear();
        ranking.push_back(scores);
    }while(!file.eof());
    file.close();
    sort(ranking.begin(), ranking.end(), greater<int>());
    int size = ranking.size();
    int mini = min(10, size);
    for(int i = 1; i <= mini; i++){
        int tmpnumber;
        tmpnumber = i;
        stringstream tmpss;
        string tmpstring1;
        tmpss << tmpnumber;
        tmpss >> tmpstring1;
        tmpss.clear();
        tmpstring1 += " ";
        tmpnumber = ranking[i-1];
        tmpss << tmpnumber;
        string tmpstring2;
        tmpss >> tmpstring2;
        tmpstring1 += tmpstring2;
        AddNewObject(new Engine::Label(tmpstring1, "pirulen.ttf", 32, halfW, halfH * i / 8, 255, 255, 255, 255, 0.5, 0.5));
        tmpss.clear();
        tmpstring1.clear();
        tmpstring2.clear();
    }
    ranking.clear();
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClickSelect, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Stage", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
	AudioHelper::PlayAudio("win.wav");
}
void ScoreboardScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		AudioHelper::PlayBGM("happy.ogg");
	}
}
void ScoreboardScene::BackOnClickSelect(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
