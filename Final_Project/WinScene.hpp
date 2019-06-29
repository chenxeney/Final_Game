#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include "IScene.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"

class WinScene final : public Engine::IScene {
private:
	float ticks;
public:
	explicit WinScene() = default;
	void Initialize() override;
	void Update(float deltaTime) override;
	void BackOnClickSelect(int stage);
	void BackOnClickScoreboard();
};

#endif // WINSCENE_HPP
