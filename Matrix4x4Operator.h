#pragma once
#include "Matrix4x4.h"

Matrix4x4 operator+(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

Matrix4x4 operator-(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

Matrix4x4 operator*(const Matrix4x4& matrix1, const Matrix4x4& matrix2);