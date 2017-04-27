#pragma once
#include "Box.h"
#include "TetrisShape.h"


class GameManager
{
public:
	glm::mat4 topPlaneTransform = IDENTITY_M4;
	glm::mat4 bottomPlaneTransform = IDENTITY_M4;
	glm::mat4 rightPlaneTransform = IDENTITY_M4;
	glm::mat4 leftPlaneTransform = IDENTITY_M4;


	GameManager();
	~GameManager();
};

