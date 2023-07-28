#include "Map.h"
#include "IOManager.h"
#include "Log.h"
#include "ResourceManager.h"

Map::Map() :
	m_ID(-1),
	m_Name("NULL")
{
}

Map::~Map()
{
}

void Map::Load(int ID, std::string Name)
{
	m_MapStringData.clear();

	m_MapTileData.clear();

	m_ID = ID;
	m_Name = Name;

	std::string path = "Maps/" + m_Name + ".data";

	if (IOManager::ReadFileToStringVector(path, m_MapStringData)) {
		m_SpriteBatch.Init();
		Init();
		InitRender();
	}
	else {
		VOID_CORE_CRITICAL("Failed to load map.");
	}
}

void Map::Init()
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	std::vector<Tile> tmpMapTileData;

	for (int y = 0; y < m_MapStringData.size(); y++) {
		for (int x = 0; x < m_MapStringData[y].size(); x++) {
			char tile = m_MapStringData[y][x];

			int flipy = y * TILE_SIZE * 2;

			glm::vec4 dest(x * TILE_SIZE, y * TILE_SIZE - flipy, TILE_SIZE, TILE_SIZE);
			glm::vec2 position(x * TILE_SIZE, y * TILE_SIZE - flipy);

			int id = tile - '0';

			m_MapTileData.push_back(Tile(id, position));

			tmpMapTileData.push_back(Tile(id, position));
		}

		m_MapTileData2D.push_back(tmpMapTileData);
		tmpMapTileData.clear();
	}

	//m_Futures.push_back(std::async(std::launch::async, &Map::CreateChunks, this));
	CreateChunks();
}

void Map::InitRender()
{
	m_SpriteBatch.Begin();

	for (int i = 0; i < m_MapTileData.size(); i++) {

		AddTileToSpriteBatch(i);
	}

	m_SpriteBatch.End();
}

void Map::CreateChunks()
{
	m_MapChunkData.clear();

	VOID_CORE_INFO("Creating chunks...");

	std::vector<Tile> chunk;

	int totalChunks = m_MapTileData.size() / TILES_IN_CHUNK;

	int chunkOffsetX = 1, chunkOffsetY = 1;

	int mapSizeX = m_MapStringData[0].size();
	int mapSizeY = m_MapStringData.size();

	const int chunksPerRow = mapSizeX / CHUNK_SIZE;

	for (int i = 0; i < totalChunks; i++) {

		for (int y = (CHUNK_SIZE * chunkOffsetY) - CHUNK_SIZE; y < CHUNK_SIZE * chunkOffsetY; y++) {
			for (int x = (CHUNK_SIZE * chunkOffsetX) - CHUNK_SIZE; x < CHUNK_SIZE * chunkOffsetX; x++) {
				for (int j = 0; j < m_MapTileData.size(); j++) {
					int flipy = y * TILE_SIZE * 2;

					glm::vec2 position = glm::vec2(x * TILE_SIZE, y * TILE_SIZE - flipy);

					if (m_MapTileData[j].position == position) {
						chunk.push_back(m_MapTileData[j]);
					}
				}
			}
		}

		//m_ChunkTileData[m_ChunkTileData.size() - 1]
		glm::vec2 chunkPosition = glm::vec2(chunk[chunk.size() - 1].position.x / 2, chunk[chunk.size() - 1].position.y / 2);

		VOID_CORE_INFO("Chunk position: (X: {}, Y: {})", chunkPosition.x, chunkPosition.y);

		m_MapChunkData.push_back(Chunk(i, chunkPosition, chunk));

		VOID_CORE_INFO("Chunk(s) created: {}", std::to_string(m_MapChunkData.size()));

		chunk.clear();

		if (chunkOffsetX >= chunksPerRow) {
			chunkOffsetY++;
			chunkOffsetX = 1;
		}
		else {
			chunkOffsetX++;
		}
	}
}

void Map::Update(float DeltaTime)
{
	for (int i = 0; i < m_MapChunkData.size(); i++) {
		m_MapChunkData[i].Update();
	}
}

void Map::Render()
{
	for (int i = 0; i < m_MapChunkData.size(); i++) {
		m_MapChunkData[i].Render();
	}
}

void Map::SetMapStringTile(glm::vec2 Position, char Tile)
{
	m_MapStringData[Position.y][Position.x] = Tile;
}

void Map::SetMapTileData(std::vector<Tile> MapTileData)
{
	m_MapTileData = MapTileData;
}

int Map::GetTileID(glm::vec2 Position)
{
	for (int i = 0; i < m_MapTileData.size(); i++) {
		if (m_MapTileData[i].position == Position) {
			return m_MapTileData[i].id;
		}
	}

	return -1;
}

void Map::SetTileID(int ID, glm::vec2 Position)
{
	for (int i = 0; i < m_MapTileData.size(); i++) {
		if (m_MapTileData[i].position == Position) {
			m_MapTileData[i].id = ID;
		}
	}
}

void Map::SetID(int ID)
{
	m_ID = ID;
}

void Map::SetName(std::string Name)
{
	m_Name = Name;
}

void Map::SetMapStringData(std::vector<std::string> MapStringData)
{
	m_MapStringData = MapStringData;
}

void Map::SetMapChunkData(std::vector<Chunk> MapChunkData)
{
	m_MapChunkData = MapChunkData;
}

void Map::AddTileToSpriteBatch(int Tile)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 dest(m_MapTileData[Tile].position.x, m_MapTileData[Tile].position.y, TILE_SIZE, TILE_SIZE);

	switch (m_MapTileData[Tile].id) {
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
	default:
		VOID_CORE_WARN("Unrecognized symbol {} at (X: {}, Y: {})", m_MapTileData[Tile].id, m_MapTileData[Tile].position.x, m_MapTileData[Tile].position.y);
		break;
	}
}