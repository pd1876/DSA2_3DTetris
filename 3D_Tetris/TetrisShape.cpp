#include "TetrisShape.h"

//-----------See Tetrisshape.h for comments-----------

TetrisShape::TetrisShape(){
	InitBoxes();
}

TetrisShape::~TetrisShape(){

}

void TetrisShape::InitBoxes() {
	box1 = new Box();
	box2 = new Box();
	box3 = new Box();

	box1->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	box2->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
	box3->SetPosition(glm::vec3(4.0f, 0.0f, 0.0f));
}

void TetrisShape::Translate(glm::vec3 _translation) {
	/*TODO: Change this so that it stops moving if it's collided with something*/
	if (position.z < -22) {	
		return;
	}

	position += _translation;
	transformMat = glm::translate(transformMat, _translation);

	box1->parentTransformMat = transformMat;
	box2->parentTransformMat = transformMat;
	box3->parentTransformMat = transformMat;

	box1->Translate();
	box2->Translate();
	box3->Translate();
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
}
