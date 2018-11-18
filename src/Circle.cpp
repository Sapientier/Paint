#include "Circle.h"
#include <math.h>

CCircle::CCircle() 
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = CIRCLE;
}

CCircle::~CCircle() 
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CCircle::display() {
	CLine linea;
	CPoint punto;
	linea.setColor(getColor()[0], getColor()[1], getColor()[2]);
	punto.setColor(getColor()[0], getColor()[1], getColor()[2]);

	int radio = fabsf(mVertices[1][0] - mVertices[0][0]);
	int d = 1 - radio;
	int x = 0;
	int y = radio;
	int x0 = mVertices[0][0];
	int y0 = mVertices[0][1];

	linea.horizontalLine(-x + x0, y + y0 - 1, x + x0);
	linea.horizontalLine(-y + x0, x + y0, y + x0);
	linea.horizontalLine(-y + x0, -x + y0, y + x0);
	linea.horizontalLine(-x + x0, -y + y0 + 1, x + x0);

	punto.setVertex(0, (x0 + x), (y0 + y));
	punto.display();
	punto.setVertex(0, (x0 + y), (y0 + x));
	punto.display();
	punto.setVertex(0, (x0 + y), (y0 - x));
	punto.display();
	punto.setVertex(0, (x0 + x), (y0 - y));
	punto.display();
	punto.setVertex(0, (x0 - x), (y0 - y));
	punto.display();
	punto.setVertex(0, (x0 - y), (y0 - x));
	punto.display();
	punto.setVertex(0, (x0 - y), (y0 + x));
	punto.display();
	punto.setVertex(0, (x0 - x), (y0 + y));
	punto.display();

	while (y > x) {
		if (d < 0) {
			d = d + 2 * x + 3;
		}
		else {
			d = d + 2 * (x - y) + 5;
			y = y - 1;
		}
		x = x + 1;

		linea.horizontalLine(-x + x0, y + y0 - 1, x + x0);
		linea.horizontalLine(-y + x0, x + y0, y + x0);
		linea.horizontalLine(-y + x0, -x + y0, y + x0);
		linea.horizontalLine(-x + x0, -y + y0 + 1, x + x0);

		punto.setVertex(0, (x0 + x), (y0 + y));
		punto.display();
		punto.setVertex(0, (x0 + y), (y0 + x));
		punto.display();
		punto.setVertex(0, (x0 + y), (y0 - x));
		punto.display();
		punto.setVertex(0, (x0 + x), (y0 - y));
		punto.display();
		punto.setVertex(0, (x0 - x), (y0 - y));
		punto.display();
		punto.setVertex(0, (x0 - y), (y0 - x));
		punto.display();
		punto.setVertex(0, (x0 - y), (y0 + x));
		punto.display();
		punto.setVertex(0, (x0 - x), (y0 + y));
		punto.display();
	}
}