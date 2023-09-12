#pragma once
#include "SceneNode.h"

class WaterSceneNode : public SceneNode {
public:
	WaterSceneNode(Mesh* m, Vector4 colour, Shader* s, GLuint waterTex, GLuint cubeMap, Vector3 size);

	void Draw(const OGLRenderer& r) override;
protected:
	GLuint waterTex;
	GLuint cubeMap;
	GLuint size;

};