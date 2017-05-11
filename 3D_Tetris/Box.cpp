#include "Box.h"

int Box::globalBoxIDCount = 0;

//We give Box a pointer to the mesh manager that AppClass is using to render models so that Box can load the correct model in
//For now, the ID passed in does nothing and we just set the boxID to the globalBoxCount
Box::Box(MeshManagerSingleton* _meshManager, int _boxID){
	//Generate the Cube
	/*boxModelPrim = new PrimitiveClass();
	boxModelPrim->GenerateCube(2.0f, RERED);*/

	boxName = std::to_string(Box::globalBoxIDCount);
	boxID = Box::globalBoxIDCount;
	_meshManager->LoadModel("Portal\\CompanionCube.bto", boxName);

	globalBoxIDCount++;

	//SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));
}
Box::Box() {

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