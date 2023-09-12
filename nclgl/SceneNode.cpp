#include "SceneNode.h"


int SceneNode::id = 0;
SceneNode::SceneNode(Mesh* mesh, Vector4 colour, Shader* shader) {

	this->mesh = mesh;
	this->colour = colour;
	this->shader = shader;
	parent = NULL;
	modelScale = Vector3(1, 1, 1);
	value = ++SceneNode::id;

	boundingRadius = 1.0f;
	distanceFromCamera = 0.0f;
	texture = 0;
	normalMap = 0;
	specMap = 0;
}

SceneNode::~SceneNode(void) {
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete children[i];
	}
}

void SceneNode::AddChild(SceneNode* s) {
	children.push_back(s);
	s->parent = this;
}

bool SceneNode::RemoveChild(int id) {
	auto iterator = children.begin();
	bool flag = false;
	while (iterator!=children.end()&& (*iterator)->value != id &&!flag) {
		flag=(*iterator)->RemoveChild(id);
		++iterator;
	}
	if (iterator != children.end()&&!flag) {
		delete (*iterator);
		children.erase(iterator);
		//delete node1;
		return true;
	}
	return flag;
}

void SceneNode::Draw(const OGLRenderer& r) {
	glUniform4fv(glGetUniformLocation(shader->GetProgram(), "nodeColour"), 1, (float*)&colour);
	glUniform1i(glGetUniformLocation(shader->GetProgram(), "useTexture"), 0);
	if (mesh) { mesh->Draw(); }
	
}

void SceneNode::Update(float dt) {
	if (parent) {
		worldTransform = parent->worldTransform * transform;
	}
	else {
		worldTransform = transform;
	}
	for (vector<SceneNode*>::iterator i = children.begin(); i != children.end(); i++) {
		(*i)->Update(dt);
	}
}