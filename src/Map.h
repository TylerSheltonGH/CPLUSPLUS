#pragma once
#include <string>
#include <vector>
#include "Tile.h"
#include "SpriteBatch.h"
#include "Chunk.h"
#include <thread>
#include <future>

class Map
{
public:
	Map();
	~Map();

	void Load(int ID = -1, std::string Name = "NULL");

	void Init();

	void InitRender();

	void CreateChunks();

	void Update(float DeltaTime);

	void Render();

	char GetMapStringTile(glm::vec2 Position) const { return m_MapStringData[Position.y][Position.x]; }
	void SetMapStringTile(glm::vec2 Position, char Tile);

	std::vector<Tile> GetMapTileData() const { return m_MapTileData; }
	void SetMapTileData(std::vector<Tile> MapTileData);

	int GetTileID(glm::vec2 Position);
	void SetTileID(int ID, glm::vec2 Position);

	int GetID() const { return m_ID; }
	void SetID(int ID);

	std::string GetName() const { return m_Name; }
	void SetName(std::string Name);

	std::vector<std::string> GetMapStringData() const { return m_MapStringData; }
	void SetMapStringData(std::vector<std::string> MapStringData);

	std::vector<Chunk> GetMapChunkData() const { return m_MapChunkData; }
	void SetMapChunkData(std::vector<Chunk> MapChunkData);

private:
	void AddTileToSpriteBatch(int Tile);

private:
	int m_ID;
	std::string m_Name;
	std::vector<std::string> m_MapStringData;

	std::vector<Chunk> m_MapChunkData;

	std::vector<Tile> m_MapTileData;

	std::vector<std::vector<Tile>> m_MapTileData2D;

	SpriteBatch m_SpriteBatch;

	std::vector<std::future<void>> m_Futures;
};