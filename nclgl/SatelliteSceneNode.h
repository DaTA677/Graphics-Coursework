#pragma once
#include "HeightMapSceneNode.h"
#include "Mesh.h"

#define X_AXIS Vector3(1,0,0)
#define Y_AXIS Vector3(0,1,0)
#define Z_AXIS Vector3(0,0,1)
#define XY_AXIS Vector3(1,1,0)
#define XZ_AXIS Vector3(1,0,1)
#define YZ_AXIS Vector3(0,1,1)
#define XYZ_AXIS Vector3(1,1,1)

#define NX_AXIS Vector3(-1,0,0)
#define NY_AXIS Vector3(0,-1,0)
#define NZ_AXIS Vector3(0,0,-1)
#define NXY_AXIS Vector3(-1,-1,0)
#define NXZ_AXIS Vector3(-1,0,-1)
#define NYZ_AXIS Vector3(0,-1,-1)
#define NXYZ_AXIS Vector3(-1,-1,-1)



class SatelliteSceneNode : public HeightMapSceneNode {
public:
	SatelliteSceneNode(Mesh* m, Shader* shader, GLuint mainTex, float radius,float speed, Vector3 axis, Vector3 heightMapSize);

	void Update(float dt) override;

	float GetRadius() const { return radius; }
	void SetRadius(const float& r) { radius = r; }

	Vector3 GetAxis() const { return axis; }
	void SetAxis(const Vector3& a) { axis = a; }
	

protected:
	float radius;
	Vector3 axis;
	float currentAngle;
	float speed;
};
