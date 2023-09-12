#include"HeightMapSceneNode.h"
#include<string.h>

HeightMapSceneNode::HeightMapSceneNode(Mesh* m, Shader* shader, GLuint mainTex) {
	mesh = m;
	this->shader = shader;
	this->texture = mainTex;

	for (int i = 0; i < 3; i++) {
		subNor[i] = 0;
		subSpec[i] = 0;
		subTex[i] = 0;
	}
	splatMap = 0;
}

void HeightMapSceneNode::Draw(const OGLRenderer& r) {
	glUniform1i(glGetUniformLocation(shader->GetProgram(), "diffuseTex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (specMap) {
		glUniform1i(glGetUniformLocation(shader->GetProgram(), "specTex"), 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specMap);
	}
	if (normalMap) {
		glUniform1i(glGetUniformLocation(shader->GetProgram(), "normalTex"), 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, normalMap);
	}
	if (splatMap) {
		glUniform1i(glGetUniformLocation(shader->GetProgram(), "splatMap"), 3);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, splatMap);
	}
	
	for (int i = 0; i < 3; i++) {
		std::string s1 = "extraTex[" + std::to_string(i) + "]";
		std::string s2 = "extraSpec[" + std::to_string(i) + "]";
		std::string s3 = "extraNor[" + std::to_string(i) + "]";
		if (subTex[i]) {
			glUniform1i(glGetUniformLocation(shader->GetProgram(), s1.c_str()), i + 4);
			glActiveTexture(GL_TEXTURE3 + i + 1);
			glBindTexture(GL_TEXTURE_2D, subTex[i]);
		}
		if (subSpec[i]) {
			glUniform1i(glGetUniformLocation(shader->GetProgram(), s2.c_str()), i + 8);
			glActiveTexture(GL_TEXTURE3 + i + 5);
			glBindTexture(GL_TEXTURE_2D, subSpec[i]);
		}
		if (subNor[i]) {
			glUniform1i(glGetUniformLocation(shader->GetProgram(), s3.c_str()), i + 12);
			glActiveTexture(GL_TEXTURE3 + i + 9);
			glBindTexture(GL_TEXTURE_2D, subNor[i]);
		}
		
		
	}


	/*glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, subTex[0]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, subTex[1]);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, subTex[2]);*/
	
	mesh->Draw(); 
}