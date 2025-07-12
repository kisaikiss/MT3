#pragma once
#include "Quaternion.h"

Quaternion IdentityQuaternion();

Quaternion Conjugate(const Quaternion& quaternion);

Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);

Quaternion Normalize(const Quaternion& q);

float Norm(const Quaternion& q);

Quaternion Inverse(const Quaternion& q);

void QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label);