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
	m_pCube->GenerateCube(5.0f, REBLUE);

	//Make a box
	//testBox1 = new Box();

	//Make a shape
	testShape1 = new TetrisShape();

	//Calculate the first projections
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 14.0f), glm::vec3(0.0f, 1.0f, 0.0f));

}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Test moving a box
	//testBox1->Translate(glm::vec3(0.0f, 0.0f, -0.01f));

	//Test moving the shape
	testShape1->Translate(glm::vec3(0.0f, 0.0f, -0.01f));

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);

}

void AppClass::Display(void){
	//clear the screen
	ClearScreen();
	
	//Render the grid
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY);

	//Render the cube
	//m_pCube->Render(cam1->GetProjection(false), cam1->GetView(), IDENTITY_M4);
	
	//Render test box
	//testBox1->boxModelPrim->Render(cam1->GetProjection(false), cam1->GetView(), testBox1->transformMat);

	//Render all boxes in test shape. See TetrisShape.cpp for explanation as to why this isn't coded well. Fuck this language
	testShape1->box1->boxModelPrim->Render(cam1->GetProjection(false), cam1->GetView(), testShape1->box1->transformMat);
	testShape1->box2->boxModelPrim->Render(cam1->GetProjection(false), cam1->GetView(), testShape1->box2->transformMat);
	testShape1->box3->boxModelPrim->Render(cam1->GetProjection(false), cam1->GetView(), testShape1->box3->transformMat);



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

	//Release the memory of the inherited fields
	super::Release(); 
}