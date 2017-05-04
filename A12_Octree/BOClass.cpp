#include "BOClass.h"

//  BOClass
void BOClass::Init(void)
{
	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_v3CenterG = vector3(0.0f);
	m_v3MinG = vector3(0.0f);
	m_v3MaxG = vector3(0.0f);

	m_v3HalfWidth = vector3(0.0f);
	m_v3HalfWidthG = vector3(0.0f);

	m_fRadius = 0.0f;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}
void BOClass::Swap(BOClass& other)
{
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_v3CenterG, other.m_v3CenterG);
	std::swap(m_v3MinG, other.m_v3MinG);
	std::swap(m_v3MaxG, other.m_v3MaxG);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
	std::swap(m_v3HalfWidthG, other.m_v3HalfWidthG);

	std::swap(m_fRadius, other.m_fRadius);

	std::swap(m_pMeshMngr, other.m_pMeshMngr);
}
void BOClass::Release(void) {/* No pointers allocated yet */ }
//The big 3
BOClass::BOClass(std::vector<vector3> a_lVectorList)
{
	//Init the default values
	Init();

	//Count the points of the incoming list
	uint nVertexCount = a_lVectorList.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = a_lVectorList[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > a_lVectorList[nVertex].x) //If min is larger than current
			m_v3Min.x = a_lVectorList[nVertex].x;
		else if (m_v3Max.x < a_lVectorList[nVertex].x)//if max is smaller than current
			m_v3Max.x = a_lVectorList[nVertex].x;

		if (m_v3Min.y > a_lVectorList[nVertex].y) //If min is larger than current
			m_v3Min.y = a_lVectorList[nVertex].y;
		else if (m_v3Max.y < a_lVectorList[nVertex].y)//if max is smaller than current
			m_v3Max.y = a_lVectorList[nVertex].y;

		if (m_v3Min.z > a_lVectorList[nVertex].z) //If min is larger than current
			m_v3Min.z = a_lVectorList[nVertex].z;
		else if (m_v3Max.z < a_lVectorList[nVertex].z)//if max is smaller than current
			m_v3Max.z = a_lVectorList[nVertex].z;
	}

	//with the max and the min we calculate the center
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	m_fRadius = glm::distance(m_v3Center, m_v3Max);

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f;

	m_v3MaxG = m_v3Max;
	m_v3MinG = m_v3Min;
	m_v3CenterG = m_v3Center;
	m_v3HalfWidthG = m_v3HalfWidth;
}
BOClass::BOClass(BOClass const& other)
{
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3CenterG = other.m_v3CenterG;
	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3HalfWidthG = other.m_v3HalfWidthG;

	m_fRadius = other.m_fRadius;

	m_pMeshMngr = other.m_pMeshMngr;
}
BOClass& BOClass::operator=(BOClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		BOClass temp(other);
		Swap(temp);
	}
	return *this;
}
BOClass::~BOClass() { Release(); };
//Accessors
void BOClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	//If there are no changes in the Model Matrix there is no need
	//of doing further calculations
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	//Calculate the vertex that makes the Object
	vector3 v3Corner[8];
	v3Corner[0] = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
	v3Corner[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	v3Corner[2] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	v3Corner[3] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);

	v3Corner[4] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	v3Corner[5] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	v3Corner[6] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	v3Corner[7] = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z);
	//Get vectors in global space
	for (uint nVertex = 0; nVertex < 8; nVertex++)
	{
		v3Corner[nVertex] = vector3(m_m4ToWorld * vector4(v3Corner[nVertex], 1.0f));
	}

	//Get the max and min out of the list
	m_v3MaxG = m_v3MinG = v3Corner[0];
	for (uint nVertex = 1; nVertex < 8; nVertex++)
	{
		if (m_v3MinG.x > v3Corner[nVertex].x) //If min is larger than current
			m_v3MinG.x = v3Corner[nVertex].x;
		else if (m_v3MaxG.x < v3Corner[nVertex].x)//if max is smaller than current
			m_v3MaxG.x = v3Corner[nVertex].x;

		if (m_v3MinG.y > v3Corner[nVertex].y) //If min is larger than current
			m_v3MinG.y = v3Corner[nVertex].y;
		else if (m_v3MaxG.y < v3Corner[nVertex].y)//if max is smaller than current
			m_v3MaxG.y = v3Corner[nVertex].y;

		if (m_v3MinG.z > v3Corner[nVertex].z) //If min is larger than current
			m_v3MinG.z = v3Corner[nVertex].z;
		else if (m_v3MaxG.z < v3Corner[nVertex].z)//if max is smaller than current
			m_v3MaxG.z = v3Corner[nVertex].z;
	}
	m_v3CenterG = (m_v3MinG + m_v3MaxG) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidthG = (m_v3MaxG - m_v3MinG) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterG, m_v3MaxG);
}
float BOClass::GetRadius(void) { return m_fRadius; }
matrix4 BOClass::GetModelMatrix(void) { return m_m4ToWorld; }
vector3 BOClass::GetCenterLocal(void) { return m_v3Center; }
vector3 BOClass::GetCenterGlobal(void) { return m_v3CenterG; }
vector3 BOClass::GetHalfWidth(void) { return m_v3HalfWidth; }
vector3 BOClass::GetHalfWidthG(void) { return m_v3HalfWidthG; }
vector3 BOClass::GetMin(void) { return m_v3Min; }
vector3 BOClass::GetMax(void) { return m_v3Max; }
vector3 BOClass::GetMinG(void) { return m_v3MinG; }
vector3 BOClass::GetMaxG(void) { return m_v3MaxG; }
//--- Non Standard Singleton Methods
void BOClass::DisplaySphere(vector3 a_v3Color)
{
	m_pMeshMngr->AddSphereToRenderList(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(vector3(m_fRadius * 2.0f)), a_v3Color, WIRE);
}
void BOClass::DisplayOriented(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(m_v3HalfWidth * 2.0f), a_v3Color, WIRE);
}
void BOClass::DisplayReAlligned(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(IDENTITY_M4, m_v3CenterG) *
		glm::scale(m_v3HalfWidthG * 2.0f), a_v3Color, WIRE);
}
bool BOClass::CheckAxis(BOClass* _other, vector3 _axis) {
	// Found Collision Detection help from this website
	/*
	https://gamedevelopment.tutsplus.com/tutorials/collision-detection-using-the-separating-axis-theorem--gamedev-169
	*/
	// Project the min and max of each object onto an arbitrary axis
	float myMaxProjection = glm::dot(m_v3MaxG, _axis);
	float myMinProjection = glm::dot(m_v3MinG, _axis);
	float otherMaxProjection = glm::dot(_other->m_v3MaxG, _axis);
	float otherMinProjection = glm::dot(_other->m_v3MinG, _axis);

	m_pMeshMngr->PrintLine("My Max Projection: " + std::to_string(myMaxProjection));
	m_pMeshMngr->PrintLine("My Min Projection: " + std::to_string(myMinProjection));
	m_pMeshMngr->PrintLine("Other Max Projection: " + std::to_string(otherMaxProjection));
	m_pMeshMngr->PrintLine("Other Min Projection: " + std::to_string(otherMinProjection));


	// check for collision
	return (otherMaxProjection < myMinProjection || myMaxProjection < otherMinProjection);

	// Following from the book in the GDD library

	float ra;
	float rb;

	vector3 v3_Rotate[3] = {
		vector3(m_m4ToWorld[0][0], m_m4ToWorld[0][1], m_m4ToWorld[0][2]),
		vector3(m_m4ToWorld[1][0], m_m4ToWorld[1][1], m_m4ToWorld[1][2]),
		vector3(m_m4ToWorld[2][0], m_m4ToWorld[2][1], m_m4ToWorld[2][2])
	};

	vector3 v3_absolute[3];
	// Compute a rotation matrix expressing b in a's plane
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			v3_Rotate[i][j] = glm::dot(m_v3LocalAxis[i], _other->m_v3LocalAxis[j]);
		}
	}

	// Compute a translation vector t (??)
	vector3 t = m_v3Center - _other->m_v3Center;

	t = vector3(glm::dot(t, v3_Rotate[0]), glm::dot(t, v3_Rotate[1]), glm::dot(t, v3_Rotate[2]));

	// Computer common whatevers
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			v3_absolute[i][j] = glm::abs(v3_Rotate[i][j]) + FLT_EPSILON;
		}
	}

	// Test all the axes
	for (int i = 0; i < 3; i++) {
		ra = m_v3Center[i];
		rb = _other->m_v3Center[0] * v3_absolute[i][0] + _other->m_v3Center[1] * v3_absolute[i][1] + _other->m_v3Center[2] * v3_absolute[i][2];
		if (glm::abs(t[i]) > ra + rb)
			return 0;
	}

	for (int i = 0; i < 3; i++) {
		rb = _other->m_v3Center[i];
		rb = m_v3Center[0] * v3_absolute[i][0] + m_v3Center[1] * v3_absolute[i][1] + m_v3Center[2] * v3_absolute[i][2];
		if (glm::abs(t[0] * v3_Rotate[0][i] + t[1] * v3_Rotate[1][i] + t[2] * v3_Rotate[2][i]) > ra + rb)
			return 0;
	}

	ra = m_v3Center[1] * v3_absolute[2][0] + m_v3Center[2] * v3_absolute[1][0];
	rb = _other->m_v3Center[1] * v3_absolute[0][2] + _other->m_v3Center[2] * v3_absolute[0][1];
	if (glm::abs(t[2] * v3_Rotate[1][0] - t[1] * v3_Rotate[2][0]) > ra + rb)
		return 0;

	ra = m_v3Center[1] * v3_absolute[2][1] + m_v3Center[2] * v3_absolute[1][1];
	rb = _other->m_v3Center[0] * v3_absolute[0][2] + _other->m_v3Center[2] * v3_absolute[0][0];
	if (glm::abs(t[2] * v3_Rotate[1][1] - t[1] * v3_Rotate[2][1]) > ra + rb)
		return 0;

	ra = m_v3Center[1] * v3_absolute[2][2] + m_v3Center[2] * v3_absolute[1][2];
	rb = _other->m_v3Center[0] * v3_absolute[0][1] + _other->m_v3Center[1] * v3_absolute[0][0];
	if (glm::abs(t[2] * v3_Rotate[1][2] - t[1] * v3_Rotate[2][2]) > ra + rb)
		return 0;

	ra = m_v3Center[0] * v3_absolute[2][0] + m_v3Center[2] * v3_absolute[1][2];
	rb = _other->m_v3Center[1] * v3_absolute[1][2] + _other->m_v3Center[2] * v3_absolute[1][1];
	if (glm::abs(t[0] * v3_Rotate[2][0] - t[2] * v3_Rotate[0][0]) > ra + rb) return 0;

	ra = m_v3Center[0] * v3_absolute[2][1] + m_v3Center[2] * v3_absolute[0][1];
	rb = _other->m_v3Center[0] * v3_absolute[1][2] + _other->m_v3Center[2] * v3_absolute[1][0];
	if (glm::abs(t[0] * v3_Rotate[2][1] - t[2] * v3_Rotate[0][1]) > ra + rb) return 0;

	ra = m_v3Center[0] * v3_absolute[2][2] + m_v3Center[2] * v3_absolute[0][2];
	rb = _other->m_v3Center[0] * v3_absolute[1][1] + _other->m_v3Center[1] * v3_absolute[1][0];
	if (glm::abs(t[0] * v3_Rotate[2][2] - t[2] * v3_Rotate[0][2]) > ra + rb) return 0;

	ra = m_v3Center[0] * v3_absolute[1][0] + m_v3Center[1] * v3_absolute[0][0];
	rb = _other->m_v3Center[1] * v3_absolute[2][2] + _other->m_v3Center[2] * v3_absolute[2][1];
	if (glm::abs(t[1] * v3_Rotate[0][0] - t[0] * v3_Rotate[1][0]) > ra + rb) return 0;

	ra = m_v3Center[0] * v3_absolute[1][1] + m_v3Center[1] * v3_absolute[0][1];
	rb = _other->m_v3Center[0] * v3_absolute[2][2] + _other->m_v3Center[2] * v3_absolute[2][0];
	if (glm::abs(t[1] * v3_Rotate[0][1] - t[0] * v3_Rotate[1][1]) > ra + rb) return 0;

	ra = m_v3Center[0] * v3_absolute[1][2] + m_v3Center[1] * v3_absolute[0][2];
	rb = _other->m_v3Center[0] * v3_absolute[2][1] + _other->m_v3Center[1] * v3_absolute[2][0];
	if (glm::abs(t[1] * v3_Rotate[0][2] - t[0] * v3_Rotate[1][2]) > ra + rb) return 0;

	// Since no separating axis is found, the OBBs must be intersecting
	return 1;
}

bool BOClass::IsColliding(BOClass* const a_pOther)
{
	//Get all vectors in global space
	vector3 v3Min = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 v3Max = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 v3MinO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
	vector3 v3MaxO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));

	/*
	Are they colliding?
	For Objects we will assume they are colliding, unless at least one of the following conditions is not met
	*/


	//If the distance was smaller it might be colliding
	//we will use the ReAligned box for the second check, notice that as long as one check return true they are 
	//not colliding thus else statements.

	//Check for X
	if (m_v3MaxG.x < a_pOther->m_v3MinG.x)
		return false;
	else if (m_v3MinG.x > a_pOther->m_v3MaxG.x)
		return false;

	//Check for Y
	else if (m_v3MaxG.y < a_pOther->m_v3MinG.y)
		return false;
	else if (m_v3MinG.y > a_pOther->m_v3MaxG.y)
		return false;

	//Check for Z
	else if (m_v3MaxG.z < a_pOther->m_v3MinG.z)
		return false;
	else if (m_v3MinG.z > a_pOther->m_v3MaxG.z)
		return false;

	return true;
}