#pragma once
#include "RE\ReEng.h"

class MyBoundingBoxClass
{
private:
	float m_fRadius = 0.0f; //radius of the box
	vector3 m_v3CenterLocal = vector3(0.0f); //center of the box in local space
	vector3 m_v3CenterGlobal = vector3(0.0f); //center of the box in global space
	matrix4 m_m4ToWorld = IDENTITY_M4; //matrix that takes you from local to global space
	MeshManagerSingleton* m_pMeshMngr = nullptr; //for drawing the box
	bool m_bColliding = false;

	vector3 m_v3Max;
	vector3 m_v3Min;
	vector3 m_v3Size;

	vector3 m_v3MaxG;
	vector3 m_v3MinG;
	vector3 m_v3SizeG;
public:
	/*
	* Calculates ReAligned bounding box vertice
	*/
	void CalculateReAlignedBoxVerts();

	/*Sets Colliding
	*/
	void SetColliding(bool input);
	/*
	Sets Center of the box in local space
	*/
	void SetCenterLocal(vector3 input);
	/*
	Sets Center of the box in global space
	*/
	void SetCenterGlobal(vector3 input);
	/*
	Sets the radius of the box
	*/
	void SetRadius(float input);

	/*
	Gets Colliding
	*/
	bool GetColliding(void);
	/*
	Gets center of the box in local space
	*/
	vector3 GetCenterLocal(void);
	/*
	Gets center of the box in global space
	*/
	vector3 GetCenterGlobal(void);
	/*
	Gets model to world matrix of the box
	*/
	matrix4 GetModelMatrix(void);
	/*
	Gets radius of the box
	*/
	float GetRadius(void);

	/*
	Constructor, needs a vertex list
	*/
	MyBoundingBoxClass(std::vector<vector3> vertexList);
	/*
	Renders the box based on the radius and the center in global space
	*/
	void RenderBox();
	/*
	Renders a box based on the farthest points on the first box - excellent
	*/
	void RenderVolumeBox(std::vector<vector3> vertexList);
	/*
	Sets the transform from the local to world matrix
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);

	/*
	Will check the collision with another object
	*/
	bool IsColliding(MyBoundingBoxClass* a_other);
};