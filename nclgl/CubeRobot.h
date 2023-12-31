#pragma once
#include "SceneNode.h"

class CubeRobot: public SceneNode {
public:
	CubeRobot(Mesh* cube,Shader* shader);
	~CubeRobot(void) {};
	void Update(float dt) override;



protected:
	SceneNode* head;
	SceneNode* leftArm;
	SceneNode* rightArm;
	SceneNode* hip;
};
