#include "MapEditor.h"
#include "SDL_mouse.h"
#include "SDL_keycode.h"
#include "IOManager.h"
#include "Log.h"

MapEditor::MapEditor() :
	m_Camera(nullptr),
	m_Input(nullptr),
	m_CurrentID(0),
	m_BrushSize(0.0f)
{
}

MapEditor::~MapEditor()
{
}

void MapEditor::LoadMap(int ID, std::string Map)
{
	m_OriginalMapChunkData.clear();
	m_ModifiedMapChunkData.clear();

	m_Map.Load(ID, Map);

	m_OriginalMapChunkData = m_Map.GetMapChunkData();

	m_ModifiedMapChunkData = m_Map.GetMapChunkData();
}

void MapEditor::PollEvents()
{
	if (m_Input->IsKeyPressed(SDL_BUTTON_LEFT)) {
		EditMap();
	}
	if (m_Input->IsKeyPressed(SDLK_0)) {
		m_CurrentID = 0;
	}
	if (m_Input->IsKeyPressed(SDLK_1)) {
		m_CurrentID = 1;
	}
	if (m_Input->IsKeyPressed(SDLK_2)) {
		m_CurrentID = 2;
	}
	if (m_Input->IsKeyPressed(SDLK_3)) {
		m_CurrentID = 3;
	}
}

void MapEditor::Update()
{
	//m_Map.Update(0.0f);

	for (int i = 0; i < m_ModifiedMapChunkData.size(); i++) {
		m_ModifiedMapChunkData[i].Update();
	}
}

void MapEditor::Render()
{
	//m_Map.Render();

	for (int i = 0; i < m_ModifiedMapChunkData.size(); i++) {
		m_ModifiedMapChunkData[i].Render();
	}
}

void MapEditor::GetApplicationData(Input* Input, Camera* Camera)
{
	m_Input = Input;
	m_Camera = Camera;
}

void MapEditor::EditMap()
{
	glm::vec2 mousePosition = m_Camera->ConvertScreenToWorld(m_Input->GetMousePosition());

	VOID_CORE_INFO("Mouse position: (X: {}, Y: {})", mousePosition.x, mousePosition.y);

	/*for (int i = 0; i < m_ModifiedMapChunkData.size(); i++) {
		if (mousePosition.x < m_ModifiedMapChunkData[i].position.x + TILE_SIZE &&
			mousePosition.x + m_BrushSize > m_ModifiedMapChunkData[i].position.x &&
			mousePosition.y < m_ModifiedMapChunkData[i].position.y + TILE_SIZE &&
			mousePosition.y + m_BrushSize > m_ModifiedMapChunkData[i].position.y) {

		}
	}*/

	//VOID_CORE_INFO("LEFT MOUSE BUTTON");

	for (int i = 0; i < m_ModifiedMapChunkData.size(); i++) {
		if (mousePosition.x < m_ModifiedMapChunkData[i].GetPosition().x + TILE_SIZE * (CHUNK_SIZE / 2) &&
			mousePosition.x + m_BrushSize > m_ModifiedMapChunkData[i].GetPosition().x - TILE_SIZE * (CHUNK_SIZE / 2) &&
			mousePosition.y < m_ModifiedMapChunkData[i].GetPosition().y + TILE_SIZE * (CHUNK_SIZE / 2) &&
			mousePosition.y + m_BrushSize > m_ModifiedMapChunkData[i].GetPosition().y - TILE_SIZE * (CHUNK_SIZE / 2)) {

			VOID_CORE_INFO("CHUNK CLICKED");

			std::vector<Tile> tileData = m_ModifiedMapChunkData[i].GetChunkTileData();

			for (int j = 0; j < tileData.size(); j++) {

				if (mousePosition.x < tileData[i].position.x + TILE_SIZE &&
					mousePosition.x + m_BrushSize > tileData[i].position.x &&
					mousePosition.y < tileData[i].position.y + TILE_SIZE &&
					mousePosition.y + m_BrushSize > tileData[i].position.y) {

					if (tileData[i].id != m_CurrentID) {
						tileData[i].id = m_CurrentID;

						m_ModifiedMapChunkData[i].SetChunkTileData(tileData);

						m_ModifiedMapChunkData[i].SetNeedsRenderUpdate(true);
					}

					VOID_CORE_INFO("TILE CLICKED");
				}
			}
		}
	}
}

void MapEditor::Save()
{
	IOManager::WriteStringVectorToFile("Maps/test.data", m_Map.GetMapStringData());
}

void MapEditor::Undo()
{
	
}

void MapEditor::UndoAll()
{
}

void MapEditor::Redo()
{
}

void MapEditor::RedoAll()
{
}