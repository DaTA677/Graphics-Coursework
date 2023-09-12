#pragma once
#include "SceneNode.h"


class HeightMapSceneNode : public SceneNode {
public :
	HeightMapSceneNode(Mesh* m = NULL, Shader* shader=NULL, GLuint mainTex =0);

	void Draw(const OGLRenderer& r) override;

	
	GLuint GetSubTex(const int& index) const { if (index < 3) return subTex[index]; else return -1; }
	void SetSubTex(const int& index, GLuint val) { if (index < 3)  subTex[index] = val;  }

	GLuint GetSubNor(const int& index) const { if (index < 3) return subNor[index]; else return -1; }
	void SetSubNor(const int& index, GLuint val) { if (index < 3)  subNor[index] = val; }

	GLuint GetSubSpec(int index) const { if (index < 3) return subSpec[index]; else return -1; }
	void SetSubSpec(const int& index, GLuint val) { if (index < 3)  subSpec[index] = val; }

	GLuint GetSplatMap() const {return splatMap; }
	void SetSplatMap(GLuint val) { splatMap = val; }

protected:
	GLuint subTex[3];
	GLuint subNor[3];
	GLuint subSpec[3];
	GLuint splatMap;
};
