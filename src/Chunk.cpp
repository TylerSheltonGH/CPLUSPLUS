#include "Chunk.h"
#include "ResourceManager.h"
#include "Log.h"

Chunk::Chunk(int ID, glm::vec2 Position, std::vector<Tile> Tiles) :
	m_ID(ID),
	m_Position(Position),
	m_ChunkTileData(Tiles),
	m_NeedsUpdate(false),
	m_NeedsRenderUpdate(false),
	m_NeedsInit(false)
{
	/*	//top left
	corners.push_back(m_Tiles[0].position);
	//top right
	corners.push_back(m_Tiles[CHUNK_SIZE - 1].position);
	//bottom left
	corners.push_back(m_Tiles[m_Tiles.size() - CHUNK_SIZE].position);
	//bottom right
	corners.push_back(m_Tiles[m_Tiles.size() - 1].position);*/

	//top left
	m_ChunkCornerData.push_back(m_ChunkTileData[0].position);

	//top right
	m_ChunkCornerData.push_back(m_ChunkTileData[CHUNK_SIZE - 1].position);

	//bottom left
	m_ChunkCornerData.push_back(m_ChunkTileData[m_ChunkTileData.size() - CHUNK_SIZE].position);

	//bottom right
	m_ChunkCornerData.push_back(m_ChunkTileData[m_ChunkTileData.size() - 1].position);

	//top left
	m_ChunkTileData[0].id = 5;
	//top right
	m_ChunkTileData[CHUNK_SIZE - 1].id = 6;
	//bottom left
	m_ChunkTileData[m_ChunkTileData.size() - CHUNK_SIZE].id = 5;
	//bottom right
	m_ChunkTileData[m_ChunkTileData.size() - 1].id = 5;

	m_SpriteBatch.Init();

	UpdateRender();

	/*for (int i = 0; i < Tiles.size(); i++) {
		VOID_CORE_INFO("Tile position: (X: {}, Y: {})", m_ChunkTileData[i].position.x, m_ChunkTileData[i].position.y);
	}*/
}

Chunk::~Chunk()
{
}

void Chunk::Init()
{
	m_SpriteBatch.Init();
	UpdateRender();
}

void Chunk::Update()
{
	if (m_NeedsInit) {
		Init();
	}

	if (m_NeedsUpdate) {
		m_NeedsUpdate = false;
	}
}

void Chunk::Render()
{
	if (m_NeedsRenderUpdate) {
		UpdateRender();
		m_NeedsRenderUpdate = false;
	}

	m_SpriteBatch.Render();
}

void Chunk::AddTileToSpriteBatch(int Tile)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 dest(m_ChunkTileData[Tile].position.x, m_ChunkTileData[Tile].position.y, TILE_SIZE, TILE_SIZE);

	//VOID_CORE_INFO("Tile position: (X: {}, Y: {})", m_ChunkTileData[Tile].position.x, m_ChunkTileData[Tile].position.y);

	switch (m_ChunkTileData[Tile].id) {
	case 0:
		m_SpriteBatch.Add(dest,
			uv,
			ResourceManager::GetTexture("Textures/Water.png").id,
			0.0f,
			Color());
		break;
	case 1:
		m_SpriteBatch.Add(dest,
			uv,
			ResourceManager::GetTexture("Textures/Dirt.png").id,
			0.0f,
			Color());
		break;
	case 2:
		m_SpriteBatch.Add(dest,
			uv,
			ResourceManager::GetTexture("Textures/Grass.png").id,
			0.0f,
			Color());
		break;
	case 3:
		m_SpriteBatch.Add(dest,
			uv,
			ResourceManager::GetTexture("Textures/Stone.png").id,
			0.0f,
			Color());
		break;
	case 5:
		m_SpriteBatch.Add(dest,
			uv,
			ResourceManager::GetTexture("Textures/Projectile.png").id,
			0.0f,
			Color());
		break;
	case 6:
		m_SpriteBatch.Add(dest,
			uv,
			ResourceManager::GetTexture("Textures/Test.png").id,
			0.0f,
			Color());
		break;
	default:
		VOID_CORE_WARN("Unrecognized symbol {} at (X: {}, Y: {})", m_ChunkTileData[Tile].id, m_ChunkTileData[Tile].position.x, m_ChunkTileData[Tile].position.y);
		break;
	}
}

int Chunk::GetTileID(glm::vec2 Position) const
{
	for (int i = 0; i < m_ChunkTileData.size(); i++) {
		if (m_ChunkTileData[i].position == Position) {
			return m_ChunkTileData[i].id;
		}
	}

	return -1;
}

void Chunk::SetTileID(int ID, glm::vec2 Position)
{
	for (int i = 0; i < m_ChunkTileData.size(); i++) {
		if (m_ChunkTileData[i].position == Position) {
			m_ChunkTileData[i].id = ID;
		}
	}
}

void Chunk::SetNeedsRenderUpdate(bool NeedsRenderUpdate)
{
	m_NeedsRenderUpdate = NeedsRenderUpdate;
}

void Chunk::SetNeedsUpdate(bool NeedsUpdate)
{
	m_NeedsUpdate = NeedsUpdate;
}

void Chunk::SetChunkTileData(std::vector<Tile>& TileData)
{
	m_ChunkTileData.clear();
	m_ChunkTileData = TileData;
}

void Chunk::UpdateRender()
{
	m_SpriteBatch.Begin();
	for (int i = 0; i < m_ChunkTileData.size(); i++) {
		AddTileToSpriteBatch(i);
	}
	m_SpriteBatch.End();
}