#include "TetrisShape.h"

//-----------See Tetrisshape.h for comments-----------

TetrisShape::TetrisShape() {

}
TetrisShape::TetrisShape(MeshManagerSingleton * _meshManager){
	//InitLineBoxes();
	meshManager = _meshManager;
	boxes.resize(20);

	InitCrossBoxes();
}

TetrisShape::~TetrisShape(){

}

void TetrisShape::InitLineBoxes() {
	//See box constructor for explanation
	myBoxCount = 3;

	box1 = new Box(meshManager, 1);
	box2 = new Box(meshManager, 2);
	box3 = new Box(meshManager, 3);

	box1->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	box2->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
	box3->SetPosition(glm::vec3(4.0f, 0.0f, 0.0f));

	boxes.push_back(*box1);
	boxes.push_back(*box2);
	boxes.push_back(*box3);
}

void TetrisShape::InitCrossBoxes() {
	//See box constructor for explanation

	myBoxCount = 5;

	box1 = new Box(meshManager, 1);
	box2 = new Box(meshManager, 2);
	box3 = new Box(meshManager, 3);
	box4 = new Box(meshManager, 4);
	box5 = new Box(meshManager, 5);

	//Center
	box1->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	
	//Left and right
	box2->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
	box3->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));

	//Top and bottom
	box4->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	box5->SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));

	boxes.push_back(*box1);
	boxes.push_back(*box2);
	boxes.push_back(*box3);
	boxes.push_back(*box4);
	boxes.push_back(*box5);
}
void TetrisShape::RenderBoxes(MyCamera* renderCam) { 
	//std::cout << "Num boxes to render: " << boxes.size() << std::endl;

	for (int i = 0; i < myBoxCount; i++) {
		//Rendering with primitive boxes
		//boxes[i].boxModelPrim->Render(renderCam->GetProjection(false), renderCam->GetView(), boxes[i].transformMat);

		//Rendering with models
		std::cout << "rendering box : " << i<< std::endl;
		std::cout << "rendering box : " << boxes[i].boxName << std::endl;	

		meshManager->SetModelMatrix(boxes[i].transformMat, i);
	}

	/*meshManager->SetModelMatrix(box1->transformMat, box1->boxName);
	meshManager->SetModelMatrix(box2->transformMat, box2->boxName);
	meshManager->SetModelMatrix(box3->transformMat, box3->boxName);
	meshManager->SetModelMatrix(box4->transformMat, box4->boxName);
	meshManager->SetModelMatrix(box5->transformMat, box5->boxName);*/

}
void TetrisShape::Translate(glm::vec3 _translation) {
	/*TODO: Change this so that it stops moving if it's collided with something*/
	if (position.z < -22) {
		return;
	}
	//std::cout << "Translating" << std::endl;
	position += _translation;
	transformMat = glm::translate(transformMat, _translation);

	for (int i = 0; i < myBoxCount; i++) {
		boxes[i].parentTransformMat = transformMat;
		boxes[i].Translate();
	}
}
void TetrisShape::Rotate(glm::vec3 _axis, float _degrees) {
	rotMat = glm::rotate(IDENTITY_M4, _degrees, _axis);
	transformMat *= rotMat;

	box1->parentTransformMat = transformMat;
	box2->parentTransformMat = transformMat;
	box3->parentTransformMat = transformMat;
}
void TetrisShape::DeleteBox() {
	delete box1;
	delete box2;
	delete box3;
	delete box4;
	delete box5;
}
