#pragma once
#include "RE\ReEng.h"
#include "Box.h"

class TetrisShape{
	public:
		//Well this line doesn't work because C++ is a fucking garbage language that's shit to use so I guess fuck good coding practices. Fuck c++ so hard
		//std::vector<Box> boxes;

		//This is gonna have to do for now.
		Box * box1;
		Box * box2;
		Box * box3;

		glm::vec3 position;
		glm::vec3 pivotPoint;
		glm::quat quatRotation;

		glm::mat4 transformMat;

		void InitBoxes();
		void Translate(glm::vec3 _translation);
		void Rotate(glm::vec3 _axis, float _degrees);
		void DeleteBox();

		TetrisShape();
		~TetrisShape();
	private:
};

