#include "QuaternionCalculations.h"
#include "Define.h"
#include "Novice.h"
#include "cmath"
#include <cassert>

Quaternion IdentityQuaternion() {
	return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Conjugate(const Quaternion& quaternion) {
	return Quaternion(-quaternion.x, -quaternion.y, -quaternion.z, quaternion.w);
}

Quaternion Multiply(const Quaternion& q1, const Quaternion& q2) {
	Quaternion result{};
	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.y * q2.z - q1.z * q2.y + q2.w * q1.x + q1.w * q2.x;
	result.y = q1.z * q2.x - q1.x * q2.z + q2.w * q1.y + q1.w * q2.y;
	result.z = q1.x * q2.y - q1.y * q2.x + q2.w * q1.z + q1.w * q2.z;

	return result;
}

Quaternion Normalize(const Quaternion& q) {
	float norm = Norm(q);
	assert(norm != 0);
	return Quaternion(q.x / norm, q.y / norm, q.z / norm, q.w / norm);
}

float Norm(const Quaternion& q) {
	
	float result = std::sqrtf(std::powf(q.x, 2.0f) + std::powf(q.y, 2.0f) + std::powf(q.z, 2.0f) + std::powf(q.w, 2.0f));

	return result;
}

Quaternion Inverse(const Quaternion& q) {
	float squaredNorm = std::powf(Norm(q), 2.0f);
	Quaternion conjugate = Conjugate(q);
	
	return Quaternion(conjugate.x / squaredNorm, conjugate.y / squaredNorm, conjugate.z / squaredNorm, conjugate.w / squaredNorm);
}

void QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", quaternion.x);
	Novice::ScreenPrintf(x + Define::kColumnWidth, y, "%.02f", quaternion.y);
	Novice::ScreenPrintf(x + Define::kColumnWidth * 2, y, "%.02f", quaternion.z);
	Novice::ScreenPrintf(x + Define::kColumnWidth * 3, y, "%.02f", quaternion.w);
	Novice::ScreenPrintf(x + Define::kColumnWidth * 4, y, "%s", label);

}
