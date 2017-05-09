/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Box.h"
#include "TetrisShape.h"
#include "Camera.h"
#include "MyBOManager.h"

//#include <chrono>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class AppClass : public ReEngAppClass
{
	bool keyDown;

	GameManager* gameManager = nullptr;

	//Sides of the game
	PrimitiveClass* topPlane = nullptr;
	PrimitiveClass* bottomPlane = nullptr;
	PrimitiveClass* rightPlane = nullptr;
	PrimitiveClass* leftPlane = nullptr;

	PrimitiveClass* m_pCube = nullptr;
	PrimitiveClass* m_pCone = nullptr;
	PrimitiveClass* m_pCylinder = nullptr;

	TetrisShape* testShape1 = nullptr;
	Box* testBox1 = nullptr;

	// Array of blocks to keep track of our blocks
	std::vector<TetrisShape> blocks;

	matrix4 m_m4Projection;
	matrix4 m_m4View;
	MyBOManager* BO_Mngr = nullptr;

public:
	MyCamera* cam1;
	typedef ReEngAppClass super;

	/* Constructor */
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow) : super(hInstance, lpCmdLine, nCmdShow) {}

	/*
	InitWindow
	Initialize ReEng variables necessary to create the window
	*/
	virtual void InitWindow(String a_sWindowName);

	/*
	InitVariables
	Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	*/
	virtual void InitVariables(void);

	/*
	Update
	Updates the scene
	*/
	virtual void Update(void);

	/*
	Display
	Displays the scene
	*/
	virtual void Display(void);

	/*
	ProcessKeyboard
	Manage the response of key presses
	*/
	virtual void ProcessKeyboard(void);

	/*
	Release
	Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	*/
	virtual void Release(void);

	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ReadConfig(void) final {}

	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void WriteConfig(void) final {}
};

#endif //__APPLICATION_H_
