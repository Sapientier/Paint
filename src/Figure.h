#pragma once
#include "../headers/glfw3.h"

enum FigureType
{
	NONE,
	LINE,
	QUAD,
	CIRCLE,
	ELIPSE,
	TRIANGLE
};

class CFigure
{
protected:
	float **mVertices, mColor[3];
	int mType;
	bool box;

public:
	CFigure();
	virtual ~CFigure();
	void setVertex(int id, float x, float y);
	void setColor(float r, float g, float b);
	void setBox(int valor);
	virtual void display() = 0;
	int getType();
	float* getVertex(int id);
	float* getColor();
	bool getBox();
};