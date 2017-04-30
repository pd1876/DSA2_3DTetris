#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("GIt GUD ScRUB"); // Window Name
}
void AppClass::InitVariables(void)
{
	//Make 6 cameras
	cam1 = new MyCamera();

	//Make the game manager. Currently just handles orienting the sides correctly
	gameManager = new GameManager();

	//Generate the sides of the play area. Generating them here for now but eventually they should go in GameManager
	topPlane = new PrimitiveClass();
	topPlane->GeneratePlane(12.0f, REBLUE);
	
	bottomPlane = new PrimitiveClass();
	bottomPlane->GeneratePlane(12.0f, REGREEN);

	rightPlane = new PrimitiveClass();
	rightPlane->GeneratePlane(12.0f, REYELLOW);

	leftPlane = new PrimitiveClass();
	leftPlane->GeneratePlane(12.0f, RECYAN);

	//Make a shape. This is what the player will be interacting with
	testShape1 = new TetrisShape(m_pMeshMngr); 

	//Calculate the first projections
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	cam1->SetView(m_m4View);
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();


	//Test moving the shape
	testShape1->Translate(glm::vec3(0.0f, 0.0f, -0.05f));

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	m_pMeshMngr->PrintLine("3D Tetris", REBLACK);
	m_pMeshMngr->PrintLine("Level: 1"); // Currently hardcoding to see it, will fix later
	m_pMeshMngr->PrintLine("Score: 0"); // See above
}

void AppClass::Display(void){
	//clear the screen
	ClearScreen();
	
	//Render the grid
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY);

	//Render the sides of the play area. Eventually should be blackboxed in GameManager
	topPlane->Render(cam1->GetProjection(false), cam1->GetView(), gameManager->topPlaneTransform);
	bottomPlane->Render(cam1->GetProjection(false), cam1->GetView(), gameManager->bottomPlaneTransform);
	rightPlane->Render(cam1->GetProjection(false), cam1->GetView(), gameManager->rightPlaneTransform);
	leftPlane->Render(cam1->GetProjection(false), cam1->GetView(), gameManager->leftPlaneTransform);

	testShape1->RenderBoxes(cam1);

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	//Release the memory of the member fields
	SafeDelete(testShape1);
	SafeDelete(m_pCube);
	SafeDelete(cam1);

	SafeDelete(topPlane);
	SafeDelete(bottomPlane);
	SafeDelete(rightPlane);
	SafeDelete(leftPlane);

	SafeDelete(gameManager);
	//Release the memory of the inherited fields
	super::Release(); 
}