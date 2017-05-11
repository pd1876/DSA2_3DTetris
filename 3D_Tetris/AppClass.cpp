#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("GIt GUD ScRUB"); // Window Name
}
void AppClass::InitVariables(void)
{
	//this needs to go here because its static and has to be defined outside of Box
	//Box::globalBoxIDCount = 0;

	//Make 6 cameras
	cam1 = new MyCamera();

	// Resize blocks array
	//shapes.resize(20); 

	//Make the game manager. Currently just handles orienting the sides correctly
	gameManager = new GameManager();

	//Generate the sides of the play area. Generating them here for now but eventually they should go in GameManager
	m_pMeshMngr->LoadModel("tetris_pieces\\checkered_wall.obj", "wall_bottom");
	m_pMeshMngr->LoadModel("tetris_pieces\\checkered_wall.obj", "wall_top");
	m_pMeshMngr->LoadModel("tetris_pieces\\checkered_wall.obj", "wall_left");
	m_pMeshMngr->LoadModel("tetris_pieces\\checkered_wall.obj", "wall_right");
	m_pMeshMngr->LoadModel("tetris_pieces\\checkered_wall.obj", "floor");
	m_pMeshMngr->LoadModel("Portal\\CompanionCube.bto", "cube");

	m_pWall_Bottom = new MyEntityClass("wall_bottom");
	m_pWall_Bottom->SetModelMatrix(glm::rotate(IDENTITY_M4, 90.0f, REAXISX) * glm::translate(0.0f, 0.0f, 2.0f));

	m_pWall_Top = new MyEntityClass("wall_top");
	m_pWall_Top->SetModelMatrix(glm::rotate(IDENTITY_M4, 90.0f, REAXISX) * glm::translate(0.0f, 0.0f, -2.0f));

	m_pWall_Left = new MyEntityClass("wall_left");
	m_pWall_Left->SetModelMatrix(glm::rotate(IDENTITY_M4, 90.0f, REAXISY) * glm::translate(0.0f, 0.0f, 2.0f));

	m_pWall_Right = new MyEntityClass("wall_right");
	m_pWall_Right->SetModelMatrix(glm::rotate(IDENTITY_M4, 90.0f, REAXISY) * glm::translate(0.0f, 0.0f, -2.0f));

	m_pFloor = new MyEntityClass("floor");
	m_pFloor->SetModelMatrix(glm::translate(0.0f, 0.0f, -2.0f));

	m_pCube = new MyEntityClass("cube");
	m_pCube->SetModelMatrix(glm::translate(0.0f, 0.0f, 0.0f));
	m_pCube->SetVelocity(vector3(0.25f, 0.25f, 0.0f));

	//Calculate the first projections
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	cam1->SetView(m_m4View);
	BO_Mngr = MyBOManager::GetInstance();

}
void AppClass::SpawnShape() {
	//Make a shape. This is what the player will be interacting with

	//This might cause errors by having us try to access the same memory location or some shit. i don't really know how c++ works
	currentShape = new TetrisShape(m_pMeshMngr);
	
	for (int i = 0; i < currentShape->boxes.size(); i++) {
		BO_Mngr->AddObject(currentShape->meshManager->GetVertexList(i), currentShape->boxes[i].boxName);
	}

	shapeCount++;
	shapes.push_back(*currentShape);
}
void AppClass::UpdateAllShapes() {
	currentShape->Fall();

	//If our current shape has stopped, spawn in a new one
	if (!currentShape->isFalling) {
		SpawnShape();
	}
}
void AppClass::DisplayAllShapes() {
	//This doesn't work for some reason
	/*for (int i = 0; i < shapeCount; i++) {
		std::cout << "Rendering shape: " << i << std::endl;
		shapes[i].RenderBoxes(cam1);
	}*/
	
	//Will need to change this for row clearing
	currentShape->RenderBoxes(cam1);
}
void AppClass::UpdateAllBOs() {
	for (int i = 0; i < shapes.size(); i++) {
		for (int j = 0; j < shapes[i].boxes.size(); j++) {
			std::cout << "Displaying BO for box " << shapes[i].boxes[j].boxName <<std::endl;
			BO_Mngr->SetModelMatrix(shapes[i].boxes[j].transformMat, shapes[i].boxes[j].boxName);
			BO_Mngr->DisplayReAlligned(shapes[i].boxes[j].boxName, RERED);
			//BO_Mngr->DisplayOriented(shapes[i].boxes[j].boxName, RERED);
		}
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


	// Test the shapes falling

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	//std::cout << "Shapes: " << shapeCount << std::endl;
	UpdateAllShapes();

	m_pCube->Update();

	// Lets made some collision detection
	if (m_pCube->IsColliding(m_pWall_Bottom)) {
		vector3 v3Velocity = m_pCube->GetVelocity();
		v3Velocity.y *= -1;
		m_pCube->SetVelocity(v3Velocity);
	}
	if (m_pCube->IsColliding(m_pWall_Top)) {
		vector3 v3Velocity = m_pCube->GetVelocity();
		v3Velocity.y *= -1;
		m_pCube->SetVelocity(v3Velocity);
	}
	if (m_pCube->IsColliding(m_pWall_Left)) {
		vector3 v3Velocity = m_pCube->GetVelocity();
		v3Velocity.x *= -1;
		m_pCube->SetVelocity(v3Velocity);
	}
	if (m_pCube->IsColliding(m_pWall_Right)) {
		vector3 v3Velocity = m_pCube->GetVelocity();
		v3Velocity.x *= -1;
		m_pCube->SetVelocity(v3Velocity);
	}

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList("Skybox_Tetris.png");
	m_pWall_Bottom->AddToRenderList(true);
	m_pWall_Top->AddToRenderList(true);
	m_pWall_Left->AddToRenderList(true);
	m_pWall_Right->AddToRenderList(true);
	m_pFloor->AddToRenderList(true);	
	m_pCube->AddToRenderList(true);

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
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	//Release the memory of the member fields
	SafeDelete(currentShape);
	SafeDelete(cam1);
	SafeDelete(m_pWall_Bottom);
	SafeDelete(m_pWall_Top);
	SafeDelete(m_pWall_Left);
	SafeDelete(m_pWall_Right);
	SafeDelete(m_pFloor);
	SafeDelete(m_pCube);
	SafeDelete(gameManager);
	SafeDelete(currentShape);
	//Release the memory of the inherited fields
	super::Release(); 
}