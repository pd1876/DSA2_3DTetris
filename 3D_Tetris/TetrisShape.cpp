#include "TetrisShape.h"

//-----------See Tetrisshape.h for comments-----------

TetrisShape::TetrisShape(){
	//InitLineBoxes();
	InitCrossBoxes();
}

TetrisShape::~TetrisShape(){

}

void TetrisShape::InitLineBoxes() {
	
	box1 = new Box();
	box2 = new Box();
	box3 = new Box();

	box1->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	box2->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
	box3->SetPosition(glm::vec3(4.0f, 0.0f, 0.0f));

	boxes.push_back(*box1);
	boxes.push_back(*box2);
	boxes.push_back(*box3);
}

void TetrisShape::InitCrossBoxes() {
	box1 = new Box();
	box2 = new Box();
	box3 = new Box();
	box4 = new Box();
	box5 = new Box();

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

	for (int i = 0; i < boxes.size(); i++) {
		boxes[i].boxModelPrim->Render(renderCam->GetProjection(false), renderCam->GetView(), boxes[i].transformMat);
	}
}
void TetrisShape::Translate(glm::vec3 _translation) {
	/*TODO: Change this so that it stops moving if it's collided with something*/
	if (position.z < -22) {	
		return;
	}

	position += _translation;
	transformMat = glm::translate(transformMat, _translation);
	for (int i = 0; i < boxes.size(); i++) {
		boxes[i].parentTransformMat = transformMat;
		boxes[i].Translate();
	}
	/*box1->parentTransformMat = transformMat;
	box2->parentTransformMat = transformMat;
	box3->parentTransformMat = transformMat;

	box1->Translate();
	box2->Translate();
	box3->Translate();*/
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
