#include "MyBoundingObjectClass.h"

MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> vertexList) {


}

void MyBoundingObjectClass::RenderSphere(vector3 v3Color) {

}

void MyBoundingObjectClass::RenderBox(vector3 v3Color) {

}

bool MyBoundingObjectClass::SphereIsColliding(MyBoundingObjectClass* other_sphere) {

	return false;
}

bool MyBoundingObjectClass::BoxIsColliding(MyBoundingObjectClass* other_box) {

	return false;
}

bool MyBoundingObjectClass::IsVisible() {
	return true;
}

void MyBoundingObjectClass::SetModelMatrix(matrix4 toWorld) { toWorld = IDENTITY_M4; }

vector3 MyBoundingObjectClass::GetCentroid() { return vector3(0.0f); };
vector3 MyBoundingObjectClass::GetMinimum() { return vector3(0.0f); };
vector3 MyBoundingObjectClass::GetMaximum() { return vector3(0.0f); };
matrix4 MyBoundingObjectClass::GetModeltoWorld() { return toWorld; };