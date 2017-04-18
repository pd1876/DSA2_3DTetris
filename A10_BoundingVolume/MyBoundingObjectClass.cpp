#include "MyBoundingObjectClass.h"

MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> vertexList) {
	if (vertexList.size() < 1)
		return;

	v3Min = vertexList[0];
	v3Max = vertexList[0];

	for (int i = 1; i < vertexList.size(); i++) {
		if (v3Min.x > vertexList[i].x)
		{
			v3Min.x = vertexList[i].x;
		}
		else if (v3Max.x < vertexList[i].x)
		{
			v3Max.x = vertexList[i].x;
		}

		if (v3Min.y > vertexList[i].y)
		{
			v3Min.y = vertexList[i].y;
		}
		else if (v3Max.y < vertexList[i].y)
		{
			v3Max.y = vertexList[i].y;
		}

		if (v3Min.z > vertexList[i].z)
		{
			v3Min.z = vertexList[i].z;
		}
		else if (v3Max.z < vertexList[i].z)
		{
			v3Max.z = vertexList[i].z;
		}
	}

	localCenter = globalCenter = (v3Max + v3Min) / 2.0f;
	radius = glm::distance(globalCenter, v3Max);
	m_pMeshManager = MeshManagerSingleton::GetInstance();
	v3Size = v3Max - v3Min;
}

void MyBoundingObjectClass::RenderSphere(vector3 v3Color) {
	vector3 color = REGREEN;
	if (sphereColliding)
		color = RERED;

	m_pMeshManager->AddSphereToRenderList(
		glm::translate(globalCenter) *
		glm::scale(vector3(radius) * 2.0f),
		color,
		WIRE
	);
}

void MyBoundingObjectClass::RenderBox(vector3 v3Color) {
	vector3 color = REGREEN;
	if (boxColliding)
		color = REYELLOW;

	m_pMeshManager->AddCubeToRenderList(
		glm::translate(localCenter) *
		glm::scale(v3Size),
		color,
		WIRE
	);
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