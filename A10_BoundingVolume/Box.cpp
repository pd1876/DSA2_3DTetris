#include "Box.h"



Box::Box(){
	//Generate the Cube
	boxModelPrim = new PrimitiveClass();
	boxModelPrim->GenerateCube(5.0f, RERED);

	SetPosition(glm::vec3(0.0f, 1.0f, 2.0f));
}


Box::~Box(){

}
void Box::SetPosition(glm::vec3 _position) {
	position = _position;
}
void Box::Translate(glm::vec3 _translation) {
	positionMat = glm::translate(positionMat, _translation);
}
void Box::Rotate(glm::vec3 _axis, float _degrees) {

}
void Box::DeleteBox() {
	delete boxModelPrim;
}