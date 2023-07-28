#pragma once
#include "GL/glew.h"

struct Position {
	float x, y;
};

struct Color {
	Color(unsigned char Red = 255, unsigned char Green = 255, unsigned char Blue = 255, unsigned char Alpha = 255) :
		r(Red),
		g(Green),
		b(Blue),
		a(Alpha)
	{

	}

	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	void SetColor(unsigned char Red, unsigned char Green, unsigned char Blue, unsigned char Alpha) {
		r = Red;
		g = Green;
		b = Blue;
		a = Alpha;
	}
};

struct UV {
	float u, v;
};

struct Vertex {
	Position position;
	Color color;
	UV uv;

	void SetPosition(float X, float Y) {
		position.x = X;
		position.y = Y;
	}

	void SetColor(unsigned char Red, unsigned char Green, unsigned char Blue, unsigned char Alpha) {
		color.r = Red;
		color.g = Green;
		color.b = Blue;
		color.a = Alpha;
	}

	void SetUV(float U, float V) {
		uv.u = U;
		uv.v = V;
	}
};