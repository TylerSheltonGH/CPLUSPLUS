#include "SpriteBatch.h"

#include <algorithm>

SpriteBatch::SpriteBatch() : m_VBO(0), m_VAO(0), m_SortType(GlyphSortType::NONE)
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::Init()
{
	CreateVertexArray();
}

void SpriteBatch::Begin(GlyphSortType SortType)
{
	m_SortType = SortType;
	m_RenderBatches.clear();

	for (int i = 0; i < m_Glyphs.size(); i++) {
		delete m_Glyphs[i];
	}

	m_Glyphs.clear();
}

void SpriteBatch::End()
{
	SortGlyphs();
	CreateRenderBatches();
}

void SpriteBatch::Add(const glm::vec4& Dest, const glm::vec4& UV, unsigned int Texture, float Depth, const Color& Color)
{
	Glyph* glyph = new Glyph;
	glyph->texture = Texture;
	glyph->depth = Depth;

	glyph->topLeft.color = Color;
	glyph->topLeft.SetPosition(Dest.x, Dest.y + Dest.w);
	glyph->topLeft.SetUV(UV.x, UV.y + UV.w);

	glyph->bottomLeft.color = Color;
	glyph->bottomLeft.SetPosition(Dest.x, Dest.y);
	glyph->bottomLeft.SetUV(UV.x, UV.y);

	glyph->bottomRight.color = Color;
	glyph->bottomRight.SetPosition(Dest.x + Dest.z, Dest.y);
	glyph->bottomRight.SetUV(UV.x + UV.z, UV.y);

	glyph->topRight.color = Color;
	glyph->topRight.SetPosition(Dest.x + Dest.z, Dest.y + Dest.w);
	glyph->topRight.SetUV(UV.x + UV.z, UV.y + UV.w);

	m_Glyphs.push_back(glyph);
}

void SpriteBatch::Render()
{
	glBindVertexArray(m_VAO);

	for (int i = 0; i < m_RenderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, m_RenderBatches[i].texture);

		glDrawArrays(GL_TRIANGLES, m_RenderBatches[i].offset, m_RenderBatches[i].vertices);
	}

	glBindVertexArray(0);
}

void SpriteBatch::CreateRenderBatches()
{
	std::vector<Vertex> vertices;

	vertices.resize(m_Glyphs.size() * 6);

	if (m_Glyphs.empty()) {
		return;
	}

	int offset = 0;
	int cv = 0; //current vertex
	m_RenderBatches.emplace_back(offset, 6, m_Glyphs[0]->texture);

	vertices[cv++] = m_Glyphs[0]->topLeft;
	vertices[cv++] = m_Glyphs[0]->bottomLeft;
	vertices[cv++] = m_Glyphs[0]->bottomRight;
	vertices[cv++] = m_Glyphs[0]->bottomRight;
	vertices[cv++] = m_Glyphs[0]->topRight;
	vertices[cv++] = m_Glyphs[0]->topLeft;

	offset += 6;

	//cg = current glyph
	for (int cg = 1; cg < m_Glyphs.size(); cg++) {
		if (m_Glyphs[cg]->texture != m_Glyphs[cg - 1]->texture) {
			m_RenderBatches.emplace_back(offset, 6, m_Glyphs[cg]->texture);
		}
		else {
			m_RenderBatches.back().vertices += 6;
		}

		vertices[cv++] = m_Glyphs[cg]->topLeft;
		vertices[cv++] = m_Glyphs[cg]->bottomLeft;
		vertices[cv++] = m_Glyphs[cg]->bottomRight;
		vertices[cv++] = m_Glyphs[cg]->bottomRight;
		vertices[cv++] = m_Glyphs[cg]->topRight;
		vertices[cv++] = m_Glyphs[cg]->topLeft;

		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::CreateVertexArray()
{
	if (m_VAO == 0) {
		glGenVertexArrays(1, &m_VAO);
	}
	glBindVertexArray(m_VAO);

	if (m_VBO == 0) {
		glGenBuffers(1, &m_VBO);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void SpriteBatch::SortGlyphs()
{
	switch (m_SortType) {
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), CompareBackToFront);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), CompareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), CompareTexture);
		break;
	}
}

bool SpriteBatch::CompareFrontToBack(Glyph* A, Glyph* B)
{
	return (A->depth < B->depth);
}

bool SpriteBatch::CompareBackToFront(Glyph* A, Glyph* B)
{
	return (A->depth > B->depth);
}

bool SpriteBatch::CompareTexture(Glyph* A, Glyph* B)
{
	return (A->texture < B->texture);
}