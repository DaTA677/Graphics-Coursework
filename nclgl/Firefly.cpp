#include "Firefly.h"
#include "Matrix4.h"



Firefly::Firefly(Mesh* mesh, Vector3 position, Vector4 lightClour, float lightRadius) {
	SetMesh(mesh);
	SetTransform(Matrix4::Translation(position));
	SetModelScale(Vector3(20, 20, 20));
	SetColour(lightClour);
	light = new Light();
	light->SetPosition(position);
	light->SetColour(lightClour);
	light->SetRadius(modelScale.x*3);

}

Firefly::~Firefly() {
	delete light;
}

void Firefly::UpdatePosition(const Vector3& position) {
	SetTransform(Matrix4::Translation(position) * GetTransform());
	
}