#pragma once
#include "RE\ReEng.h"
#include "GameManager.h"
#include "Camera.h"

class TetrisShape{
	public:

		//Well this line doesn't work because C++ is a fucking garbage language that's shit to use so I guess fuck good coding practices. Fuck c++ so hard
		std::vector<Box> boxes;

		//Is this the shape that the player is currently controlling?

		//This is gonna have to do for now.
		Box* box1;
		Box* box2;
		Box* box3;
		Box* box4;
		Box* box5;

		//Position isn't really used currently but it might be helpful later
		glm::vec3 position;

		//Also not currently in use but same deal
		glm::vec3 pivotPoint;

		//Ditto
		glm::quat quatRotation;
		
		//Movement is being handled by updating this matrix every frame
		glm::mat4 transformMat;

		//Roatation matrix
		glm::mat4 rotMat;
		
		//Creates five box line shape
		void InitLineBoxes();

		//Creates four box cross shape
		void InitCrossBoxes();

		//blackboxing rendering this shape's boxes
		void RenderBoxes(MyCamera* camera);

		//Moves the TetrisShape's model matrix along with its boxes model matrices
		void Translate(glm::vec3 _translation);

		//Not implemented yet
		void Rotate(glm::vec3 _axis, float _degrees);
		void DeleteBox();

		TetrisShape();
		~TetrisShape();
	private:
};

