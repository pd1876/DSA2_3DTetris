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
	topPlane = new PrimitiveClass();
	topPlane->GeneratePlane(12.0f, REBLUE);
	
	bottomPlane = new PrimitiveClass();
	bottomPlane->GeneratePlane(12.0f, REGREEN);

	rightPlane = new PrimitiveClass();
	rightPlane->GeneratePlane(12.0f, REYELLOW);

	leftPlane = new PrimitiveClass();
	leftPlane->GeneratePlane(12.0f, RECYAN);


	//Calculate the first projections
	m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	cam1->SetView(m_m4View);
	BO_Mngr = MyBOManager::GetInstance();

	SpawnShape();

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
	//currentShape->Fall();
	UpdateAllShapes();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	//std::cout << "Shapes: " << shapeCount << std::endl;

	for (int j = 0; j < currentShape->boxes.size(); j++) {
		//std::cout << "Box: " << j << std::endl;
		BO_Mngr->SetModelMatrix(currentShape->boxes[j].transformMat, std::to_string(currentShape->boxes[j].boxID));
	}

	//UpdateAllBOs();

	BO_Mngr->Update();
	BO_Mngr->DisplayReAlligned();

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

	DisplayAllShapes();

	//Render the sides of the play area. Eventually should be blackboxed in GameManager
	topPlane->Render(cam1->GetProjection(false), cam1->GetView(), gameManager->topPlaneTransform);
	bottomPlane->Render(cam1->GetProjection(false), cam1->GetView(), gameManager->bottomPlaneTransform);
	rightPlane->Render(cam1->GetProjection(false), cam1->GetView(), gameManager->rightPlaneTransform);
	leftPlane->Render(cam1->GetProjection(false), cam1->GetView(), gameManager->leftPlaneTransform);


	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	//Release the memory of the member fields
	SafeDelete(currentShape);
	SafeDelete(m_pCube);
	SafeDelete(cam1);

	SafeDelete(topPlane);
	SafeDelete(bottomPlane);
	SafeDelete(rightPlane);
	SafeDelete(leftPlane);

	SafeDelete(gameManager);
	SafeDelete(currentShape);
	//Release the memory of the inherited fields
	super::Release(); 
}