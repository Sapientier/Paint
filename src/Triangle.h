#pragma once
#include "Figure.h"
#include "Line.h"
#include <vector>
using namespace std;

class CTriangle : public CFigure {
public:
	CTriangle();
	~CTriangle();
    void firstTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
    void secondTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
	void display();
};