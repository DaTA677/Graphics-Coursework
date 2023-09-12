#include "SatelliteSceneNode.h"
#include "HeightMap.h"


SatelliteSceneNode::SatelliteSceneNode(Mesh* m, Shader* shader, GLuint mainTex, float radius,float speed, Vector3 axis,Vector3 heightMapSize)  {
	
	this->radius = radius;
	this->axis = axis;
	this->SetTransform(Matrix4::Translation(Vector3(heightMapSize.x, 0, heightMapSize.z * 0.5)));
	this->speed = speed;
	currentAngle = 0;
	 
	HeightMapSceneNode* satellite = new HeightMapSceneNode(m, shader, mainTex);
	satellite->SetTransform(Matrix4::Translation((axis+Vector3(-1,-1,-1)*(-radius))));
	this->AddChild(satellite);

}

void SatelliteSceneNode::Update(float dt){
	currentAngle += speed*dt;
	if (parent) {
		worldTransform = Matrix4::Rotation(currentAngle,axis)*parent->GetWorldTransform() * transform;
	}
	else {
		worldTransform = Matrix4::Rotation(currentAngle, axis) *transform;
	}
	for (vector<SceneNode*>::iterator i = children.begin(); i != children.end(); i++) {
		(*i)->Update(dt);
	}
}