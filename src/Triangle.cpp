#include "Triangle.h"
#include <algorithm>

CTriangle::CTriangle() 
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = TRIANGLE;
}

CTriangle::~CTriangle() 
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CTriangle::firstTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
	if (y0 == y1);
	else if (y0 == y2) swap(x2, x1), swap(y2, y1);
	else if (y1 == y2) swap(x0, x2), swap(y0, y2);
	else return;

	if (x1 < x0) swap(x1, x0), swap(y1, y0);
	else if (x1 == x0) return;

	float dxy_left = (x2 - x0)*1.0 / (y2 - y0);
	float dxy_right = (x1 - x2)*1.0 / (y1 - y2);
	float xs = x0, xe = x1;

	CLine linea;
	linea.setColor(getColor()[0], getColor()[1], getColor()[2]);

	for (int y = y0; y < y2; y++) {
		linea.setVertex(0, xs + 1, y);
		linea.setVertex(1, xe, y);
		linea.display();

		xs += dxy_left;
		xe += dxy_right;
	}
}

void CTriangle::secondTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
	if (y2 == y1);
	else if (y2 == y0) swap(x0, x1), swap(y0, y1);
	else if (y0 == y1) swap(x0, x2), swap(y0, y2);
	else return;

	if (x1 < x2) swap(x1, x2);
	else if (x1 == x2) return;

	float dxy_left = (x2 - x0)*1.0 / (y2 - y0);
	float dxy_right = (x1 - x0)*1.0 / (y1 - y0);
	float xs = x0, xe = x0;
	CLine linea;
	linea.setColor(getColor()[0], getColor()[1], getColor()[2]);

	for (int y = y0; y < y2; y++) {
		linea.setVertex(0, xs + 1, y);
		linea.setVertex(1, xe, y);
		linea.display();

		xs += dxy_left;
		xe += dxy_right;
	}
}

void CTriangle::display() {
	int x0 = mVertices[0][0];
	int y0 = mVertices[0][1];
	int x1 = mVertices[1][0];
	int y1 = mVertices[1][1];
	int x2 = 0;
	int y2 = 0;

	if (y0 > y1)swap(x0, x1), swap(y0, y1);
	if (y0 > y2)swap(x0, x2), swap(y0, y2);
	if (y1 > y2)swap(y1, y2), swap(x1, x2);
	if (y0 == y1) firstTriangle(x0, y0, x1, y1, x2, y2);
	else if (y1 == y2) secondTriangle(x0, y0, x1, y1, x2, y2);
	else {
		float k = 1.0*(x2 - x0) / (y2 - y0);
		int new_x = x0 + k * (y1 - y0);
		secondTriangle(x0, y0, new_x, y1, x1, y1);
		firstTriangle(new_x, y1, x1, y1, x2, y2);
	}
	CLine linea;
	setColor(getColor()[0], getColor()[1], getColor()[2]);
	linea.setVertex(0, x0, y0);
	linea.setVertex(1, x1, y1);
	linea.display();
	linea.setVertex(0, x0, y0);
	linea.setVertex(1, x2, y2);
	linea.display();
	linea.setVertex(0, x1, y1);
	linea.setVertex(1, x2, y2);
	linea.display();
}