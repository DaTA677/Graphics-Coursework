#pragma once
#pragma once
#include "SceneNode.h"
#include "Light.h"


class Firefly :public SceneNode {

public:
	Firefly(Mesh* m, Vector3 position, Vector4 lightClour, float lightRadius);
	~Firefly();

	
	void UpdatePosition(const Vector3& position);
	Light* GetLight() const { return light; }

protected:
	Light* light;


};
