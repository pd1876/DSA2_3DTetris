#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "BOManager.h"

using namespace ReEng; 

class AppClass : public ReEngAppClass {

	// Pointer to the BO manager
	BOManager* m_pBOMngr;

public:
	typedef ReEngAppClass super;

	// Constructor for the class 
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole = false) : super(hInstance, lpCmdLine, nCmdShow, a_bUsingConsole) {}

	// Destructor for the class
	~AppClass(void) { Release(); }

	// Reads config of app to file
	virtual void ReadConfig(void) final {}

	// Writes config of app to file
	virtual void WriteConfig(void) final {}

	// Initialize ReEng vars needed to make window
	virtual void InitWindow(String a_sWindowName) final;

	// Initialize user specific vars, executed after InitApplicationVariables
	virtual void InitVariables(void) final;

	// Updates scene
	virtual void Update(void) final;

	// Displays scene
	virtual void Display(void) final;

	// Manages response of keys pressed
	virtual void ProcessKeyboard(void) final;

	// Manages response of mouse pressed
	virtual void ProcessMouse(void) final;

	// Releases application
	virtual void Release(void) final;

};

#endif // !_APPLICATION_H_
