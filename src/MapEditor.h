#pragma once
#include "Map.h"
#include "Camera.h"
#include "Input.h"
#include "Chunk.h"

class MapEditor
{
public:
	MapEditor();

	~MapEditor();

	void LoadMap(int ID = -1, std::string Map = "NULL");

	void PollEvents();

	void Update();

	void Render();

	void GetApplicationData(Input* Input, Camera* Camera);

private:
	void EditMap();

	void Save();
	
	void Undo();

	void UndoAll();

	void Redo();

	void RedoAll();

private:
	Camera* m_Camera;
	Input* m_Input;

	int m_CurrentID;

	float m_BrushSize;

	Map m_Map;

	std::vector<Chunk> m_OriginalMapChunkData;
	
	std::vector<Chunk> m_ModifiedMapChunkData;

	std::vector<Chunk> m_UndoMapChunkData;
};