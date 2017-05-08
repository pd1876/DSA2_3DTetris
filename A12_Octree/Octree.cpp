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

void Octree::displayOctree(vector3 _center, vector3 _min, vector3 _max, vector3 _halfWidth, float counter) {
	if (counter <= 0)
		return;
	else {
		center = _center;
		min = _min;
		max = _max;
		halfWidth = _halfWidth;
		m_pMeshMngr->AddCubeToRenderList(glm::translate(IDENTITY_M4, center) *
			glm::scale(halfWidth * 2.0f), REBLACK, WIRE);

		displayOctree((_center + _min) / 2.0f, _min, _center, (_center - _min) / 2.0f, counter - 1);

		displayOctree((_center + _max) / 2.0f, _center, _max, (_max - _center) / 2.0f, counter - 1);

		displayOctree((_center + vector3(_max.x, _max.y, _min.z)) / 2.0f, _center, vector3(_max.x, _max.y, _min.z), (vector3(_max.x, _max.y, _min.z) - _center) / 2.0f, counter - 1);

		displayOctree((_center + vector3(_min.x, _max.y, _min.z)) / 2.0f, (_min + vector3(_min.x, _max.y, _min.z)) / 2.0f,
			(_center + vector3(0.0f, _max.y, 0.0f)) / 2.0f, (vector3(_max.x, _max.y, _min.z) - _center) / 2.0f, counter - 1);

		displayOctree((_center + _min) / 2.0f, _min, _center, (_center - _min) / 2.0f, counter - 1);

		return;
	}
};