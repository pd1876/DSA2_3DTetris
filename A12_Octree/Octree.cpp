#include "Octree.h"

Octree* Octree::instance = nullptr;
// Constructor
Octree::Octree() {
	vector3 center = vector3(0.0f);
	vector3 min = vector3(0.0f);
	vector3 max = vector3(0.0f);
	vector3 halfWidth = vector3(0.0f);

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
};

Octree* Octree::getInstance() {
	if (instance == nullptr)
	{
		instance = new Octree();
	}
	return instance;
}

void Octree::displayOctree(vector3 _center, vector3 _min, vector3 _max, vector3 _halfWidth) {
	center = _center;
	min = _min;
	max = _max;
	halfWidth = _halfWidth;
	m_pMeshMngr->AddCubeToRenderList(glm::translate(IDENTITY_M4, center) *
		glm::scale(halfWidth * 2.0f), REBLACK, WIRE);
	m_pMeshMngr->PrintLine("Center" + std::to_string(center.x) + ", " + std::to_string(center.y) + ", " + std::to_string(center.z));
};