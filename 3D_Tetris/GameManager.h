#pragma once
#include "Box.h"
#include "TetrisShape.h"


class GameManager
{
public:
	glm::mat4 topPlaneTransform;
	glm::mat4 bottomPlaneTransform;
	glm::mat4 rightPlaneTransform;
	glm::mat4 leftPlaneTransform;


	GameManager();
	~GameManager();
};

