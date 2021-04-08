#include "ZombieArena.hpp"
#include "Configuration.hpp"

int createBackground(VertexArray& rVA, IntRect arena) {
	int worldWidth = arena.width / Configs::TILE_SIZE;
	int worldHeight = arena.height / Configs::TILE_SIZE;

	rVA.setPrimitiveType(Quads);
	rVA.resize(worldWidth * worldHeight * Configs::VERTS_IN_QUAD);
	int currentVertex = 0;

	for (int w = 0; w < worldWidth; w++) {
		for (int h = 0; h < worldHeight; h++) {
			rVA[currentVertex + 0].position = Vector2f(w * Configs::TILE_SIZE, h * Configs::TILE_SIZE);
			rVA[currentVertex + 1].position = Vector2f((w * Configs::TILE_SIZE) + Configs::TILE_SIZE, h * Configs::TILE_SIZE);
			rVA[currentVertex + 2].position = Vector2f((w * Configs::TILE_SIZE) + Configs::TILE_SIZE, (h * Configs::TILE_SIZE) + Configs::TILE_SIZE);
			rVA[currentVertex + 3].position = Vector2f(w * Configs::TILE_SIZE, (h * Configs::TILE_SIZE) + Configs::TILE_SIZE);

			if ((h == 0 || h == worldHeight - 1) || (w == 0 || w == worldWidth - 1)) {
				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + Configs::TILE_SIZE * Configs::TILE_TYPES);
				rVA[currentVertex + 1].texCoords = Vector2f(Configs::TILE_SIZE, 0 + Configs::TILE_SIZE * Configs::TILE_TYPES);
				rVA[currentVertex + 2].texCoords = Vector2f(Configs::TILE_SIZE, Configs::TILE_SIZE + Configs::TILE_SIZE * Configs::TILE_TYPES);
				rVA[currentVertex + 3].texCoords = Vector2f(0, Configs::TILE_SIZE + Configs::TILE_SIZE * Configs::TILE_TYPES);
			}
			else {
				srand((int)time(0) + h * w - h);
				int mudOrGrass = rand() % Configs::TILE_TYPES;
				int vertexOffset = mudOrGrass * Configs::TILE_SIZE;
				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + vertexOffset);
				rVA[currentVertex + 1].texCoords = Vector2f(Configs::TILE_SIZE, 0 + vertexOffset);
				rVA[currentVertex + 2].texCoords = Vector2f(Configs::TILE_SIZE, Configs::TILE_SIZE + vertexOffset);
				rVA[currentVertex + 3].texCoords = Vector2f(0, Configs::TILE_SIZE + vertexOffset);
			}
			currentVertex += Configs::VERTS_IN_QUAD;

		}
	}

	return Configs::TILE_SIZE;
}