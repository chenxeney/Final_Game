#include <allegro5/allegro.h>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <memory>
#include <string>
#include <algorithm>
#include <thread>

#include "AudioHelper.hpp"
#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "Image.hpp"
#include "Label.hpp"
#include "LaserTurret.hpp"
#include "MachineGunTurret.hpp"
#include "MissileTurret.hpp"
#include "Plane.hpp"
#include "PlaneEnemy.hpp"
#include "PlayScene.hpp"
#include "SoldierEnemy.hpp"
#include "NewEnemy.hpp"
#include "Sprite.hpp"
#include "TankEnemy.hpp"
#include "Turret.hpp"
#include "TurretButton.hpp"
#include "NewTurret.hpp"
#include "Army.h"
#include "Army1.h"
#include "TurretButton.hpp"
#include "LaserBullet.hpp"
#include "Point.hpp"

#define H 832
#define W 1600
bool PlayScene::DebugMode = false;
const std::vector<Engine::Point> PlayScene::directions = { Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0), Engine::Point(0, 1) };
const int PlayScene::MapWidth = 20, PlayScene::MapHeight = 13;
const int PlayScene::BlockSize = 64;
const Engine::Point PlayScene::SpawnGridPoint = Engine::Point(-1 , MapHeight - 3);
const Engine::Point PlayScene::EndGridPoint = Engine::Point(MapWidth, MapHeight - 3);
const std::vector<int> PlayScene::code = { ALLEGRO_KEY_UP, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_DOWN,
									ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT,
									ALLEGRO_KEY_B, ALLEGRO_KEY_A, ALLEGRO_KEYMOD_SHIFT, ALLEGRO_KEY_ENTER };
Engine::Point PlayScene::GetClientSize() {
	return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}
void PlayScene::AddBackgroundThread(string background_path, int x, int y){
    Engine::Image* background;
	background = new Engine::Image(background_path, 0, 0);
	AddNewObject(background);
    return;
}


void PlayScene::Initialize() {
	// TODO 5 (1/2): There's a bug in this file, which crashes the game when you win. Try to find it.
	// TODO 5 (2/2): There's a cheat code in this file. Try to find it.
	mapState.clear();
	keyStrokes.clear();
	ticks = 0;
	lives = 1;
	money = 150;
	SpeedMult = 1;
	//
    Engine::Image* background;
	background = new Engine::Image("play/play3.jpg", 0, 0);
	AddNewObject(background);
	Engine::Image* enemytower;
	enemytower = new Engine::Image("play/tower4.png", 0, H-9*BlockSize);
	AddNewObject(enemytower);
	Engine::Image* mytower;
	mytower = new Engine::Image("play/tower4.png", W-5*BlockSize, H-9*BlockSize);
	AddNewObject(mytower);
	//
	// Add groups from bottom to top.
	AddNewObject(TileMapGroup = new Group());
	AddNewObject(GroundEffectGroup = new Group());
	AddNewObject(DebugIndicatorGroup = new Group());
	AddNewObject(TowerGroup = new Group());
	AddNewObject(EnemyGroup = new Group());
	AddNewObject(BulletGroup = new Group());
	AddNewObject(EffectGroup = new Group());
	// Should support buttons.
	AddNewControlObject(UIGroup = new Group());
	ReadMap();
	ReadEnemyWave();
	mapDistance = CalculateBFSDistance();
	ConstructUI();
	imgTarget = new Engine::Image("play/target.png", 0, 0);
	imgTarget->Visible = false;
	preview = nullptr;
	UIGroup->AddNewObject(imgTarget);
	AudioHelper::PlayBGM("play.ogg");
}
void PlayScene::Update(float deltaTime) {
	// If we use deltaTime directly, then we might have Bullet-through-paper problem.
	// Reference: Bullet-Through-Paper
	for (int i = 0; i < SpeedMult; i++) {
		IScene::Update(deltaTime);
		// Check if we should create new enemy.
		ticks += deltaTime;
		if (enemyWaveData.empty()) {
			if (EnemyGroup->GetObjects().empty()) {
				Engine::GameEngine::GetInstance().ChangeScene("win");
			}
			continue;
		}
		auto current = enemyWaveData.front();
		if (ticks < current.second)
			continue;
		ticks -= current.second;
		enemyWaveData.pop_front();
		const Engine::Point SpawnCoordinate = Engine::Point(SpawnGridPoint.x * BlockSize + BlockSize / 2, SpawnGridPoint.y * BlockSize + BlockSize / 2);
		Enemy* enemy;
		switch (current.first) {
		case 1:
			EnemyGroup->AddNewObject(enemy = new SoldierEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
			break;
		case 2:
			EnemyGroup->AddNewObject(enemy = new PlaneEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
			break;
		case 3:
			EnemyGroup->AddNewObject(enemy = new TankEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
			break;
		case 4:
			EnemyGroup->AddNewObject(enemy = new NewEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
			break;
		default:
			continue;
		}
		enemy->UpdatePath(mapDistance);
		// Compensate the time lost.
		enemy->Update(ticks);
	}
	if (preview) {
		preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
		// To keep responding when paused.
		preview->Update(deltaTime);
	}
}
void PlayScene::Draw() const {
	IScene::Draw();
	if (DebugMode) {
		// Draw reverse BFS distance on all reachable blocks.
		for (int i = 0; i < MapHeight; i++) {
			for (int j = 0; j < MapWidth; j++) {
				if (mapDistance[i][j] != -1) {
					// Not elegant nor efficient, but it's quite enough for debugging.
					Engine::Label label(std::to_string(mapDistance[i][j]), "pirulen.ttf", 32, (j + 0.5) * BlockSize, (i + 0.5) * BlockSize);
					label.Anchor = Engine::Point(0.5, 0.5);
					label.Draw();
				}
			}
		}
	}
}
void PlayScene::AssignArmy1(){
    std::unique_ptr<int> black (new int (255));
    Turret *NewArmy(new LaserTurret(W-5*BlockSize, H-3*BlockSize));
    NewArmy->Enabled = true;
    NewArmy->Preview = true;
    EarnMoney(-20);
    NewArmy->Tint = al_map_rgba((*black),(*black), (*black), (*black));
    UIGroup->AddNewObject(NewArmy);
    preview = nullptr;
    return;
}
void PlayScene::AssignArmy2(){
    std::unique_ptr<int> black (new int (255));
    Turret *NewArmy;
    NewArmy = new MissileTurret(W-5*BlockSize, H-3*BlockSize);
    NewArmy->Enabled = true;
    NewArmy->Preview = true;
    EarnMoney(-30);
    NewArmy->Tint = al_map_rgba((*black),(*black), (*black), (*black));
    UIGroup->AddNewObject(NewArmy);
    preview = nullptr;
    return;
}
void PlayScene::AssignArmy3(){
    std::unique_ptr<int> black (new int (255));
    Turret *NewArmy;
    NewArmy = new NewTurret(W-5*BlockSize, H-3*BlockSize);
    NewArmy->Enabled = true;
    NewArmy->Preview = true;
    EarnMoney(-50);
    NewArmy->Tint = al_map_rgba((*black),(*black), (*black), (*black));
    UIGroup->AddNewObject(NewArmy);
    preview = nullptr;
    return;
}

void PlayScene::OnMouseDown1(int button, int mx, int my) {
	if (button & 1) {
		AssignArmy1();
	}
}


void PlayScene::OnMouseDown2(int button, int mx, int my) {
	if (button & 1) {
		AssignArmy2();
	}
}


void PlayScene::OnMouseDown3(int button, int mx, int my) {
	if (button & 1) {
		AssignArmy3();
	}
}
void PlayScene::OnMouseDown(int button, int mx, int my) {
	if ((button & 1) && !imgTarget->Visible && preview) {
		// Cancel turret construct.
		UIGroup->RemoveObject(preview->GetObjectIterator());
		preview = nullptr;
	}
	int n = [] (int mx, int my, int x, int y) { return (mx >= x && mx <= x+BlockSize && my >= y && my <= y+BlockSize);}(mx, my, 1370, 136);
	if(n)
        PlayScene::OnMouseDown1(button, mx, my);
    n = [] (int mx, int my, int x, int y) { return (mx >= x && mx <= x+BlockSize && my >= y && my <= y+BlockSize);}(mx, my, 1446, 136);
    if(n)
        PlayScene::OnMouseDown2(button, mx, my);
    n = [] (int mx, int my, int x, int y) { return (mx >= x && mx <= x+BlockSize && my >= y && my <= y+BlockSize);}(mx, my, 1522, 136);
    if(n)
        PlayScene::OnMouseDown3(button, mx, my);
}
void PlayScene::OnMouseMove(int mx, int my) {
	IScene::OnMouseMove(mx, my);
	const int x = mx / BlockSize;
	const int y = my / BlockSize;
	if (!preview || x < 0 || x >= MapWidth || y < 0 || y >= MapHeight) {
		imgTarget->Visible = false;
		return;
	}
	imgTarget->Visible = true;
	imgTarget->Position.x = x * BlockSize;
	imgTarget->Position.y = y * BlockSize;
}
void PlayScene::OnMouseUp(int button, int mx, int my) {
	Down = false;
	/*const int x = mx / BlockSize;
	const int y = my / BlockSize;
	if (button & 1) {
		if (mapState[y][x] != TILE_OCCUPIED) {
			if (!preview)
				return;
			// Check if valid.
			if (!CheckSpaceValid(x, y)) {
				Engine::Sprite* sprite;
				GroundEffectGroup->AddNewObject(sprite = new DirtyEffect("play/target-invalid.png", 1, x * BlockSize + BlockSize / 2, y * BlockSize + BlockSize / 2));
				sprite->Rotation = 0;
				return;
			}
			// Purchase.
			EarnMoney(-preview->GetPrice());
			// Remove Preview.
			preview->GetObjectIterator()->first = false;
			UIGroup->RemoveObject(preview->GetObjectIterator());
			// Construct real turret.
			preview->Position.x = x * BlockSize + BlockSize / 2;
			preview->Position.y = y * BlockSize + BlockSize / 2;
			preview->Enabled = true;
			preview->Preview = true;
			preview->Tint = al_map_rgba(255, 255, 255, 255);
			TowerGroup->AddNewObject(preview);
			// To keep responding when paused.
			preview->Update(0);
			// Remove Preview.
			preview = nullptr;

			mapState[y][x] = TILE_OCCUPIED;
			EarnMoney(-preview->GetPrice());
			OnMouseMove(mx, my);
			preview->GetObjectIterator()->first = false;
			UIGroup->RemoveObject(preview->GetObjectIterator());
			preview->Position.x = W-1*BlockSize;//
			preview->Position.y = H-9*BlockSize;
			preview->Enabled = true;
			preview->Preview = true;
			preview->Tint = al_map_rgba(255, 255, 255, 255);
			TowerGroup->AddNewObject(preview);
            UIGroup->AddNewObject(preview);*/
			// To keep responding when paused.
			/*preview->Update(0.8);*/
			// Remove Preview.
			preview = nullptr;
}
void PlayScene::OnKeyDown(int keyCode) {
	IScene::OnKeyDown(keyCode);
	if (keyCode == ALLEGRO_KEY_TAB) {
		DebugMode = !DebugMode;
	}
	else {
		keyStrokes.push_back(keyCode);
		if (keyStrokes.size() > code.size())
			keyStrokes.pop_front();
		if (keyCode == ALLEGRO_KEY_ENTER && keyStrokes.size() == code.size()) {
			auto it = keyStrokes.begin();
			for (int c : code) {
				if (*it != c && (c == ALLEGRO_KEYMOD_SHIFT && *it != ALLEGRO_KEY_LSHIFT && *it != ALLEGRO_KEY_RSHIFT))
					return;
				++it;
			}
			EffectGroup->AddNewObject(new Plane());
		}
	}
	if (keyCode == ALLEGRO_KEY_Q) {
		// Hotkey for MachineGunTurret.
		AssignArmy1();
	}
	else if (keyCode == ALLEGRO_KEY_W) {
		// Hotkey for LaserTurret.
		AssignArmy2();
	}
	else if (keyCode == ALLEGRO_KEY_E) {
		// Hotkey for MissileTurret.
		AssignArmy3();
	}
	// TODO 2 (5/8): Make the R key to create the 4th turret.
	else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
		// Hotkey for Speed up.
		SpeedMult = keyCode - ALLEGRO_KEY_0;
	}
}
void PlayScene::Hit() {
	lives--;
	UILives->Text = std::string("Life ") + std::to_string(lives);
	if (lives <= 0) {
		Engine::GameEngine::GetInstance().ChangeScene("lose");
	}
}
int PlayScene::GetMoney() const {
	return money;
}
void PlayScene::EarnMoney(int money) {
	this->money += money;
	UIMoney->Text = std::string("$") + std::to_string(this->money);
}
void PlayScene::ReadMap() {
	std::string filename = std::string("resources/map") + std::to_string(MapId) + ".txt";
	// Read map file.
	char c;
	std::vector<bool> mapData;
	std::ifstream fin(filename);
	while (fin >> c) {
		switch (c) {
		case '0': mapData.push_back(false); break;
		case '1': mapData.push_back(true); break;
		case '\n':
		case '\r':
			if (static_cast<int>(mapData.size()) / MapWidth != 0)
				throw std::ios_base::failure("Map data is corrupted.");
			break;
		default: throw std::ios_base::failure("Map data is corrupted.");
		}
	}
	fin.close();
	// Validate map data.
	if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
		throw std::ios_base::failure("Map data is corrupted.");
	// Store map in 2d array.
	mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));

	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			const int num = mapData[i * MapWidth + j];
			mapState[i][j] = num ? TILE_FLOOR : TILE_DIRT;
			/*
			if (num)
				TileMapGroup->AddNewObject(new Engine::Image("play/floor.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
			else
				TileMapGroup->AddNewObject(new Engine::Image("play/dirt.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
			*/
		}
	}

}
void PlayScene::ReadEnemyWave() {
	std::string filename = std::string("resources/enemy") + std::to_string(MapId) + ".txt";
	// Read enemy file.
	float type, wait, repeat;
	enemyWaveData.clear();
	std::ifstream fin(filename);
	while (fin >> type && fin >> wait && fin >> repeat) {
		for (int i = 0; i < repeat; i++)
			enemyWaveData.emplace_back(type, wait);
	}
	fin.close();
}


void PlayScene::ConstructUI() {
	// Background

	//UIGroup->AddNewObject(new Engine::Image("play/sand.png", 1280, 0, 320, 832));
	// Text

	UIGroup->AddNewObject(new Engine::Label(std::string("Stage ") + std::to_string(MapId), "pirulen.ttf", 32, 1294, 0, 255, 255, 255));
	UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("$") + std::to_string(money), "pirulen.ttf", 24, 1294, 48, 255, 255, 255));
	UIGroup->AddNewObject(UILives = new Engine::Label(std::string("Life ") + std::to_string(lives), "pirulen.ttf", 24, 1294, 88, 255, 255, 255));
	TurretButton* btn;
	// Button 2
	btn = new TurretButton("play/base.jpg", "play/base.jpg",
		Engine::Sprite("play/base.jpg", 1370, 136, 0, 0, 0, 0),
		Engine::Sprite("play/dino-1.png", 1370, 136, 0, 0, 0, 0)
		, 1370, 136, 50);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 0));
	UIGroup->AddNewControlObject(btn);
	// Button 3
	btn = new TurretButton("play/base.jpg", "play/base.jpg",
		Engine::Sprite("play/base.jpg", 1446, 136, 0, 0, 0, 0),
		Engine::Sprite("play/dino-2.png", 1446, 136, 0, 0, 0, 0)
		, 1446, 136, 50);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 1));
	UIGroup->AddNewControlObject(btn);
	// TODO 2 (3/8): Create a button to support constructing the 4th tower.
	btn = new TurretButton("play/base.jpg", "play/base.jpg",
		Engine::Sprite("play/base.jpg", 1522, 136, 0, 0, 0, 0),
		Engine::Sprite("play/dino-3.png", 1522, 136, 0, 0, 0, 0)
		, 1522, 136, 50);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 2));
	UIGroup->AddNewControlObject(btn);
    Turret* InitialTurret;
    InitialTurret = new MachineGunTurret(W - 3 * BlockSize + 20, H - 8 * BlockSize - 30);
    TowerGroup->AddNewObject(InitialTurret);
}

void PlayScene::UIBtnClicked(int id) {
    /*std::cout << "Clicked" << '\n';
	if (preview)
		UIGroup->RemoveObject(preview->GetObjectIterator());
	if (id == 0 && money >= LaserTurret::Price){
        std::cout << "Laser" << '\n';
		preview = new LaserTurret(1200, 1000);
		std::cout << "Create" << '\n';
	}
	else if (id == 1 && money >= LaserTurret::Price){
        std::cout << "Laser" << '\n';
		preview = new LaserTurret(1200, 300);
	}
	else if (id == 2 && money >= MissileTurret::Price){
        std::cout << "Laser" << '\n';
		preview = new LaserTurret(1200, 300);
	}if (!preview){
        std::cout << "No" << '\n';
		return;
	}
    preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
	preview->Tint = al_map_rgba(255, 255, 255, 200);
	preview->Enabled = false;
	preview->Preview = true;
	UIGroup->AddNewObject(preview);*/
	TowerGroup->AddNewObject(preview);
	/*OnMouseMove(Engine::GameEngine::GetInstance().GetMousePosition().x, Engine::GameEngine::GetInstance().GetMousePosition().y);*/
}

bool PlayScene::CheckSpaceValid(int x, int y) {
	if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight)
		return false;
	auto map00 = mapState[y][x];
	mapState[y][x] = TILE_OCCUPIED;
	std::vector<std::vector<int>> map = CalculateBFSDistance();
	mapState[y][x] = map00;
	if (map[0][0] == -1)
		return false;
	for (auto& it : EnemyGroup->GetObjects()) {
		Engine::Point pnt;
		pnt.x = floor(it->Position.x / BlockSize);
		pnt.y = floor(it->Position.y / BlockSize);
		if (pnt.x < 0 || pnt.x >= MapWidth || pnt.y < 0 || pnt.y >= MapHeight)
			continue;
		if (map[pnt.y][pnt.x] == -1)
			return false;
	}
	// All enemy have path to exit.
	mapState[y][x] = TILE_OCCUPIED;
	mapDistance = map;
	for (auto& it : EnemyGroup->GetObjects())
		dynamic_cast<Enemy*>(it)->UpdatePath(mapDistance);
	return true;
}
std::vector<std::vector<int>> PlayScene::CalculateBFSDistance() {
	// Reverse BFS to find path.
	std::vector<std::vector<int>> map(MapHeight, std::vector<int>(std::vector<int>(MapWidth, -1)));
	std::queue<Engine::Point> que;
	// Push end point.
	// BFS from end point.

	if (mapState[MapHeight - 3][MapWidth - 1] != TILE_DIRT)
		return map;
	que.push(Engine::Point(MapWidth - 1, MapHeight - 3));
	map[MapHeight - 3][MapWidth - 1] = 0;
	int dx[4] = { -1 , 0, 1, 0 }, dy[4] = { 0 , 1 , 0 , -1 };
	while (!que.empty()) {
		Engine::Point p = que.front();
		que.pop();
		if (map[p.y][p.x] != -1 && (p.x != MapWidth - 1 || p.y != MapHeight - 3)) continue;
		if (p.x != MapWidth - 1 || p.y != MapHeight - 3) {
			int res = -1;
			for (int i = 0; i < 4; ++i) {
				int to_x = p.x + dx[i], to_y = p.y + dy[i];
				if (to_x < 0 || to_x >= MapWidth || to_y < 0 || to_y > MapHeight - 3) continue;
				if (map[to_y][to_x] != -1) {
					res = (res == -1 ? map[to_y][to_x] + 1 : std::min(res, map[to_y][to_x] + 1));
				}
			}
			map[p.y][p.x] = res;
		}

		for (int i = 0; i < 4; ++i) {
			int to_x = p.x + dx[i], to_y = p.y + dy[i];
			if (to_x < 0 || to_x >= MapWidth || to_y < 0 || to_y > MapHeight - 3) continue;
			if (map[to_y][to_x] == -1 && mapState[to_y][to_x] == TILE_DIRT) {
				que.push(Engine::Point(to_x, to_y));
			}
		}
	}
	return map;
}
