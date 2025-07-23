#pragma once
#include <vector>
#include <iostream>
#include "Vertex.h"
class TerrainMesh
{
public:
	int lod = 4;
	float gridSize = 65;
	float size = 65;

	std::vector<Vertex> vertices;
	std::vector<uint16_t>indices;

	void CreateMesh();
	void CreateCenterMesh();
	void CreateDonutMesh(int startingIndex, float scale, int level);

	void AddTile(uint16_t index, int offset, std::vector<uint16_t>& indices);
};

