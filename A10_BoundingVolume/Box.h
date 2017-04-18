#pragma once
#include "RE\ReEng.h"
#include "TetrisShape.h"

class Box
{
public:
	TetrisShape* parentShape;
	vector3 position;
	glm::quat quatRotation;
	vector3 pivotPoint;
	bool colliding;

	Box();
	~Box();

	void Translate(vector3 _translation);
	void Rotate(vector3 _axis, float _degrees);
	void DeleteBox();
};

