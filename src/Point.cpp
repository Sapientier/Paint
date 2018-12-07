#include "Point.h"

CPoint::CPoint() {
	mVertices = new float*[2];
	selectingPoint = false;
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = PUNTO;
}

CPoint::~CPoint() {
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CPoint::display() {
	if (getBezier()) {
		glPointSize(8.0);
		glColor3f(255, 0, 0);
	}
	else {
		glPointSize(1.0);
		glColor3fv(mColor);
	}
	glBegin(GL_POINTS);
	glVertex2d(mVertices[0][0], mVertices[0][1]);
	glEnd();
}