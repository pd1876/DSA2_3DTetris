#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("GIt GUD ScRUB"); // Window Name
}
void AppClass::InitVariables(void)
{
	//Make a camera
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
	leftPlane->GeneratePlane(12.0f, REGREENDARK);


	//Make a shape. This is what the player will be interacting with
	testShape1 = new TetrisShape();


	//Load Models
	m_pMeshMngr->LoadModel("Tetris\\blue_Lpiece.obj", "blueLpiece");
	m_pMeshMngr->LoadModel("Tetris\\green_Zpiece.obj", "greenZpiece");
	m_pMeshMngr->LoadModel("Tetris\\magenta_Tblock.obj", "magentaTblock");
	m_pMeshMngr->LoadModel("Tetris\\orange_Lpiece.obj", "orangeLpiece");
	m_pMeshMngr->LoadModel("Tetris\\red_Zpiece.obj", "redZpiece");
	m_pMeshMngr->LoadModel("Tetris\\skyblue_linepiece.obj", "skybluelinepiece");
	m_pMeshMngr->LoadModel("Tetris\\yellow_blockpiece.obj", "yellowblockpiece");

	m_pBOMngr = MyBOManager::GetInstance();
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("blueLpiece"), "blueLpiece");
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("greenZpiece"), "greenZpiece");
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("magenta_Tblock"), "magenta_Tblock");
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("orangeLpiece"), "orangeLpiece");
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("redZpiece"), "redZpiece");
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("skybluelinepiece"), "skybluelinepiece");
	m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList("yellowblockpiece"), "yellowblockpiece");

	//Calculate the first projections
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	m_m4View = glm::lookAt(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 14.0f), vector3(0.0f, 1.0f, 0.0f));
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

	// Test falling shapes
	testShape1->Fall();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList("Skybox_Tetris.png");
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	m_pMeshMngr->PrintLine("3D Tetris", REBLACK);
	m_pMeshMngr->PrintLine("Level: 1"); // Currently hardcoding to see it, will fix later
	m_pMeshMngr->PrintLine("Score: 0"); // See above
	m_pMeshMngr->Print("Time passed: "); 
	m_pMeshMngr->PrintLine(std::to_string(gameTimer)); // Let's player see game time

	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("blueLpiece"), "blueLpiece");
	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("greenZpiece"), "greenZpiece");
	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("magenta_Tblock"), "magenta_Tblock");
	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("orangeLpiece"), "orangeLpiece");
	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("redZpiece"), "redZpiece");
	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("skybluelinepiece"), "skybluelinepiece");
	m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix("yellowblockpiece"), "yellowblockpiece");

	m_pBOMngr->Update();//Update collision detection

						//m_pBOMngr->DisplaySphere(-1, REWHITE);
	m_pBOMngr->DisplayReAlligned();
	m_pBOMngr->DisplayOriented(-1, REWHITE);


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

	SafeDelete(topPlane);
	SafeDelete(bottomPlane);
	SafeDelete(rightPlane);
	SafeDelete(leftPlane);

	SafeDelete(gameManager);
	//Release the memory of the inherited fields
	super::Release(); 
}