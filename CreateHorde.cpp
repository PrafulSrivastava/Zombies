#include "ZombieArena.hpp"
#include "Configuration.hpp"
#include <vector>

ZombieType getZombieType(int num) {
	switch (num) {
	case 0: 
		return ZombieType::BLOATER;
	case 1:
		return ZombieType::CHASER;
	case 2:
		return ZombieType::CRAWLER;
	}
	return ZombieType::NONE;
}

vector<Zombie*> createHorde(int numZombies, IntRect arena) {
	vector<Zombie*> zombies(numZombies);
	int maxY = arena.height - Configs::ZOMBIE_SPAWN_ADJUSTMENT;
	int maxX = arena.width - Configs::ZOMBIE_SPAWN_ADJUSTMENT;
	int minY = arena.top + Configs::ZOMBIE_SPAWN_ADJUSTMENT;
	int minX = arena.left + Configs::ZOMBIE_SPAWN_ADJUSTMENT;

	for(int i = 0; i < numZombies; i++) {
		Zombie* temp = new Zombie();
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x = 0, y = 0;
		switch (side) {
		case 0://L
			x = minX;
			y = (rand() % maxY) + minY;
			break;
		case 1://R
			x = maxX;
			y = (rand() % maxY) + minY;
			break;
		case 2://U
			y = minY;
			x = (rand() % maxX) + minX;
			break;
		case 3://D
			y = maxY;
			x = (rand() % maxX) + minX;
			break;
		}
		zombies[i] = temp;
		srand((int)time(0) * i * 2);
		ZombieType type = getZombieType(rand() % 3);
		zombies[i]->spawn(x, y, type, i);
	}
	return zombies;
}