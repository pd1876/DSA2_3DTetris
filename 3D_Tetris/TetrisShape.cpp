#include "TetrisShape.h"


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
	box1->SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	box1->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
}

void TetrisShape::Translate(glm::vec3 _translation) {
	position += _translation;
	transformMat = glm::translate(transformMat, _translation);
}
void TetrisShape::Rotate(glm::vec3 _axis, float _degrees) {

}
void TetrisShape::DeleteBox() {
	delete box1;
	delete box2;
	delete box3;
}
