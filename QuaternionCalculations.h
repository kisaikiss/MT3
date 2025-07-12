#pragma once
#include "Quaternion.h"

struct Vector3;
struct Matrix4x4;

Quaternion IdentityQuaternion();

Quaternion Conjugate(const Quaternion& quaternion);

Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);

Quaternion Normalize(const Quaternion& q);

float Norm(const Quaternion& q);

Quaternion Inverse(const Quaternion& q);

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);

Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);

void QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label);