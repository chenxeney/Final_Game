#ifndef SCOREBOARDSCENE_HPP_INCLUDED
#define SCOREBOARDSCENE_HPP_INCLUDED
#include <vector>
class ScoreboardScene final : public Engine::IScene {
private:
	float ticks;
public:
	explicit ScoreboardScene() = default;
	void Initialize() override;
	void Update(float deltaTime) override;
	void BackOnClickSelect(int stage);
	vector<int>ranking;
};

#endif // SCOREBOARDSCENE_HPP_INCLUDED
