#pragma once
#include "RE\ReEng.h"
//#include "GameManager.h"

class Box{
public: 
	static int globalBoxIDCount; //Each box needs to have a unique id so we will increment this static int every time we spawn a box
	
	//TetrisShape* parentShape;
	std::string modelFilePath;
	
	//Gets passed to the mesh manager singleton so it knows which box it is currently rendering
	std::string boxName;
	int boxID;

	glm::mat4 parentTransformMat;
	glm::mat4 transformMat;
	ReEng::PrimitiveClass* boxModelPrim;

	glm::vec3 position;
	glm::vec3 pivotPoint;
	glm::quat quatRotation;

	MeshManagerSingleton * meshManager;
	
	bool colliding;

	Box(MeshManagerSingleton * _meshManager, int _boxID);
	Box();
	~Box();

	void SetPosition(glm::vec3 _position);
	void Translate();
	void Rotate(glm::vec3 _axis, float _degrees);
	void DeleteBox();
};

