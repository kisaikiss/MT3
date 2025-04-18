#pragma once
#include "Vector3Class.h"
#include "Matrix4x4.h"

class Camera {
public:
	Camera();
	~Camera() = default;

	void Update();

	Matrix4x4 GetVeiwProjectionMatrix() const { return viewProjectionMatrix_; }

	Matrix4x4 GetVeiwportMatrix() const { return viewportMatrix_; }

private:
	Vector3 pos_;
	Vector3 rotate_;
	Vector3 scale_;

	Matrix4x4 worldMatrix_;
	Matrix4x4 viewProjectionMatrix_;
	Matrix4x4 viewportMatrix_;
};

