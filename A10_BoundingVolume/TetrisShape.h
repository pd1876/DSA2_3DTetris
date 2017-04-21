#pragma once
#include "RE\ReEng.h"
#include "Box.h"

class TetrisShape
{
public:
	//std::vector<vector3> boxPositions;
	//std::vector<Box> boxes;

	void Translate(vector3 _translation);
	void Rotate(vector3 _axis, float _degrees);
	void DeleteBox();

	TetrisShape();
	~TetrisShape();
};

