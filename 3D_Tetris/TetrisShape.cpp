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

	box1->SetPosition(vector3(0.0f, 0.0f, 0.0f));
	box2->SetPosition(vector3(2.0f, 0.0f, 0.0f));
	box3->SetPosition(vector3(4.0f, 0.0f, 0.0f));

	// Initiate all the physics
	mass = 1.0f;
	velocity = vector3(0.01f, 0.01f, 0.01f);
	acceleration = vector3(0.0f, 0.0f, -0.001f);

	// When a shape is spawned, by default it should be falling
	isFalling = true;
}

void TetrisShape::Translate(vector3 _translation) {
	/*TODO: Change this so that it stops moving if it's collided with something*/
	if (position.z < -12) {
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

void TetrisShape::Fall() {

	if (position.z < -12) {
		acceleration = vector3(0.0f);
		isFalling = false;
		return;
	}

	velocity += acceleration * mass;
	position += velocity;

	transformMat = glm::translate(transformMat, velocity);

	box1->parentTransformMat = transformMat;
	box2->parentTransformMat = transformMat;
	box3->parentTransformMat = transformMat;

	box1->Translate();
	box2->Translate();
	box3->Translate();
}
void TetrisShape::Rotate(vector3 _axis, float _degrees) {

}
void TetrisShape::DeleteBox() {
	delete box1;
	delete box2;
	delete box3;
}
