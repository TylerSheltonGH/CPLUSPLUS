#pragma once
#include "Vertex.h"
#include <glm.hpp>
#include <vector>

enum class GlyphSortType{NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE};

struct Glyph {
	unsigned int texture;
	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};

class RenderBatch {
public:
	RenderBatch(unsigned int Offset, unsigned int Vertices, unsigned int Texture) : offset(Offset), vertices(Vertices), texture(Texture) {}

	unsigned int offset;
	unsigned int vertices;
	unsigned int texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void Init();

	void Begin(GlyphSortType SortType = GlyphSortType::TEXTURE);

	void End();

	void Add(const glm::vec4& Dest, const glm::vec4& UV, unsigned int Texture, float Depth, const Color& Color);

	void Render();

private:
	void CreateRenderBatches();
	void CreateVertexArray();
	void SortGlyphs();

	static bool CompareFrontToBack(Glyph* A, Glyph* B);
	static bool CompareBackToFront(Glyph* A, Glyph* B);
	static bool CompareTexture(Glyph* A, Glyph* B);

	unsigned int m_VBO;
	unsigned int m_VAO;

	GlyphSortType m_SortType;

	std::vector<Glyph*> m_Glyphs;
	std::vector<RenderBatch> m_RenderBatches;
};

