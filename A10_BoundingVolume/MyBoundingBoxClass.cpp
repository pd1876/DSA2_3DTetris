#include "MyBoundingBoxClass.h"

MyBoundingBoxClass::MyBoundingBoxClass(std::vector<vector3> vertexList)
{
	m_bColliding = false;
	m_fRadius = 0.0f;
	m_v3CenterGlobal = vector3(0.0f);

	if (vertexList.size() < 1)
		return;

	m_v3Min = vertexList[0];
	m_v3Max = vertexList[0];

	for (int i = 1; i < vertexList.size(); i++)
	{
		if (m_v3Min.x > vertexList[i].x)
		{
			m_v3Min.x = vertexList[i].x;
		}
		else if (m_v3Max.x < vertexList[i].x)
		{
			m_v3Max.x = vertexList[i].x;
		}

		if (m_v3Min.y > vertexList[i].y)
		{
			m_v3Min.y = vertexList[i].y;
		}
		else if (m_v3Max.y < vertexList[i].y)
		{
			m_v3Max.y = vertexList[i].y;
		}

		if (m_v3Min.z > vertexList[i].z)
		{
			m_v3Min.z = vertexList[i].z;
		}
		else if (m_v3Max.z < vertexList[i].z)
		{
			m_v3Max.z = vertexList[i].z;
		}
	}

	m_v3CenterLocal = m_v3CenterGlobal = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3Max);
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3Size = m_v3Max - m_v3Min;

	m_v3MinG = m_v3Min;
	m_v3MaxG = m_v3Max;
}

void MyBoundingBoxClass::CalculateReAlignedBoxVerts() {
	vector3 diagonal = m_v3MaxG - m_v3MinG;


}
void MyBoundingBoxClass::RenderBox()
{
	vector3 v3Color = REGREEN;
	if (m_bColliding)
		v3Color = RERED;

	m_pMeshMngr->AddCubeToRenderList(
		m_m4ToWorld *
		glm::translate(m_v3CenterLocal) *
		glm::scale(m_v3Size),
		v3Color, WIRE);


}

void MyBoundingBoxClass::RenderVolumeBox(std::vector<vector3> vertexList) {

	vector3 v3Color = REBLUE;
	if (m_bColliding)
		v3Color = REYELLOW;

	vector3 p1 = vector3(m_v3Min);
	vector3 p2 = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	vector3 p3 = vector3(m_v3Max.x,m_v3Min.y,m_v3Min.z);
	vector3 p4 = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	vector3 p5 = vector3(m_v3Min.x,m_v3Max.y,m_v3Max.z);
	vector3 p6 = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	vector3 p7 = vector3(m_v3Max.x,m_v3Max.y,m_v3Min.z);
	vector3 p8 = vector3(m_v3Max);
	//vector3 diag = m_v3MaxG - m_v3MinG;
	std::vector<vector3> volumeList;
	volumeList.push_back(p1);
	volumeList.push_back(p2);
	volumeList.push_back(p3);
	volumeList.push_back(p4);
	volumeList.push_back(p5);
	volumeList.push_back(p6);
	volumeList.push_back(p7);
	volumeList.push_back(p8);
	for (int i = 0; i < 8; i++) {
		volumeList[i] = vector3(m_m4ToWorld * vector4(volumeList[i], 1.0f));
	}
	
	vector3 localMinCopy = volumeList[0];
	vector3 localMaxCopy = volumeList[0];

	for (int i = 1; i < volumeList.size(); i++)
	{
		if (localMinCopy.x > volumeList[i].x)
		{
			localMinCopy.x = volumeList[i].x;
		}
		else if (localMaxCopy.x < volumeList[i].x)
		{
			localMaxCopy.x = volumeList[i].x;
		}



		if (localMinCopy.y > volumeList[i].y)
		{
			localMinCopy.y = volumeList[i].y;
		}
		else if (localMaxCopy.y < volumeList[i].y)
		{
			localMaxCopy.y = volumeList[i].y;
		}



		if (localMinCopy.z > volumeList[i].z)
		{
			localMinCopy.z = volumeList[i].z;
		}
		else if (localMaxCopy.z < volumeList[i].z)
		{
			localMaxCopy.z = volumeList[i].z;
		}
	}
	m_v3SizeG = localMaxCopy - localMinCopy;
	m_pMeshMngr->AddCubeToRenderList(
		glm::translate(m_v3CenterGlobal) * 
		glm::scale(m_v3SizeG),
		v3Color, WIRE);

	std::cout << vertexList[1].x;
}

void MyBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	m_v3CenterGlobal = vector3(m_m4ToWorld * vector4(m_v3CenterLocal, 1.0f));
	m_v3MinG = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	m_v3MaxG = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));
}

bool MyBoundingBoxClass::IsColliding(MyBoundingBoxClass* a_other)
{
	if (this->m_v3MaxG.x < a_other->m_v3MinG.x)
		return false;
	if (this->m_v3MinG.x > a_other->m_v3MaxG.x)
		return false;

	if (this->m_v3MaxG.y < a_other->m_v3MinG.y)
		return false;
	if (this->m_v3MinG.y > a_other->m_v3MaxG.y)
		return false;

	if (this->m_v3MaxG.z < a_other->m_v3MinG.z)
		return false;
	if (this->m_v3MinG.z > a_other->m_v3MaxG.z)
		return false;

	return true;
}

void MyBoundingBoxClass::SetColliding(bool input) { m_bColliding = input; }
void MyBoundingBoxClass::SetCenterLocal(vector3 input) { m_v3CenterLocal = input; }
void MyBoundingBoxClass::SetCenterGlobal(vector3 input) { m_v3CenterGlobal = input; }
void MyBoundingBoxClass::SetRadius(float input) { m_fRadius = input; }
bool MyBoundingBoxClass::GetColliding(void) { return m_bColliding; }
vector3 MyBoundingBoxClass::GetCenterLocal(void) { return m_v3CenterLocal; }
vector3 MyBoundingBoxClass::GetCenterGlobal(void) { return m_v3CenterGlobal; }
float MyBoundingBoxClass::GetRadius(void) { return m_fRadius; }
matrix4 MyBoundingBoxClass::GetModelMatrix(void) { return m_m4ToWorld; }