#include "GameManager.h"



GameManager::GameManager()
{
	topPlaneTransform = glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	topPlaneTransform = glm::translate(topPlaneTransform, glm::vec3(0.0f, 0.0f, 6.0f));

	bottomPlaneTransform = glm::rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	bottomPlaneTransform = glm::translate(bottomPlaneTransform, glm::vec3(0.0f, 0.0f, 6.0f));

	rightPlaneTransform = glm::rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	rightPlaneTransform = glm::translate(rightPlaneTransform, glm::vec3(0.0f, 0.0f, 6.0f));

	leftPlaneTransform = glm::rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	leftPlaneTransform = glm::translate(leftPlaneTransform, glm::vec3(0.0f, 0.0f, 6.0f));
}

GameManager::~GameManager()
{

}

