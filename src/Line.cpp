#include "Line.h"
#include <math.h>

CLine::CLine()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = LINE;
}

CLine::~CLine()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CLine::display()
{
	int ancho = mVertices[1][0] - mVertices[0][0];
	int alto = mVertices[1][1] - mVertices[0][1];
	int dxInitial = 0, dyInitial = 0, dxFinal = 0, dyFinal = 0;

	if (ancho < 0) dxInitial = -1;
	else if (ancho > 0) dxInitial = 1;

	if (alto < 0) dyInitial = -1;
	else if (alto > 0) dyInitial = 1;

	if (ancho < 0) dxFinal = -1;
	else if (ancho > 0) dxFinal = 1;

	int max = abs(ancho);
	int min = abs(alto);

	if (max <= min) {
		max = abs(alto);
		min = abs(ancho);
		if (alto < 0) dyFinal = -1;
		else if (alto > 0) dyFinal = 1;
		dxFinal = 0;
	}

	CPoint point;
	point.setColor(getColor()[0], getColor()[1], getColor()[2]);

	int aux = max / 2;
	int x0 = mVertices[0][0];
	int y0 = mVertices[0][1];

	for (int i = 0; i <= max; i++) {
		point.setVertex(0, x0, y0);
		point.display();
		aux += min;

		if (aux >= max) {
			aux -= max;
			x0 += dxInitial;
			y0 += dyInitial;
		}
		else {
			x0 += dxFinal;
			y0 += dyFinal;
		}
	}
}

void CLine::horizontalLine(int xMin, int yMin, int xMax) {
	for (int i = xMin; i <= xMax; i++) {
		CPoint point;
		point.setVertex(0, i, yMin);
		point.setColor(getColor()[0], getColor()[1], getColor()[2]);
		point.display();
	}
}