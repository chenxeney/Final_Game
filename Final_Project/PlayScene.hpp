#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <list>
#include <utility>
#include <vector>
#include <string>

#include "IScene.hpp"
#include "Point.hpp"
using namespace std;
class Turret;
namespace Engine {
	class Group;
	class Image;
	class Label;
	class Sprite;
}  // namespace Engine

class PlayScene final : public Engine::IScene {
private:
	enum TileType {
		TILE_DIRT,
		TILE_FLOOR,
		TILE_OCCUPIED,
	};
protected:
	int Point;
public:
	static bool DebugMode;
	static const std::vector<Engine::Point> directions;
	static const int MapWidth, MapHeight;
	static const int BlockSize;
	static const Engine::Point SpawnGridPoint;
	static const Engine::Point EndGridPoint;
	static const std::vector<int> code;
	int MapId;
	float ticks;
	// Map tiles.
	Group* TileMapGroup;
	Group* GroundEffectGroup;
	Group* DebugIndicatorGroup;
	Group* BulletGroup;
	Group* TowerGroup;
	Group* EnemyGroup;
	Group* EffectGroup;
	Group* UIGroup;
	Group* ArmyGroup;
	Engine::Label* UIMoney;
	Engine::Label* UILives;
	Engine::Label* UIScore;
	Engine::Image* imgTarget;
	Turret* preview;
	Turret* InitialTurret;
	std::vector<std::vector<TileType>> mapState;
	std::vector<std::vector<int>> mapDistance;
	std::list<std::pair<int, float>> enemyWaveData;
	std::list<int> keyStrokes;
	static Engine::Point GetClientSize();
	explicit PlayScene() = default;
	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;
	void Hit();
	int GetMoney() const;
	void EarnMoney(int money);
	void EarnScore(int score);
	void ReadMap();
	void AssignArmy1();
	void AssignArmy2();
	void AssignArmy3();
	void OnMouseDown1(int button, int mx, int my);
    void OnMouseDown2(int button, int mx, int my);
    void OnMouseDown3(int button, int mx, int my);
	void ReadEnemyWave();
	void ConstructUI();
	void AddBackgroundThread(string background_path, int x, int y);
	void UIBtnClicked(int id);
	bool CheckSpaceValid(int x, int y);
	bool Down;
	std::vector<std::vector<int>> CalculateBFSDistance();
	int money = 150;
	int lives = 5;
    int SpeedMult = 5;
    int score = 0;
	// void ModifyReadMapTiles();
};
#endif // PLAYSCENE_HPP
