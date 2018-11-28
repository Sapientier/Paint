#include "Elipse.h"
#include "Line.h"
#include <math.h>

CElipse::CElipse() 
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = ELIPSE;
}

CElipse::~CElipse() 
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CElipse::display() {
	CLine linea;
	CPoint punto;
	float r, g, b2;
	r = getColor()[0];
	g = getColor()[1];
	b2 = getColor()[2];
	linea.setColor(getColor()[0], getColor()[1], getColor()[2]);
	punto.setColor(getColor()[0], getColor()[1], getColor()[2]);

	int a = fabsf(mVertices[1][0] - mVertices[0][0]);
	int b = fabsf(mVertices[1][1] - mVertices[0][1]);
	int x = 0, y = b, d;
	int x0 = mVertices[0][0];
	int y0 = mVertices[0][1];
	d = b * (4 * b - 4 * a*a) + a * a;

	linea.horizontalLine(-x + x0, y + y0 - 1, x + x0);
	linea.horizontalLine(-x + x0, -y + y0 + 1, x + x0);

	punto.setVertex(0, x + x0, y + y0);
	punto.display();
	punto.setVertex(0, x + x0, -y + y0);
	punto.display();
	punto.setVertex(0, -x + x0, -y + y0);
	punto.display();
	punto.setVertex(0, -x + x0, y + y0);
	punto.display();

	while (b * b * 2 * (x + 1) < a * a * (2 * y - 1)) {
		if (d < 0) d = d + 4 * (b * b * (2 * x + 3));
		else {
			d = d + 4 * (b * b * (2 * x + 3) + a * a * (-2 * y + 2));
			y = y - 1;
		};
		x = x + 1;

		linea.horizontalLine(-x + x0, y + y0 - 1, x + x0);
		linea.horizontalLine(-x + x0, -y + y0 + 1, x + x0);

		punto.setVertex(0, x + x0, y + y0);
		punto.display();
		punto.setVertex(0, x + x0, -y + y0);
		punto.display();
		punto.setVertex(0, -x + x0, -y + y0);
		punto.display();
		punto.setVertex(0, -x + x0, y + y0);
		punto.display();
	}
	d = b * b * (4 * x * x + 4 * x + 1) + a * a * (4 * y * y - 8 * y + 4) - 4 * a * a * b * b;

	while (y > 0) {
		if (d <= 0) {
			d = d + 4 * (b * b * (2 * x + 2) + a * a * (-2 * y + 3));
			x = x + 1;
		}
		else d = d + 4 * a * a * (-2 * y + 3);

		y = y - 1;

		if (y - 1 > 0) {
			linea.horizontalLine(-x + x0, y + y0 - 1, x + x0);
			linea.horizontalLine(-x + x0, -y + y0 + 1, x + x0);
		}
		else {
			linea.horizontalLine(-x + x0, y + y0, x + x0);
			linea.horizontalLine(-x + x0, -y + y0, x + x0);
		}

		punto.setVertex(0, x + x0, y + y0);
		punto.display();
		punto.setVertex(0, x + x0, -y + y0);
		punto.display();
		punto.setVertex(0, -x + x0, -y + y0);
		punto.display();
		punto.setVertex(0, -x + x0, y + y0);
		punto.display();
	}
}