#pragma once
#include "Line.h"
#include <vector>
using namespace std;

class CCurve : public CFigure 
{
public:
	CCurve();
	~CCurve();
	vector<CPoint *> arrayPoints;
	float color[3];
	double maxX;
	double maxY;
	double minX;
	double minY;
	void display();
	void setPoints(vector <CPoint *> puntos);
	vector <CPoint *> getPoints();
	CPoint* getCasteljauPoint(int r, int i, double t, vector<CPoint *> points);
};