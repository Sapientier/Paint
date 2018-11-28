#pragma once
#include "Figure.h"
#include "Line.h"

class CQuad : public CFigure
{
public:
	CQuad();
	~CQuad();
	void display();
	void drawBoundingBox(int x0, int y0, int x1, int y1);
};

