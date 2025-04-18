#include "Vector3Calculations.h"

#include "Define.h"

float Dot(Vector3 v1, Vector3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Cross(Vector3& v1, Vector3& v2) {
	Vector3 result{};
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

float Length(Vector3 vector3) {
	return sqrtf(powf(vector3.x, 2.0f) + powf(vector3.y, 2.0f) + powf(vector3.z, 2.0f));
}

Vector3 Normalize(Vector3& vector3) {
	float length = Length(vector3);
	assert(length != 0);
	return Vector3(vector3.x / length, vector3.y / length, vector3.z / length);
}


void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + Define::kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + Define::kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + Define::kColumnWidth * 3, y, "%s", label);
}