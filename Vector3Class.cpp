#include "Vector3Class.h"

Vector3 Vector3::operator-(const Vector3& other) const {
	return { x - other.x, y - other.y, z - other.z };
}

Vector3 Vector3::operator+(const Vector3& other) const {
	return { x + other.x, y + other.y, z + other.z };
}

Vector3 Vector3::operator+(const float& scalar) const
{
	return { x + scalar, y + scalar, z + scalar };
}

Vector3 Vector3::Multiply(const float& scalar) const {
	return { x * scalar, y * scalar, z * scalar };
}

Vector3 Vector3::operator=(float scalar) const {
	return{ scalar, scalar, scalar };
}