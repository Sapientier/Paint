//Brian Manuel Torres Carrero
//CI 24042974

#include "Main.h"
#include "Line.h"
#include "Quad.h"
#include "Circle.h"
#include "Elipse.h"
#include "Triangle.h"
#include "UserInterface.h"

using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
int picked;
bool gPress;
bool selecting = false;
bool BoxExist = false;
CUserInterface * userInterface;
vector <CFigure *> figures;
FigureType figureSelected;
CTriangle *triangle = new CTriangle();
CQuad *boundBox = new CQuad();
int trianCont = 0;

void save() {
	char filename[MAX_PATH];
	int x0, y0, x1, y1, x2, y2;
	float r, g, b;
	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Archivos json\0*.json\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Especifique la ruta para guardar el archivo.";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
	if (GetSaveFileName(&ofn)) {
		string fileToSave = string(ofn.lpstrFile) + ".json";
		ofstream file(fileToSave, std::ofstream::out);
		file << figures.size() << "\n";
		for (int i = 0; i < figures.size(); i++) {
			float *v1 = figures[i]->getVertex(0);
			float *v2 = figures[i]->getVertex(1);
			x0 = v1[0];
			y0 = v1[1];
			x1 = v2[0];
			y1 = v2[1];
			r = figures[i]->getColor()[0];
			g = figures[i]->getColor()[1];
			b = figures[i]->getColor()[2];
			if (figures[i]->getType() == TRIANGLE) {
				float *v3 = figures[i]->getVertex(2);
				x2 = v3[0];
				y2 = v3[1];
				file << figures[i]->getType() << " " << r << " " << g << " " << b << " " << x0 << " " << y0 << " " << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
			}
			else if (figures[i]->getType() == QUAD) {
				if (figures[i]->getBox() == 0) {
					file << figures[i]->getType() << " " << r << " " << g << " " << b << " " << x0 << " " << y0 << " " << x1 << " " << y1 << "\n";
				}
			}
			else {
				file << figures[i]->getType() << " " << r << " " << g << " " << b << " " << x0 << " " << y0 << " " << x1 << " " << y1 << "\n";
			}
		}
	}
}

void load() {
	char filename[MAX_PATH];
	int tipo;
	int x0, y0, x1, y1, x2, y2;
	string color;
	float r, g, b;
	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Archivos json\0*.json\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Seleccione un archivo para cargar.";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
	if (GetOpenFileNameA(&ofn)) {
		while (!figures.empty()) figures.pop_back();
		int nFigures;
		ifstream file(filename, std::ifstream::in);
		file >> nFigures;
		for (int i = 0; i < nFigures; i++) {
			file >> tipo;
			if (tipo == 1) {
				CLine *line = new CLine();
				file >> r >> g >> b >> x0 >> y0 >> x1 >> y1;
				line->setColor(r, g, b);
				line->setVertex(0, x0, y0);
				line->setVertex(1, x1, y1);
				figures.push_back(line);
			} 
			else if (tipo == 2) {
				CQuad *quad = new CQuad();
				file >> r >> g >> b >> x0 >> y0 >> x1 >> y1;
				quad->setColor(r, g, b);
				quad->setVertex(0, x0, y0);
				quad->setVertex(1, x1, y1);
				figures.push_back(quad);
			}
			else if (tipo == 3) {
				CCircle *circle = new CCircle();
				file >> r >> g >> b >> x0 >> y0 >> x1 >> y1;
				circle->setColor(r, g, b);
				circle->setVertex(0, x0, y0);
				circle->setVertex(1, x1, y1);
				figures.push_back(circle);
			}
			else if (tipo == 4) {
				CElipse *elipse = new CElipse();
				file >> r >> g >> b >> x0 >> y0 >> x1 >> y1;
				elipse->setColor(r, g, b);
				elipse->setVertex(0, x0, y0);
				elipse->setVertex(1, x1, y1);
				figures.push_back(elipse);
			}
			else if (tipo == 5) {
				CTriangle *triangle = new CTriangle();
				file >> r >> g >> b >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;
				triangle->setColor(r, g, b);
				triangle->setVertex(0, x0, y0);
				triangle->setVertex(1, x1, y1);
				triangle->setVertex(2, x2, y2);
				figures.push_back(triangle);
			}
		}
	}
}

void pick(int x, int y)
{
	picked = -1;
	userInterface->hide();

	if (!BoxExist) {
		figures.push_back(boundBox);
		BoxExist = true;
	}

	for (unsigned int i = 0; i < figures.size(); i++)
	{
		float *v1 = figures[i]->getVertex(0);
		float *v2 = figures[i]->getVertex(1);
		float max[2];
		float min[2];

		// This should be precalculated

		max[0] = MAX(v1[0], v2[0]);
		max[1] = MAX(v1[1], v2[1]);

		min[0] = MIN(v1[0], v2[0]);
		min[1] = MIN(v1[1], v2[1]);

		if (selecting) {
			boundBox->setBox(3);
			selecting = false;
		}

		if (x >= min[0] && x <= max[0] && y >= min[1] && y <= max[1])
		{
			picked = i;

			userInterface->setFigureColor(figures[picked]->getColor());
			userInterface->show();

			int type = figures[picked]->getType();

			if (type == LINE) {
				userInterface->setFigureType("Line");

				boundBox->setVertex(0, v1[0], v1[1]);
				boundBox->setVertex(1, v2[0], v2[1]);
				boundBox->setBox(1);

				selecting = true;
			}
			else if (type == QUAD) {
				userInterface->setFigureType("Quad");
				int x0 = v1[0] - 5, x1 = v2[0] + 5;
				int y0 = v1[1] + 5, y1 = v2[1] - 5;

				boundBox->setVertex(0, x0, y0);
				boundBox->setVertex(1, x1, y1);
				boundBox->setBox(1);

				selecting = true;
			}
			else if (type == CIRCLE) {
				userInterface->setFigureType("Circle");
				int radio = fabsf(v2[0] - v1[0]);

				boundBox->setVertex(0, v1[0] - radio, v1[1] - radio);
				boundBox->setVertex(1, v1[0] + radio, v1[1] + radio);
				boundBox->setBox(1);

				selecting = true;
			}
				
			else if (type == ELIPSE) {
				userInterface->setFigureType("Elipse");
				int radioX = fabsf(v2[0] - v1[0]);
				int radioY = fabsf(v2[1] - v1[1]);

				boundBox->setVertex(0, v1[0] - radioX, v1[1] - radioY);
				boundBox->setVertex(1, v1[0] + radioX, v1[1] + radioY);
				boundBox->setBox(1);

				selecting = true;
			}
				
			else if (type == TRIANGLE) {
				userInterface->setFigureType("Triangle");
				float *v3 = figures[i]->getVertex(2);
				int xMin, yMin, xMax, yMax;

				xMin = min[0];
				xMin = MIN(xMin, v3[0]);
				yMin = min[1];
				yMin = MIN(yMin, v3[1]);
				xMax = max[0];
				xMax = MAX(xMax, v3[0]);
				yMax = max[1];
				yMax = MAX(yMax, v3[1]);

				boundBox->setVertex(0, xMin, yMin);
				boundBox->setVertex(1, xMax, yMax);
				boundBox->setBox(1);

				selecting = true;
			}

			break;
		}
	}
}

void updateUserInterface()
{
	if (picked > -1)
	{
		float *color = userInterface->getFigureColor();
		float r, g, b;
		r = color[0];
		g = color[1];
		b = color[2];
		figures[picked]->setColor(color[0], color[1], color[2]);
	}
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (unsigned int i = 0; i < figures.size(); i++)
		figures[i]->display();
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, gWidth, 0, gHeight, -1.0f, 1.0f);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_P:
			figureSelected = NONE;
			userInterface->hide();
			break;

		case GLFW_KEY_S:
			save();
			break;

		case GLFW_KEY_G:
			load();
			break;

		case GLFW_KEY_L:
			figureSelected = LINE;
			userInterface->hide();
			break;

		case GLFW_KEY_Q:
			figureSelected = QUAD;
			userInterface->hide();
			break;

		case GLFW_KEY_C:
			figureSelected = CIRCLE;
			userInterface->hide();
			break;

		case GLFW_KEY_E:
			figureSelected = ELIPSE;
			userInterface->hide();
			break;

		case GLFW_KEY_T:
			figureSelected = TRIANGLE;
			userInterface->hide();
			break;
		}
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;

	double x, y;
	glfwGetCursorPos(gWindow, &x, &y);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !gPress)
	{
		float ax = float(x);
		float ay = gHeight - float(y);

		if (figureSelected == NONE)
			pick(int(ax), int(ay));
		else if (figureSelected == LINE)
		{
			CLine *line = new CLine();
			line->setVertex(0, ax, ay);
			line->setVertex(1, ax, ay);
			figures.push_back(line);

			gPress = true;
		}
		else if (figureSelected == QUAD)
		{
			CQuad *quad = new CQuad();
			quad->setVertex(0, ax, ay);
			quad->setVertex(1, ax, ay);
			figures.push_back(quad);

			gPress = true;
		}
		else if (figureSelected == CIRCLE)
		{
			CCircle *circle = new CCircle();
			circle->setVertex(0, ax, ay);
			circle->setVertex(1, ax, ay);
			figures.push_back(circle);

			gPress = true;
		}
		else if (figureSelected == ELIPSE)
		{
			CElipse *elipse = new CElipse();
			elipse->setVertex(0, ax, ay);
			elipse->setVertex(1, ax, ay);
			figures.push_back(elipse);

			gPress = true;
		}
		else if (figureSelected == TRIANGLE)
		{
			if (trianCont == 0) {
				triangle->setVertex(0, ax, ay);
				trianCont++;
			}
			else if (trianCont == 1) {
				triangle->setVertex(1, ax, ay);
				trianCont++;
			}
			else if (trianCont == 2) {
				triangle->setVertex(2, ax, ay);
				figures.push_back(triangle);
				trianCont = 0;
				triangle = new CTriangle();
			}
		}
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		gPress = false;
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;

	if (gPress)
	{
		float ax = float(x);
		float ay = gHeight - float(y);

		figures.back()->setVertex(1, ax, ay);
	}
}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < figures.size(); i++)
		delete figures[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "Proyecto 1 - Paint", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();
	return true;
}

int main(void)
{
	gWidth = 1200;
	gHeight = 680;
	gPress = false;
	figureSelected = LINE;
	picked = -1;

	if (!initGlfw() || !initUserInterface())
		return EXIT_FAILURE;

	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	while (!glfwWindowShouldClose(gWindow))
	{
		display();

		TwDraw();

		updateUserInterface();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}