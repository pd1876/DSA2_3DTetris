#pragma once
#include "RE\ReEng.h"
#include "GameManager.h"
#include "Camera.h"

class TetrisShape{
	public:
		//To keep track of how many boxes we've spawned in total so that each box has a unique id so the mesh manager can render each box
		static int boxCount;
		float transSpeed = 400.0f;
		float rotateAngle = 90.0f;
		//Well this line doesn't work because C++ is a fucking garbage language that's shit to use so I guess fuck good coding practices. Fuck c++ so hard
		std::vector<Box> boxes;
		
		//Number of boxes might not line up with the actualy length of the boxes vector. This variable keeps track of how many boxes are in this shape
		int myBoxCount;

		//This is gonna have to do for now.
		Box* box1;
		Box* box2;
		Box* box3;
		Box* box4;
		Box* box5;

		MeshManagerSingleton* meshManager;

		//Position isn't really used currently but it might be helpful later
		glm::vec3 position;

		// Let's declare some physics variables

		float mass;
		vector3 velocity;
		vector3 acceleration;

		// Check for if something is actively falling
		bool isFalling;

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

		//Creates five box cross shape
		void InitCrossBoxes();

		//Creates five box Z shape
		void InitZBoxes();

		//Creates five box reverse Z shape
		void InitReverseZBoxes();

		//Creates five box L shape
		void InitLBoxes();

		//Creates five box reverse L shape
		void InitReverseLBoxes();

		//blackboxing rendering this shape's boxes
		void RenderBoxes(MyCamera* camera);

		// Makes the blocks fall due to physics!
		void Fall();

		//Moves the TetrisShape's model matrix along with its boxes model matrices
		void Translate(glm::vec3 _translation);

		//Not implemented yet
		void Rotate(glm::vec3 _axis, float _degrees);
		void DeleteBox();

		TetrisShape(MeshManagerSingleton* _meshManager);
		TetrisShape();
		~TetrisShape();
	private:
};

