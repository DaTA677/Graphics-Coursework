#pragma once
#include "Matrix4.h"
#include "Vector3.h"

class Camera {
public:
	Camera(void) {
		yaw = 0.0f;
		pitch = 0.0f;
		moveCamera = true;
		speedFac = 300.0f;
	}

	Camera(float pitch, float yaw, Vector3 position) {
		this->pitch = pitch;
		this->yaw = yaw;
		this->position = position;
		moveCamera = true;
		speedFac = 300.0f;
	}
	~Camera(void) {};

	void UpdateCamera(float dt = 1.0f);

	Matrix4 BuildViewMatrix();

	Vector3 GetPosition()const { return position; }
	void SetPosition(Vector3 val) { position = val; }

	float GetYaw() { return yaw; }
	void SetYaw(float val) { yaw = val; }

	float GetPitch() { return pitch; }
	void SetPitch(float val) { pitch = val; }

	void ToggleMoveCamera() { moveCamera = !moveCamera; }
	bool MoveCamera()const { return moveCamera; }

	float GetSpeed() const { return speedFac; }
	void SetSpeed(const float& s) { speedFac = s; }

	void SetCameraMovement(int i);


	void moveForward(float dt);
	void moveLeft(float dt);
	void moveRight(float dt);
	void moveBack(float dt);

protected:
	float yaw;
	float pitch;
	Vector3 position;//Set to 0,0,0 by Vector3 constructor ;)
	bool moveCamera;
	float speedFac;
};