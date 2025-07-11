#include "MatrixCalculations.h"
#include "Matrix4x4Operator.h"
#include "Vector3Calculations.h"
#include "Vector3Operator.h"
#include "Define.h"

#include <Novice.h>

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}

Matrix4x4 Multiply(Matrix4x4 const& matrix1, Matrix4x4 const& matrix2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}

	return result;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result{};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakeRotateXMatrix(float theta) {
	Matrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[1][1] = std::cos(theta);
	result.m[1][2] = std::sin(theta);
	result.m[2][1] = -std::sin(theta);
	result.m[2][2] = std::cos(theta);
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakeRotateYMatrix(float theta) {
	Matrix4x4 result{};
	result.m[0][0] = std::cos(theta);
	result.m[1][1] = 1.0f;
	result.m[2][0] = std::sin(theta);
	result.m[0][2] = -std::sin(theta);
	result.m[2][2] = std::cos(theta);
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakeRotateZMatrix(float theta) {
	Matrix4x4 result{};
	result.m[0][0] = std::cos(theta);
	result.m[0][1] = std::sin(theta);
	result.m[1][0] = -std::sin(theta);
	result.m[1][1] = std::cos(theta);
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakeRotateMatrix(const Vector3& rotate) {
	Matrix4x4 result{};
	result = Multiply(MakeRotateXMatrix(rotate.x), Multiply(MakeRotateYMatrix(rotate.y), MakeRotateZMatrix(rotate.z)));
	return result;
}

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle) {
	Matrix4x4 result{};
	
	Matrix4x4 s = std::cos(angle) * MakeIdentity4x4();

	Matrix4x4 p = {
		{axis.x * axis.x, axis.x * axis.y, axis.x * axis.z, 0.0f,
		 axis.y * axis.x, axis.y * axis.y, axis.y * axis.z, 0.0f,
		 axis.z * axis.x, axis.z * axis.y, axis.z * axis.z, 0.0f,
		 0.0f, 0.0f, 0.0f, 1.0f}
	};

	p = (MakeIdentity4x4() - s) * p;

	Matrix4x4 axisCloss = {
		{0.0f, -axis.z, axis.y, 0.0f,
		 axis.z, 0.0f, -axis.x, 0.0f,
		 -axis.y, axis.x, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f}
	};


	Matrix4x4 c = -(std::sin(angle) * MakeIdentity4x4()) * axisCloss;

	result = s + p + c;
	
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to) {
	Matrix4x4 result{};
	Vector3 axis{};
	if (from == -to) {
		axis = { from.y, -from.x, 0.f };
	} else {
		axis = Cross(from, to);
	}
	axis = Normalize(axis);

	float cos = Dot(from, to);
	float sin = Length(Cross(from, to));

	Matrix4x4 s = cos * MakeIdentity4x4();

	Matrix4x4 p = {
		{axis.x * axis.x, axis.x * axis.y, axis.x * axis.z, 0.0f,
		 axis.y * axis.x, axis.y * axis.y, axis.y * axis.z, 0.0f,
		 axis.z * axis.x, axis.z * axis.y, axis.z * axis.z, 0.0f,
		 0.0f, 0.0f, 0.0f, 1.0f}
	};

	p = (MakeIdentity4x4() - s) * p;

	Matrix4x4 axisCloss = {
		{0.0f, -axis.z, axis.y, 0.0f,
		 axis.z, 0.0f, -axis.x, 0.0f,
		 -axis.y, axis.x, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f}
	};


	Matrix4x4 c = -(sin * MakeIdentity4x4()) * axisCloss;

	result = s + p + c;

	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result{};
	result = Multiply(MakeScaleMatrix(scale), MakeRotateMatrix(rotate));
	result = Multiply(result, MakeTranslateMatrix(translate));
	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result{};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Matrix4x4 Inverse(Matrix4x4 matrix) {
	Matrix4x4 result{};

	float determinant =
		matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0] - matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0] -
		matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0] + matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0] +
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0] - matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0] -
		matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1] + matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1] +
		matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1] - matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1] -
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1] + matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1] +
		matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2] - matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2] -
		matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] + matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2] +
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2] - matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3] + matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] - matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] + matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3];


	if (determinant == 0) {
		return result;
	}

	Matrix4x4 cofactorMatrix{};
	cofactorMatrix.m[0][0] = matrix.m[1][1] * (matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2]) - matrix.m[1][2] * (matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1]) + matrix.m[1][3] * (matrix.m[2][1] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][1]);
	cofactorMatrix.m[0][1] = -(matrix.m[0][1] * (matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2]) - matrix.m[0][2] * (matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1]) + matrix.m[0][3] * (matrix.m[2][1] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][1]));
	cofactorMatrix.m[0][2] = matrix.m[0][1] * (matrix.m[1][2] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][2]) - matrix.m[0][2] * (matrix.m[1][1] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][1]) + matrix.m[0][3] * (matrix.m[1][1] * matrix.m[3][2] - matrix.m[1][2] * matrix.m[3][1]);
	cofactorMatrix.m[0][3] = -(matrix.m[0][1] * (matrix.m[1][2] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][2]) - matrix.m[0][2] * (matrix.m[1][1] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][1]) + matrix.m[0][3] * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]));
	cofactorMatrix.m[1][0] = -(matrix.m[1][0] * (matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2]) - matrix.m[1][2] * (matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0]) + matrix.m[1][3] * (matrix.m[2][0] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][0]));
	cofactorMatrix.m[1][1] = matrix.m[0][0] * (matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2]) - matrix.m[0][2] * (matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0]) + matrix.m[0][3] * (matrix.m[2][0] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][0]);
	cofactorMatrix.m[1][2] = -(matrix.m[0][0] * (matrix.m[1][2] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][2]) - matrix.m[0][2] * (matrix.m[1][0] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][0]) + matrix.m[0][3] * (matrix.m[1][0] * matrix.m[3][2] - matrix.m[1][2] * matrix.m[3][0]));
	cofactorMatrix.m[1][3] = matrix.m[0][0] * (matrix.m[1][2] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][2]) - matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][0]) + matrix.m[0][3] * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]);
	cofactorMatrix.m[2][0] = matrix.m[1][0] * (matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1]) - matrix.m[1][1] * (matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0]) + matrix.m[1][3] * (matrix.m[2][0] * matrix.m[3][1] - matrix.m[2][1] * matrix.m[3][0]);
	cofactorMatrix.m[2][1] = -matrix.m[0][0] * (matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1]) + matrix.m[0][1] * (matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0]) - matrix.m[0][3] * (matrix.m[2][0] * matrix.m[3][1] - matrix.m[2][1] * matrix.m[3][0]);
	cofactorMatrix.m[2][2] = matrix.m[0][0] * (matrix.m[1][1] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][1]) + matrix.m[0][1] * (matrix.m[1][3] * matrix.m[3][0] - matrix.m[1][0] * matrix.m[3][3]) + matrix.m[0][3] * (matrix.m[1][0] * matrix.m[3][1] - matrix.m[1][1] * matrix.m[3][0]);
	cofactorMatrix.m[2][3] = -matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][1]) - matrix.m[0][1] * (matrix.m[1][3] * matrix.m[2][0] - matrix.m[1][0] * matrix.m[2][3]) - matrix.m[0][3] * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
	cofactorMatrix.m[3][0] = matrix.m[1][0] * (-matrix.m[2][1] * matrix.m[3][2] + matrix.m[2][2] * matrix.m[3][1]) + matrix.m[1][1] * (-matrix.m[2][2] * matrix.m[3][0] + matrix.m[2][0] * matrix.m[3][2]) + matrix.m[1][2] * (matrix.m[2][1] * matrix.m[3][0] - matrix.m[2][0] * matrix.m[3][1]);
	cofactorMatrix.m[3][1] = -matrix.m[0][0] * (-matrix.m[2][1] * matrix.m[3][2] + matrix.m[2][2] * matrix.m[3][1]) - matrix.m[0][1] * (-matrix.m[2][2] * matrix.m[3][0] + matrix.m[2][0] * matrix.m[3][2]) - matrix.m[0][2] * (matrix.m[2][1] * matrix.m[3][0] - matrix.m[2][0] * matrix.m[3][1]);
	cofactorMatrix.m[3][2] = matrix.m[3][2] * (-matrix.m[0][0] * matrix.m[1][1] + matrix.m[0][1] * matrix.m[1][0]) + matrix.m[3][0] * (-matrix.m[0][1] * matrix.m[1][2] + matrix.m[0][2] * matrix.m[1][1]) + matrix.m[3][1] * (matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);
	cofactorMatrix.m[3][3] = -matrix.m[2][2] * (-matrix.m[0][0] * matrix.m[1][1] + matrix.m[0][1] * matrix.m[1][0]) - matrix.m[2][0] * (-matrix.m[0][1] * matrix.m[1][2] + matrix.m[0][2] * matrix.m[1][1]) - matrix.m[2][1] * (matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);

	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			result.m[row][column] = cofactorMatrix.m[row][column] / determinant;
		}
	}

	return result;
}

Matrix4x4 Transpose(Matrix4x4 matrix) {
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = matrix.m[j][i];
		}
	}
	return result;
}

Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result{
		{
			1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,1.0f
		}
	};
	return result;
}


Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float zNear, float zFar) {
	Matrix4x4 result{};
	result.m[0][0] = 2.f / (right - left);
	result.m[1][1] = 2.f / (top - bottom);
	result.m[2][2] = 1.f / (zFar - zNear);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = zNear / (zNear - zFar);
	result.m[3][3] = 1.f;

	return result;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result{};
	result.m[0][0] = (1.f / aspectRatio) * (1.f / tanf(fovY / 2.f));
	result.m[1][1] = 1.f / tanf(fovY / 2.f);
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	result.m[2][3] = 1.f;
	return result;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result{};
	result.m[0][0] = width / 2.f;
	result.m[1][1] = -1 * (height / 2.f);
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + result.m[0][0];
	result.m[3][1] = top + (height / 2.f);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.f;
	return result;
}


void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, label);
	y += Define::kRowHeight;
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * Define::kColumnWidth, y + row * Define::kRowHeight, "%.03f", matrix.m[row][column]);
		}
	}
}

Matrix4x4 MakeWorldOBB(Vector3 center, Vector3 orientations[3]) {
	Matrix4x4 result{};
	result = {
		{
			orientations[0].x, orientations[0].y,orientations[0].z,0.f,
			orientations[1].x, orientations[1].y,orientations[1].z,0.f,
			orientations[2].x, orientations[2].y,orientations[2].z,0.f,
			center.x,		   center.y,		 center.z,		   1.f
		}
	};
	return result;
}

Matrix4x4 MakeWorldOBB(OBB obb) {
	Matrix4x4 result{};
	result = {
		{
			obb.orientations[0].x, obb.orientations[0].y, obb.orientations[0].z,0.f,
			obb.orientations[1].x, obb.orientations[1].y, obb.orientations[1].z,0.f,
			obb.orientations[2].x, obb.orientations[2].y, obb.orientations[2].z,0.f,
			obb.center.x,		   obb.center.y,		  obb.center.z,		   1.f
		}
	};
	return result;
}
