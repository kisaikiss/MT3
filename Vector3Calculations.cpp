#include "Vector3Calculations.h"

#include "Define.h"
#include "Vector3Operator.h"

float Dot(Vector3 v1, Vector3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Cross(const Vector3& v1, const  Vector3& v2) {
	Vector3 result{};
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

float Length(Vector3 vector3) {
	return sqrtf(powf(vector3.x, 2.0f) + powf(vector3.y, 2.0f) + powf(vector3.z, 2.0f));
}

float LengthSquared(const Vector3& v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

Vector3 Normalize(const Vector3& vector3) {
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

Vector3 Project(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	float length = Length(v2);
	assert(length != 0);
	result.x = (Dot(v1, v2) / length) * (v2.x / length);
	result.y = (Dot(v1, v2) / length) * (v2.y / length);
	result.z = (Dot(v1, v2) / length) * (v2.z / length);
	return result;
}


Vector3 TransforNormal(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result{
		vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0],
		vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1],
		vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2]
	};

	return result;
}

Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0 || vector.y != 0.0f) {
		return Vector3(-vector.y, vector.x, 0.0f);
	}
	return Vector3(0.0f, -vector.z, vector.y);
}

Vector3 Reflect(const Vector3& input, const Vector3& normal) {
	Vector3 result = input - 2 * (Dot(input, normal)) * normal;
	return result;
}
