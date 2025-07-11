#include "Matrix4x4Operator.h"
#include "MatrixCalculations.h"

Matrix4x4 operator+(const Matrix4x4& matrix1, const Matrix4x4& matrix2) {
	return Add(matrix1, matrix2);
}

Matrix4x4 operator-(const Matrix4x4& matrix1, const Matrix4x4& matrix2) {
	return Subtract(matrix1, matrix2);
}

Matrix4x4 operator*(const Matrix4x4& matrix1, const Matrix4x4& matrix2) {
	return Multiply(matrix1, matrix2);
}

Matrix4x4 operator*(const Matrix4x4& matrix, float s) {
	Matrix4x4 result;
	for (uint32_t i = 0; i < 4; i++) {
		for (uint32_t j = 0; j < 4; j++) {
			result.m[i][j] = matrix.m[i][j] * s;
		}
	}
	return result;
}

Matrix4x4 operator*(float s, const Matrix4x4& matrix) {
	return operator*(matrix, s);
}

Matrix4x4 operator-(const Matrix4x4& matrix) {
	Matrix4x4 result;
	for (uint32_t i = 0; i < 4; i++) {
		for (uint32_t j = 0; j < 4; j++) {
			result.m[i][j] = matrix.m[i][j] * -1.0f;
		}
	}

	return result;
}
