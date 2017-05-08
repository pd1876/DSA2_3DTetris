#pragma once
#include "RE\ReEng.h"

class Octree {
	// bounds of the octree
	// All in global space
	// Passed in by an object's global vectors
	vector3 center = vector3(0.0f);
	vector3 min = vector3(0.0f);
	vector3 max = vector3(0.0f);
	vector3 halfWidth = vector3(0.0f);

	// whether to display the octree or not
	bool active;

	MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager Singleton

	// static pointer to class
	static Octree* instance;
public:
	Octree(void);

	// Get Instance
	static Octree* getInstance();

	// display the octree
	void displayOctree(vector3 _center, vector3 _min, vector3 _max, vector3 _halfWidth, float counter);

	// Destructor
	~Octree();
};