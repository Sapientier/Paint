#include "Point.h"

CPoint::CPoint() {
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];
}

CPoint::~CPoint() {
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CPoint::display() {
	glColor3fv(mColor);
	glBegin(GL_POINTS);
	glVertex2d(mVertices[0][0], mVertices[0][1]);
	glEnd();
}