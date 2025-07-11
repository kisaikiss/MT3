#pragma once
#include "Vector3.h"

Vector3 operator+(const Vector3& v1, const Vector3& v2);

Vector3 operator-(const Vector3& v1, const Vector3& v2);

Vector3 operator*(float s, const Vector3& v);

Vector3 operator*(const Vector3& v, float s);

Vector3 operator/(const Vector3& v, float s);

Vector3 operator+(const Vector3& v);

Vector3 operator-(const Vector3& v);

bool operator==(const Vector3& v1, const Vector3& v2);