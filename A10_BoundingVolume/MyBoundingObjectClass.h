#pragma once
#include "RE\ReEng.h"

class MyBoundingObjectClass {

private:
	float radius = 0.0f;
	vector3 localCenter = vector3(0.0f);
	vector3 globalCenter = vector3(0.0f);
	matrix4 toWorld = IDENTITY_M4;
	MeshManagerSingleton* m_pMeshManager = nullptr;
	bool sphereColliding = false;
	bool boxColliding = false;

	vector3 v3Min;
	vector3 v3Max;
	vector3 v3Size;

public:
	// Constructor to take in the model vertex
	MyBoundingObjectClass(std::vector<vector3> vertexList);

	/* 
		Get all the things
	*/

	// Get the centroid
	vector3 GetCentroid();

	// Get the minimum
	vector3 GetMinimum();

	// Get the maximum
	vector3 GetMaximum();

	// Get the model to world matrix
	matrix4 GetModeltoWorld();

	/* 
		Set all the things
	*/

	// Set transform from local to world
	void SetModelMatrix(matrix4 toWorld);

	/*
		Declare all the things
	*/

	// Render sphere with choice color
	void RenderSphere(vector3 v3Color);

	// Render Box with choice color
	void RenderBox(vector3 v3Color);

	// Check collision with spheres
	bool SphereIsColliding(MyBoundingObjectClass* other_sphere);

	// Check collision with boxes
	bool BoxIsColliding(MyBoundingObjectClass* other_box);

	// Check if boxes should be visible
	bool IsVisible();
};
