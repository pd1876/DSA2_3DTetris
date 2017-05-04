#include "BOManager.h"
//  BOManager
BOManager* BOManager::m_pInstance = nullptr;
void BOManager::Init(void)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_nObjectCount = 0;
}
void BOManager::Release(void)
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		if (m_lObject[nObject] != nullptr)
		{
			delete m_lObject[nObject];
			m_lObject[nObject] = nullptr;
		}
		m_llCollidingIndices[nObject].clear();
	}
	m_lObject.clear();
	m_llCollidingIndices.clear();
}
BOManager* BOManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new BOManager();
	}
	return m_pInstance;
}
void BOManager::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
BOManager::BOManager() { Init(); }
BOManager::BOManager(BOManager const& other) { }
BOManager& BOManager::operator=(BOManager const& other) { return *this; }
BOManager::~BOManager() { Release(); };
//Accessors
BOClass* BOManager::GetBoundingObject(String a_sIndex)
{
	int nIndex = GetIndex(a_sIndex);
	return GetBoundingObject(nIndex);
}
BOClass* BOManager::GetBoundingObject(uint a_nIndex)
{
	if (a_nIndex < m_nObjectCount)
		return m_lObject[a_nIndex];

	return nullptr;
}
//--- Non Standard Singleton Methods
void BOManager::AddObject(String a_sName)
{
	std::vector<vector3> lVertex = m_pMeshMngr->GetVertexList(a_sName);
	AddObject(lVertex, a_sName);
	SetModelMatrix(m_pMeshMngr->GetModelMatrix(a_sName), a_sName);
}
void BOManager::AddObject(std::vector<vector3> a_lVertex, String a_sName)
{
	BOClass* pObject = new BOClass(a_lVertex);
	if (pObject != nullptr)
	{
		m_lObject.push_back(pObject);//Add the Object
		m_mapIndex[a_sName] = m_nObjectCount; //Add entry to the dictionary
	}
	m_nObjectCount = m_lObject.size();
	std::vector<int> lVector;
	m_llCollidingIndices.push_back(lVector);
}
void BOManager::SetModelMatrix(matrix4 a_mModelMatrix, String a_sIndex)
{
	//find the object
	int nIndex = this->GetIndex(a_sIndex);
	if (nIndex < 0) //if not found return
		return;

	m_lObject[nIndex]->SetModelMatrix(a_mModelMatrix);//set the matrix for the indexed Object
}
void BOManager::DisplaySphere(String a_sName, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_sName);
	DisplaySphere(nIndex, a_v3Color);
}
void BOManager::DisplaySphere(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		//Default will render in white for non colliding and red for colliding
		if (v3Color == REDEFAULT)
		{
			v3Color = REWHITE;
			if (m_llCollidingIndices[a_nIndex].size() > 0)
				v3Color = RERED;
		}
		m_lObject[a_nIndex]->DisplaySphere(v3Color);
	}
	else //all objects sent
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			//Default will render in white for non colliding and red for colliding
			if (v3Color == REDEFAULT)
			{
				v3Color = REWHITE;
				if (m_llCollidingIndices[nObject].size() > 0)
					v3Color = RERED;
			}
			m_lObject[nObject]->DisplaySphere(v3Color);
			v3Color = a_v3Color;
		}
	}
}
void BOManager::DisplayOriented(String a_sName, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_sName);
	DisplayOriented(nIndex, a_v3Color);
}
void BOManager::DisplayOriented(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists
	if (a_nIndex >= 0)
	{
		//Default will render in white for non colliding and red for colliding
		if (v3Color == REDEFAULT)
		{
			v3Color = REWHITE;
			if (m_llCollidingIndices[a_nIndex].size() > 0)
				v3Color = RERED;
		}
		m_lObject[a_nIndex]->DisplayOriented(v3Color);
	}
	else
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			//Default will render in white for non colliding and red for colliding
			if (v3Color == REDEFAULT)
			{
				v3Color = REWHITE;
				if (m_llCollidingIndices[nObject].size() > 0)
					v3Color = RERED;
			}
			m_lObject[nObject]->DisplayOriented(v3Color);
			v3Color = a_v3Color;
		}
	}
}
void BOManager::DisplayReAlligned(String a_sName, vector3 a_v3Color)
{
	int nIndex = GetIndex(a_sName);
	DisplayReAlligned(nIndex, a_v3Color);
}
void BOManager::DisplayReAlligned(int a_nIndex, vector3 a_v3Color)
{
	//If the index is larger than the number of objects stored return with no changes
	if (a_nIndex >= static_cast<int>(m_nObjectCount))
		return;

	vector3 v3Color = a_v3Color;
	//if The index exists we are talking about a single asset
	if (a_nIndex >= 0)
	{
		//Default will render in white for non colliding and red for colliding
		if (v3Color == REDEFAULT)
		{
			v3Color = REWHITE;
			if (m_llCollidingIndices[a_nIndex].size() > 0)
				v3Color = RERED;
		}
		m_lObject[a_nIndex]->DisplayReAlligned(v3Color);
	}
	else //we want to render all of them
	{
		for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
		{
			//Default will render in white for non colliding and red for colliding
			if (v3Color == REDEFAULT)
			{
				v3Color = REWHITE;
				if (m_llCollidingIndices[nObject].size() > 0)
					v3Color = RERED;
			}
			m_lObject[nObject]->DisplayReAlligned(v3Color);
			v3Color = a_v3Color;
		}
	}
}
void BOManager::Update(void)
{
	for (uint nObject = 0; nObject < m_nObjectCount; nObject++)
	{
		m_llCollidingIndices[nObject].clear();
	}
	CheckCollisions();
}
void BOManager::CheckCollisions(void)
{
	for (uint nObjectA = 0; nObjectA < m_nObjectCount - 1; nObjectA++)
	{
		for (uint nObjectB = nObjectA + 1; nObjectB < m_nObjectCount; nObjectB++)
		{
			if (m_lObject[nObjectA]->IsColliding(m_lObject[nObjectB]))
			{
				m_llCollidingIndices[nObjectA].push_back(nObjectB);
				m_llCollidingIndices[nObjectB].push_back(nObjectA);
			}
		}
	}
}
std::vector<int> BOManager::GetCollidingVector(String a_sIndex)
{
	int nIndex = GetIndex(a_sIndex);
	if (nIndex < 0)
	{
		std::vector<int> empty;
		return empty;
	}
	return GetCollidingVector(static_cast<uint>(nIndex));
}
std::vector<int> BOManager::GetCollidingVector(uint a_nIndex)
{
	if (a_nIndex >= m_nObjectCount)
	{
		std::vector<int> empty;
		return empty;
	}
	return m_llCollidingIndices[a_nIndex];
}
int BOManager::GetIndex(String a_sIndex)
{
	//Find the related index
	auto var = m_mapIndex.find(a_sIndex);
	//If not found return -1
	if (var == m_mapIndex.end())
		return -1;
	return var->second;//Get the index
}