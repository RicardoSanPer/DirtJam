#include "TerrainMesh.h"

void TerrainMesh::CreateMesh()
{
	CreateCenterMesh();
	float scale = 1.0f;
	for (int i = 0; i < lod; i++)
	{
		CreateDonutMesh(vertices.size(), scale, i);
		scale *= 2;
	}
}


void TerrainMesh::CreateCenterMesh()
{
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			float x = (((float)i / (gridSize - 1)) - 0.5f) * size;
			float y = (((float)j / (gridSize - 1)) - 0.5f) * size;
			vertices.push_back({
				
				{x, y},
				{(float)j / gridSize, (float)i / gridSize, 1.0f }, 
				{x / size, y/size}
				});
		}
	}

	for (int i = 0; i < gridSize - 1; i++)
	{
		for (int j = 0; j < gridSize - 1; j++)
		{
			int currIndex = i + j * gridSize;
			indices.push_back(currIndex);
			indices.push_back(currIndex + gridSize);
			indices.push_back(currIndex + gridSize + 1);
			/*indices.push_back(currIndex);
			indices.push_back(currIndex + gridSize + 1);
			indices.push_back(currIndex + 1);*/
		}
	}
}

void TerrainMesh::CreateDonutMesh(int startingIndex, float scale, int level)
{
	int ignore = ((float)(gridSize - 1) / 4.0f);
	float val = (float)(lod - level) / lod;
	//Leftmost part
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (j > ignore && j < gridSize - ignore - 1 && i > ignore && i < gridSize - ignore - 1)
			{
				continue;
			}
			float x = (((float)i / (gridSize - 1)) - 0.5f) * size * 2 * scale;
			float y = (((float)j / (gridSize - 1)) - 0.5f) * size * 2 * scale;
			vertices.push_back({
				{x, y},
				{ val, val, val }, 
				{x / size, y / size}
				});
		}
	}

	int startingOffset = startingIndex;
	//Indices of leftmost portion
	for (int i = 0; i < gridSize - 1; i++)
	{
		for (int j = 0; j < ignore; j++)
		{
			int currIndex = startingOffset + i + j * gridSize;
			AddTile(currIndex, gridSize, indices);
		}
	}
	//Indices of upper left "hole"
	for (int i = 0; i < ignore; i++)
	{
		int currIndex = startingOffset + (gridSize * ignore) + i;

		AddTile(currIndex, gridSize, indices);
	}
	startingOffset = (gridSize * ignore) + (gridSize - ignore - 1) + startingIndex;
	int offset = (ignore + 1) * 2;

	//lower left "hole"
	for (int i = 0; i < ignore; i++)
	{
		int currIndex = startingOffset + i;
		
		AddTile(currIndex, offset, indices);
	}
	startingOffset = (gridSize * (ignore + 1)) + startingIndex;

	//"hole"
	for (int j = 0; j < (ignore - 1) * 2; j++)
	{
		for (int i = 0; i <= ignore * 2; i++)
		{
			if (i == ignore)
			{
				continue;
			}
			int currIndex = startingOffset + i + (offset * j);
			AddTile(currIndex, offset, indices);
		}
	}

	startingOffset = (gridSize * (ignore + 1)) + (ignore * ignore * 4) - 4 + startingIndex;

	//top right hole connection
	for (int i = 0; i < ignore; i++)
	{
		int currIndex = startingOffset + i;

		AddTile(currIndex, offset, indices);
	}
	//lower right hole
	startingOffset = (gridSize * (ignore + 1)) + (ignore * ignore * 4) - 4 + ignore + 1 + startingIndex;

	for (int i = 0; i < ignore; i++)
	{
		int currIndex = startingOffset + i;
		AddTile(currIndex, gridSize, indices);
	}

	//rightmost section
	startingOffset = (gridSize * gridSize) - (ignore * ignore * 4) - (gridSize * ignore) - 2 + startingIndex;
	for (int i = 0; i < gridSize - 1; i++)
	{
		for (int j = 0; j < ignore; j++)
		{
			int currentIndex = startingOffset + i + (j * gridSize);
			AddTile(currentIndex, gridSize, indices);
		}
	}
}

void TerrainMesh::AddTile(uint16_t index, int offset, std::vector<uint16_t>& indices)
{
	indices.push_back(index);
	indices.push_back(index + offset);
	indices.push_back(index + offset + 1);
	indices.push_back(index);
	indices.push_back(index + offset + 1);
	indices.push_back(index + 1);
}
