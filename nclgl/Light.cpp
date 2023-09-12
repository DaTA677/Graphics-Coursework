#include "Light.h"

Light::Light(const Vector3& position, const Vector4& colour, float radius) {
this->position = position;
this->colour = colour;
this->radius = radius;
}