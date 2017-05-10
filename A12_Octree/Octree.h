#pragma once
#include "RE\ReEng.h"
#include "BOClass.h"

struct Node {
	vector3 center;
	vector3 halfWidth;
	// list to hold nodes of tree
	Node* nodes[8];
	// list of contained items
	std::vector<BOClass*> objList;
	int maxObjects = 10;
};

class Octree {
	// whether to display the octree or not
	bool active;

	MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager Singleton

	// static pointer to class
	static Octree* instance;

public:
	Octree(void);

	// Get Instance
	static Octree* getInstance();

	// build the octree
	//Node* BuildOctree(vector3 _center, vector3 _halfWidth);

	Node* Divide(vector3 _center, vector3 _halfWidth, std::vector<BOClass*> objList);

	void InsertObject(Node* pTree, BOClass* object);

	// display the octree
	void displayOctree(Node* node);
	
	// Destructor
	~Octree();
};