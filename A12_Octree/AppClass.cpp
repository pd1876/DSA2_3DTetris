#include "AppClass.h"

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Spatial Optimization"); // Window Name 

	/*	
		Set the clear color based on whatever happens when I play with the values
		Beautiful isn't it?

		If this line is in Init Application it will depend on the .cfg file, if it
		is on the InitVariables it will always force it regardless of the .cfg
	*/
	m_v4ClearColor = vector4(0.4f, 0.8f, 0.6f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Load Models - I really like my companion cubes
	m_pMeshMngr->LoadModel("Portal\\CompanionCube.bto", "Cubie");

	// Load the bounding object manager
	m_pBOMngr = BOManager::GetInstance();

	// Add cubie to the bounding object manager
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("Cubie"), "Cubie");

}

void AppClass::Update(void) 
{
	// Update system's time
	m_pSystem->UpdateTime();

	// Update mesh manager's time w/out updating collision detection
	m_pMeshMngr->Update();

	// Lets put one cube in the scene for right now
	m_pMeshMngr->SetModelMatrix(glm::translate(vector3(0.0f)), "Cubie");

	// Set model matrix to bounding object
	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Cubie"), "Cubie");

	// Updates bounding object manager
	m_pBOMngr->Update();

	// We have cubes, let's display cubes
	m_pBOMngr->DisplayReAlligned();

	// Adds all loaded instances to render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	// Indicates FPS
	int nFPS = m_pSystem->GetFPS();

	// Let's print that shall we (and pretend I understand this syntax)
	printf("FPS: %d        \r", nFPS);

	// TODO print other stuff
}

void AppClass::Display(void) 
{
	// Clears the screen
	ClearScreen();

	// Renders grid based on camera mode
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render();
	m_pMeshMngr->ClearRenderList();
	m_pGLSystem->GLSwapBuffers();
}

void AppClass::Release(void)
{
	super::Release(); 

}