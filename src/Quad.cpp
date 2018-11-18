#include "Quad.h"

CQuad::CQuad()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = QUAD;
}

CQuad::~CQuad()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CQuad::display()
{
	CLine linea;
	linea.setColor(getColor()[0], getColor()[1], getColor()[2]);
	int x0 = mVertices[0][0], x1 = mVertices[1][0];
	int y0 = mVertices[0][1], y1 = mVertices[1][1];

	if (x0 > x1) {
		int aux = x1;
		x1 = x0;
		x0 = aux;
	}

	if (y0 > y1) {
		int aux = y1;
		y1 = y0;
		y0 = aux;
	}

	if (y1 > y0) {
		for (int i = y0 + 1; i <= y1 - 1; i++) {
			if (x1 > x0)
				linea.horizontalLine(x0 + 1, i, x1 - 1);
			else
				linea.horizontalLine(x1 + 1, i, x0 - 1);	
		}
	}
	else {
		for (int i = y1 + 1; i <= y0 - 1; i++) {
			if (x1 > x0) 
				linea.horizontalLine(x0 + 1, i, x1 - 1);
			else 
				linea.horizontalLine(x1 + 1, i, x0 - 1);
		}
	}

	linea.setVertex(0, x0, y0);
	linea.setVertex(1, x1, y0);
	linea.display();
	linea.setVertex(0, x1, y0);
	linea.setVertex(1, x1, y1);
	linea.display();
	linea.setVertex(0, x1, y1);
	linea.setVertex(1, x0, y1);
	linea.display();
	linea.setVertex(0, x0, y1);
	linea.setVertex(1, x0, y0);
	linea.display();
}