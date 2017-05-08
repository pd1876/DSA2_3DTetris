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
	SpawnCubes(650);

	// Set up the camera away from the cubes
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 0.5f, 60.0f),//Camera position
		vector3(0.0f, 0.5f, 0.0f),//What Im looking at
		REAXISY);//What is up
}

void AppClass::SpawnCubes(int _numCubes) {
	// Load the bounding object manager
	m_pBOMngr = BOManager::GetInstance();
	numCubes = _numCubes;

	for (int i = 0; i < _numCubes; i++) {
		std::string modelName = "Cubie" + i;
		//Load Models - I really like my companion cubes
		m_pMeshMngr->LoadModel("Portal\\CompanionCube.bto", modelName);

		// Add cubie to the bounding object manager
		m_pBOMngr->AddObject(m_pMeshMngr->GetVertexList(modelName), modelName);


		// Lets put one cubie in the scene for right now
		m_pMeshMngr->SetModelMatrix(glm::translate(vector3(glm::linearRand(-10.0f, 10.0f), glm::linearRand(-10.0f, 10.0f), glm::linearRand(-10.0f, 10.0f))), modelName);
	}
}
void AppClass::RenderOctree() {
	// temp min max and center values
	vector3 _center;
	vector3 _min;
	vector3 _max;
	vector3 _halfWidth;

	octree = Octree::getInstance();
	
	// loop through each object
	for (int i = 0; i < numCubes; i++) {
		std::string modelName = "Cubie" + i;
		BOClass* cube = m_pBOMngr->GetBoundingObject(modelName);
		vector3 cubeMin = cube->GetMinG();
		vector3 cubeMax = cube->GetMaxG();

		// if first cube imediately set min and max
		if (i == 0) {
			_min = cubeMin;
			_max = cubeMax;
		}
		else {
			if (_min.x > cubeMin.x) //If min is larger than cube's min
				_min.x = cubeMin.x;
			else if (_max.x < cubeMax.x)//if max is smaller than cube's max
				_max.x = cubeMax.x;

			if (_min.y > cubeMin.y) //If min is larger than cube's min
				_min.y = cubeMin.y;
			else if (_max.y < cubeMax.y)//if max is smaller than cube's max
				_max.y = cubeMax.y;

			if (_min.z > cubeMin.z) //If min is larger than cube's min
				_min.z = cubeMin.z;
			else if (_max.z < cubeMax.z)//if max is smaller than cube's max
				_max.z = cubeMax.z;
		}
	}

	// calculate the center
	_center = (_max + _min) / 2.0f;

	_halfWidth = (_max - _min) / 2.0f;

	octree->displayOctree(_center, _min, _max, _halfWidth);
}
void AppClass::UpdateCubes() {
	for (int i = 0; i < numCubes; i++) {
		std::string modelName = "Cubie" + i;

		// Set model matrix to bounding object
		m_pBOMngr->SetModelMatrix(m_pMeshMngr->GetModelMatrix(modelName), modelName);

		// Display bounding frame of object
		m_pBOMngr->DisplayReAlligned(modelName);
	}
}
void AppClass::Update(void) 
{
	// Update system's time
	m_pSystem->UpdateTime();

	// Update mesh manager's time w/out updating collision detection
	m_pMeshMngr->Update();

	// Updates cube based stuff
	UpdateCubes();

	RenderOctree();

	// Updates bounding object manager
	m_pBOMngr->Update();

	// Adds all loaded instances to render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	// Indicates FPS
	int nFPS = m_pSystem->GetFPS();

	// TODO print other stuff
	//(x == y) ? a : b
	m_pMeshMngr->PrintLine("Spatial Optimization :" + (spatialOptEnabled == true) ? "Enabled" : "Disabled");
	m_pMeshMngr->PrintLine("FPS: " + nFPS);
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