#include "WaterSceneNode.h"

WaterSceneNode::WaterSceneNode(Mesh* m, Vector4 colour, Shader* s, GLuint waterTex, GLuint cubeMap, Vector3 size) : SceneNode(m, colour, s) {
	this->waterTex = waterTex;
	this->cubeMap = cubeMap;
	SetTransform(Matrix4::Translation(Vector3(size.x * 0.5f,size.y*0.3,size.z*0.5f)) * Matrix4::Scale(size * 0.5f) * Matrix4::Rotation(90, Vector3(-1, 0, 0)));
}

void WaterSceneNode::Draw(const OGLRenderer& r) {
	glUniform1i(glGetUniformLocation(shader->GetProgram(), "diffuseTex"), 3);
	glUniform1i(glGetUniformLocation(shader->GetProgram(), "cubeTex"), 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, waterTex);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

	SceneNode::Draw(r);
}