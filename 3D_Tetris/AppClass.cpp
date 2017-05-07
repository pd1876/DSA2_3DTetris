#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("GIt GUD ScRUB"); // Window Name
}
void AppClass::InitVariables(void)
{
	//Make 6 cameras
	cam1 = new MyCamera();

	// Resize blocks array
	blocks.resize(20); 

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
	BO_Mngr = MyBOManager::GetInstance();
	for (int i = 0; i < testShape1->boxes.size(); i++) {
		BO_Mngr->AddObject(testShape1->meshManager->GetVertexList(i),std::to_string(i+1));
	}
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	// Setting up game clock to print out for player -- From Ex01_A solution
	static float gameTimer = 0.0f; // Creates new timer
	static uint gameClock = m_pSystem->GenClock(); // Asks system for new clock id
	float deltaTime = m_pSystem->LapClock(); // Laps selected clock
	gameTimer += deltaTime; // Adds delta time to current clock

	//Test moving the shape
	//testShape1->Translate(glm::vec3(0.0f, 0.0f, -0.05f));

	// Test the shapes falling
	testShape1->Fall();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	for (int i = 0; i < testShape1->boxes.size(); i++) {
		BO_Mngr->SetModelMatrix(testShape1->boxes[i].transformMat, std::to_string(i + 1));
	}
	BO_Mngr->Update();
	BO_Mngr->DisplayReAlligned();
	//BO_Mngr->DisplayOriented(-1,REWHITE);
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList("Skybox_Tetris.png");
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	m_pMeshMngr->PrintLine("3D Tetris", REBLACK);
	m_pMeshMngr->PrintLine("Level: 1"); // Currently hardcoding to see it, will fix later
	m_pMeshMngr->PrintLine("Score: 0"); // See above
	m_pMeshMngr->Print("Time passed: ");
	m_pMeshMngr->PrintLine(std::to_string(gameTimer)); // Let's player see game time
	
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
	SafeDelete(testShape1);
	//Release the memory of the inherited fields
	super::Release(); 
}