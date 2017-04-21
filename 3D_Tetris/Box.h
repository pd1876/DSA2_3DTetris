#pragma once
#include "RE\ReEng.h"

class Box
{
public:
	TetrisShape parentShape;
	
	glm::mat4 transformMat;
	ReEng::PrimitiveClass* boxModelPrim;

	glm::vec3 position;
	glm::vec3 pivotPoint;
	glm::quat quatRotation;
	
	bool colliding;

	Box();
	~Box();

	void SetPosition(glm::vec3 _position);
	void Translate(glm::vec3 _translation);
	void Rotate(glm::vec3 _axis, float _degrees);
	void DeleteBox();
};

