#pragma once
struct Quaternion {
	float x;
	float y;
	float z;
	float w;
};

Quaternion operator*(const Quaternion& q1, const Quaternion& q2);