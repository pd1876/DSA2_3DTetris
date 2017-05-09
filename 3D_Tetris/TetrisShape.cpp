#include "TetrisShape.h"

//-----------See Tetrisshape.h for comments-----------

TetrisShape::TetrisShape() {

}
TetrisShape::TetrisShape(MeshManagerSingleton * _meshManager){
	//InitLineBoxes();
	meshManager = _meshManager;
	boxes.resize(20);

	mass = 1.0f;
	velocity = vector3(0.01f);
	acceleration = vector3(0.0f, 0.0f, -0.001f);

	isFalling = true;

	srand(time(NULL));

	switch (rand() % 6) {
	case 0: InitLineBoxes();
		break;
	case 1: InitCrossBoxes();
		break;
	case 2: InitZBoxes();
		break;
	case 3: InitReverseZBoxes();
		break;
	case 4: InitLBoxes();
		break;
	case 5: InitReverseLBoxes();
		break;
	default: InitLineBoxes();
		break;
	}
}

TetrisShape::~TetrisShape(){

}

void TetrisShape::InitLineBoxes() {
	//See box constructor for explanation
	myBoxCount = 5;

	box1 = new Box(meshManager, 1);
	box2 = new Box(meshManager, 2);
	box3 = new Box(meshManager, 3);
	box4 = new Box(meshManager, 4);
	box5 = new Box(meshManager, 5);

	boxes.push_back(*box1);
	boxes.push_back(*box2);
	boxes.push_back(*box3);
	boxes.push_back(*box4);
	boxes.push_back(*box5);

	boxes[0].SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	boxes[1].SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
	boxes[2].SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
	boxes[3].SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
	boxes[4].SetPosition(glm::vec3(4.0f, 0.0f, 0.0f));

}
void TetrisShape::InitCrossBoxes() {
	//See box constructor for explanation

	myBoxCount = 5;

	box1 = new Box(meshManager, 1);
	box2 = new Box(meshManager, 2);
	box3 = new Box(meshManager, 3);
	box4 = new Box(meshManager, 4);
	box5 = new Box(meshManager, 5);

	boxes.push_back(*box1);
	boxes.push_back(*box2);
	boxes.push_back(*box3);
	boxes.push_back(*box4);
	boxes.push_back(*box5);

	//Center
	boxes[0].SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	
	//Left and right
	boxes[1].SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
	boxes[2].SetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));

	//Top and bottom
	boxes[3].SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	boxes[4].SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));


}
void TetrisShape::InitZBoxes() {

	myBoxCount = 5;

	box1 = new Box(meshManager, 1);
	box2 = new Box(meshManager, 2);
	box3 = new Box(meshManager, 3);
	box4 = new Box(meshManager, 4);
	box5 = new Box(meshManager, 5);

	boxes.push_back(*box1);
	boxes.push_back(*box2);
	boxes.push_back(*box3);
	boxes.push_back(*box4);
	boxes.push_back(*box5);

	boxes[0].SetPosition(glm::vec3(0.0f));
	boxes[1].SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	boxes[2].SetPosition(glm::vec3(1.0f, 1.0f, 0.0f));
	boxes[3].SetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
	boxes[4].SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
}
void TetrisShape::InitReverseZBoxes() {

	myBoxCount = 5;

	box1 = new Box(meshManager, 1);
	box2 = new Box(meshManager, 2);
	box3 = new Box(meshManager, 3);
	box4 = new Box(meshManager, 4);
	box5 = new Box(meshManager, 5);

	boxes.push_back(*box1);
	boxes.push_back(*box2);
	boxes.push_back(*box3);
	boxes.push_back(*box4);
	boxes.push_back(*box5);

	boxes[0].SetPosition(glm::vec3(0.0f));
	boxes[1].SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
	boxes[2].SetPosition(glm::vec3(-1.0f, -1.0f, 0.0f));
	boxes[3].SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
	boxes[4].SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
}
void TetrisShape::InitLBoxes() {

	myBoxCount = 5;

	box1 = new Box(meshManager, 1);
	box2 = new Box(meshManager, 2);
	box3 = new Box(meshManager, 3);
	box4 = new Box(meshManager, 4);
	box5 = new Box(meshManager, 5);

	boxes.push_back(*box1);
	boxes.push_back(*box2);
	boxes.push_back(*box3);
	boxes.push_back(*box4);
	boxes.push_back(*box5);

	boxes[0].SetPosition(glm::vec3(0.0f));
	boxes[1].SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	boxes[2].SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	boxes[3].SetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
	boxes[4].SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
}
void TetrisShape::InitReverseLBoxes() {

	myBoxCount = 5;

	box1 = new Box(meshManager, 1);
	box2 = new Box(meshManager, 2);
	box3 = new Box(meshManager, 3);
	box4 = new Box(meshManager, 4);
	box5 = new Box(meshManager, 5);

	boxes.push_back(*box1);
	boxes.push_back(*box2);
	boxes.push_back(*box3);
	boxes.push_back(*box4);
	boxes.push_back(*box5);

	boxes[0].SetPosition(glm::vec3(0.0f));
	boxes[1].SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	boxes[2].SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	boxes[3].SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
	boxes[4].SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
}
void TetrisShape::RenderBoxes(MyCamera* renderCam) { 
	//std::cout << "Num boxes to render: " << boxes.size() << std::endl;

	for (int i = 0; i < myBoxCount; i++) {
		//Rendering with primitive boxes
		//boxes[i].boxModelPrim->Render(renderCam->GetProjection(false), renderCam->GetView(), boxes[i].transformMat);

		//Rendering with models
		meshManager->SetModelMatrix(boxes[i].transformMat, i);
	}
}
void TetrisShape::Fall() {
	if (position.z < -22) {
		isFalling = false;
		return;
	}

	velocity += acceleration * mass;
	position += velocity;

	transformMat = glm::translate(transformMat, velocity);

	for (int i = 0; i < myBoxCount; i++) {
		boxes[i].parentTransformMat = transformMat;
		boxes[i].Translate();
	}
}
void TetrisShape::Translate(glm::vec3 _translation) {
	/*TODO: Change this so that it stops moving if it's collided with something*/
	if (position.z < -22) {
		return;
	}
	//std::cout << "Translating" << std::endl;
	position += (_translation * transSpeed);
	transformMat = glm::translate(transformMat, _translation);

	for (int i = 0; i < myBoxCount; i++) {
		boxes[i].parentTransformMat = transformMat;
		boxes[i].Translate();
	}
}
void TetrisShape::Rotate(glm::vec3 _axis, float _degrees) {
	rotMat = glm::rotate(IDENTITY_M4, _degrees * rotateAngle, _axis);
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
