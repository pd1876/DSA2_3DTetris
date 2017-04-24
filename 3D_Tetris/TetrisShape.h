#pragma once
#include "RE\ReEng.h"
#include "GameManager.h"

class TetrisShape{
	public:

		//Well this line doesn't work because C++ is a fucking garbage language that's shit to use so I guess fuck good coding practices. Fuck c++ so hard
		//std::vector<Box> boxes;

		//Is this the shape that the player is currently controlling?

		//This is gonna have to do for now.
		Box* box1;
		Box* box2;
		Box* box3;

		// Let's declare some physics variables
		float mass;
		vector3 velocity;
		vector3 acceleration;

		// Bool for if it should be moving or not
		bool isFalling;

		//Position isn't really used currently but it might be helpful later
		vector3 position;

		//Also not currently in use but same deal
		vector3 pivotPoint;

		//Ditto
		glm::quat quatRotation;
		
		//Movement is being handled by updating this matrix every frame
		glm::mat4 transformMat;

		//Creates three boxes at predefined locations
		void InitBoxes();

		//Moves the TetrisShape's model matrix along with its boxes model matrices
		void Translate(vector3 _translation);

		// Moves the TetrisShape model matrix along the Z axis
		void Fall();

		//Not implemented yet
		void Rotate(vector3 _axis, float _degrees);
		void DeleteBox();

		TetrisShape();
		~TetrisShape();
	private:
};

