#include "Box.h"



Box::Box(){
	//Generate the Cube
	boxModelPrim = new PrimitiveClass();
	boxModelPrim->GenerateCube(2.0f, RERED);
	mass = 0.01f;

	SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

Box::~Box(){

}
void Box::SetPosition(glm::vec3 _position) {
	position = _position;
}
void Box::Translate() {
	transformMat = glm::translate(parentTransformMat, position);
}
void Box::Rotate(glm::vec3 _axis, float _degrees) {

}
void Box::DeleteBox() {
	delete boxModelPrim;
}