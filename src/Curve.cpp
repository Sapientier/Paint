#include "Curve.h"

CCurve::CCurve() {
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = CURVE;
}

CCurve::~CCurve() {
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CCurve::setPoints(vector <CPoint *> puntos) {
	arrayPoints = puntos;
}

vector <CPoint *> CCurve::getPoints() {
	return arrayPoints;
}

void CCurve::display() {
	vector<CPoint *> points = getPoints();
	CPoint *aux;
	float x0, y0;
	float *v1;
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	for (double t = 0.0; t <= 1.0; t += 0.005) {
		aux = getCasteljauPoint(points.size() - 1, 0, t, points);
		v1 = aux->getVertex(0);
		x0 = v1[0];
		y0 = v1[1];
		glColor3fv(mColor);
		glVertex2d(x0, y0);
	}
	glEnd();
}

CPoint* CCurve::getCasteljauPoint(int r, int i, double t, vector<CPoint *> points) {
	if (r == 0) return points[i];
	float *v1, *v2;
	CPoint *p1 = getCasteljauPoint(r - 1, i, t, points);
	CPoint *p2 = getCasteljauPoint(r - 1, i + 1, t, points);
	CPoint *p = new CPoint();
	v1 = p1->getVertex(0);
	v2 = p2->getVertex(0);
	p->setVertex(0, (float)((1 - t) * v1[0] + t * v2[0]), (float)((1 - t) * v1[1] + t * v2[1]));
	return p;
}