#pragma once

#include "Tile.h"
#include <vector>
#include "SpriteBatch.h"

const int CHUNK_SIZE = 16; // DEFAULT: 8
const int TILES_IN_CHUNK = pow(CHUNK_SIZE, 2);

class Chunk
{
public:
	Chunk(int ID = -1, glm::vec2 Position = glm::vec2(0.0f, 0.0f), std::vector<Tile> Tiles = {});

	~Chunk();

	void Init();

	void Update();

	void Render();

	void AddTileToSpriteBatch(int Tile);

	int GetTileID(glm::vec2 Position) const;
	void SetTileID(int ID, glm::vec2 Position);

	glm::vec2 GetPosition() const { return m_Position; }

	bool GetNeedsRenderUpdate() const { return m_NeedsRenderUpdate; }
	void SetNeedsRenderUpdate(bool NeedsRenderUpdate);

	bool GetNeedsUpdate() const { return m_NeedsUpdate; }
	void SetNeedsUpdate(bool NeedsUpdate);

	std::vector<Tile> GetChunkTileData() const { return m_ChunkTileData; }
	void SetChunkTileData(std::vector<Tile>& TileData);

private:
	void UpdateRender();

private:
	int m_ID;
	glm::vec2 m_Position;
	std::vector<Tile> m_ChunkTileData;

	bool m_NeedsUpdate;
	bool m_NeedsRenderUpdate;

	bool m_NeedsInit;

	SpriteBatch m_SpriteBatch;

	std::vector<glm::vec2> m_ChunkCornerData;
};