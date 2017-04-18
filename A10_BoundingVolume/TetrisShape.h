#pragma once
#include "RE\ReEng.h"
#include "Box.h"

class TetrisShape
{
public:
	std::vector<vector3> boxPositions;
	std::vector<Box> boxes;

	TetrisShape();
	~TetrisShape();
};

