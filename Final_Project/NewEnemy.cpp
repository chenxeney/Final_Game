#include <string>

#include "NewEnemy.hpp"

NewEnemy::NewEnemy(int x, int y) : Enemy("play/enemy-4.png", x, y, 10, 50, 5, 5) {
	// TODO 2 (6/8): You can imitate the 2 files: 'SoldierEnemy.hpp', 'SoldierEnemy.cpp' to create a new enemy.
    NewEnemy::score = 20;
}
