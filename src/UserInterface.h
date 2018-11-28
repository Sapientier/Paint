#pragma once
#include "../headers/AntTweakBar.h"
#include "Windows.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

using std::string;

//Singleton user interface class

class CUserInterface
{
private:
	static CUserInterface * mInterface; //Holds the instance of the class
	TwBar *mUserInterface;
	float mFigureColor[3];
	string mFigureType;

public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setFigureColor(float *color);
	void setFigureType(string type);
	float* getFigureColor();

private:
	///Private constructor
	CUserInterface();
};