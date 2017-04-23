#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("A08"); // Window Name
}
void AppClass::InitVariables(void)
{
	//Make a camera
	cam1 = new MyCamera();

	//Generate the Cube
	m_pCube = new PrimitiveClass();
	m_pCone = new PrimitiveClass();
	m_pCylinder = new PrimitiveClass();
	m_pCube->GenerateCube(2.0f, REBLUE);
	m_pCone->GenerateCone(2.0f, 2.0f, 12, RERED);
	m_pCylinder->GenerateCylinder(2.0f, 2.0f, 12, REGREEN);
	coneMatrix = IDENTITY_M4 * glm::translate(vector3(5.0f, 0.0f, 0.0f));
	cylMatrix = IDENTITY_M4 * glm::translate(vector3(-5.0f, 0.0f, 0.0f));
	

	//Calculate the first projections
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	cam1->SetView(m_m4View);
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	
	//Render the grid
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY);

	//Render the cube
	m_pCube->Render(cam1->GetProjection(false), cam1->GetView(), IDENTITY_M4);
	m_pCone->Render(cam1->GetProjection(false), cam1->GetView(), coneMatrix);
	m_pCylinder->Render(cam1->GetProjection(false), cam1->GetView(), cylMatrix);
	

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	//Release the memory of the member fields
	SafeDelete(m_pCube);
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);
	SafeDelete(cam1);

	//Release the memory of the inherited fields
	super::Release(); 
}