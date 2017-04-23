#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	//Flag for the modifier
	bool bModifier = false;

	//ON PRESS/RELEASE
#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion
	
	// John's Previous Camera Code
	/*
	cam1->mousedX = sf::Mouse::getPosition().x - cam1->mouseXLastFrame;
	cam1->mousedY = sf::Mouse::getPosition().y - cam1->mouseYLastFrame;
	
	cam1->mouseXLastFrame = sf::Mouse::getPosition().x;
	cam1->mouseYLastFrame = sf::Mouse::getPosition().y;

	//Change Yaw
	if (cam1->mousedX > 0) {
		cam1->ChangeYaw(cam1->mousedX * cam1->mouseSensitivityHoriz);
	}

	if (cam1->mousedX < 0) {
		cam1->ChangeYaw(cam1->mousedX * cam1->mouseSensitivityHoriz);
	}


	/*Change Pitch
	if (cam1->mousedY > 0) {
		cam1->ChangePitch(cam1->mousedY * cam1->mouseSensitivityVert);
	}

	if (cam1->mousedY < 0) {
		cam1->ChangePitch(cam1->mousedY * cam1->mouseSensitivityVert);
	}*/


	//Forward / Backward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		testShape1->Translate(glm::vec3(0.0f, 0.05f, 0.0f));
		//cam1->MoveForward(0.2f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		testShape1->Translate(glm::vec3(0.0f, -0.05f, 0.0f));
		//cam1->MoveForward(-0.2f);
	}

	//Right / Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		testShape1->Translate(glm::vec3(-0.05f, 0.0f, 0.0f));
		//cam1->MoveSideways(0.2f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//cam1->MoveSideways(-0.2f);
		testShape1->Translate(glm::vec3(0.05f, 0.0f, 0.0f));
	}


	//Rotate Right / Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		testShape1->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), 1);
		//cam1->MoveSideways(0.2f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//cam1->MoveSideways(-0.2f);
		testShape1->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), -1);
	}

	//Rotate up / down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		testShape1->Rotate(glm::vec3(1.0f, 0.0f, 0.0f), 1);
		//cam1->MoveSideways(0.2f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//cam1->MoveSideways(-0.2f);
		testShape1->Rotate(glm::vec3(1.0f, 0.0f, 0.0f), -1);
	}

	// Camera on Z-axis
	// Facing Front
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		cam1->SetView(glm::lookAt(vector3(0.0f, 0.0f, -20.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 1.0f, 0.0f)));
	}
	// Camera on Z-axis
	// Facing Back
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		cam1->SetView(glm::lookAt(vector3(0.0f, 0.0f, 20.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 1.0f, 0.0f)));
	}
	// Camera on X-axis
	// Facing Right Side
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
		cam1->SetView(glm::lookAt(vector3(20.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 1.0f, 0.0f)));
	}
	// Camera on X-axis
	// Facing Left Side
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
		cam1->SetView(glm::lookAt(vector3(-20.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 1.0f, 0.0f)));
	}
	// Camera on Y-axis
	// Facing Top Down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
		cam1->SetView(glm::lookAt(vector3(0.0f, 20.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 1.0f)));
	}
	// Camera on Y-axis
	// Facing Bottom
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
		cam1->SetView(glm::lookAt(vector3(0.0f, -20.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 1.0f)));
	}
	//Exit the program
#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
#pragma endregion
}