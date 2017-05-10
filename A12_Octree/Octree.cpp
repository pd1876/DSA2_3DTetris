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

// Node* Octree::BuildOctree(vector3 _center, vector3 _halfWidth) {
// 		Node* temp = new Node();
// 		temp->center = _center;
// 		temp->halfWidth = _halfWidth;
// 
// 		vector3 offset;
// 		vector3 step = temp->halfWidth * 0.5f;
// 
// 		for (int i = 0; i < 8; i++) {
// 			offset.x = ((i & 1) ? step.x : -step.x);
// 			offset.y = ((i & 2) ? step.y : -step.y);
// 			offset.z = ((i & 4) ? step.z : -step.z);
// 			temp->nodes[i] = BuildOctree(temp->center + offset, step);
// 		}
// 
// 		return temp;
// }

Node* Octree::Divide(Node* node) {
	if (node->objList.size() == 0)
		return nullptr;
	
		Node* temp = new Node();
		temp->center = node->center;
		temp->halfWidth = node->halfWidth;

		vector3 offset;
		vector3 step = temp->halfWidth * 0.5f;

		// Okay so here is how this is supposed to work and I just can't code it
		/*
			1) If the code makes it to here, that means there was more than 10 objects generated checked already
			2) So it should first instatiate 8 children nodes, no questions asked
			3) Then it checks, out of the objects already accounted for, who ended up in what child
			4) After that it should keep going through the list of objects, but now by keeping track of all the children and each of them calling InsertObject
			5) Then if a child reaches 11 objects registered in its area, the divide method gets called again.
			6) And this all just keeps repeating until all the objects generated have been checked
		*/

/*
		for (int i = 0; i < 8; i++) {
			offset.x = ((i & 1) ? step.x : -step.x);
			offset.y = ((i & 2) ? step.y : -step.y);
			offset.z = ((i & 4) ? step.z : -step.z);
			temp->nodes[i] = Divide(temp->center + offset, step, objList);
		}

		for (int i = objList.size(); i > 0; i--) {
			InsertObject(temp, objList[i]);
			objList.pop_back();
		}
		*/
		return temp;
}

void Octree::InsertObject(Node* pTree, BOClass* object) {
	if (pTree->objList.size() <= pTree->maxObjects) {
		pTree->objList.push_back(object);
	}
	else {
		Divide(pTree);
	}
}

void Octree::displayOctree(Node* node) {
	m_pMeshMngr->AddCubeToRenderList(glm::translate(IDENTITY_M4, node->center) *
		glm::scale(node->halfWidth * 2.0f), REBROWN, WIRE);
}