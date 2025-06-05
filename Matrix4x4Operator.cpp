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
