#pragma once
#include "Point.h"

class CLine : public CFigure
{
public:
	CLine();
	~CLine();
	void display();
	void horizontalLine(int xMin, int yMin, int xMax);
};

