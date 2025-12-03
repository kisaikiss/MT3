#pragma once
#include "Matrix4x4.h"

Matrix4x4 operator+(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

Matrix4x4 operator-(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

Matrix4x4 operator*(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

Matrix4x4 operator*(const Matrix4x4& matrix, float s);

Matrix4x4 operator*(float s, const Matrix4x4& matrix);

Matrix4x4 operator-(const Matrix4x4& matrix);