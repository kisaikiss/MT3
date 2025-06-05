#pragma once
#include <memory>
#include "Vector3Class.h"
#include "Matrix4x4.h"

class Arm {
public:
	Arm();
	~Arm() = default;

	void Update();

	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

private:
	Vector3 translates_[3];
	Vector3 rotates_[3];
	Vector3 scales_[3];

	Matrix4x4 worldMatrixs_[3];
};

