#include "Box.h"


//We give Box a pointer to the mesh manager that AppClass is using to render models so that Box can load the correct model in
//we give Box an unique int that will identify each box for the mesh manager so that it knows which box to render. Kind of shitty but it is what it is
Box::Box(MeshManagerSingleton* _meshManager, int _boxID){
	//Generate the Cube
	/*boxModelPrim = new PrimitiveClass();
	boxModelPrim->GenerateCube(2.0f, RERED);*/

	boxName = std::to_string(_boxID);
	
	std::cout << "Box Name: " << boxName << std::endl;

	_meshManager->LoadModel("Portal\\CompanionCube.bto", boxName);

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