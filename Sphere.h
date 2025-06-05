#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include <cstdint>

class Sphere {
public:
	static int32_t sphereNum;

	Sphere();
	~Sphere();

	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

	void OnCollision();

	void SetPos(const Vector3& position);
	void SetRadius(float radius) { radius_ = radius; }
	void SetColor(uint32_t color) { color_ = color; }

	Vector3 GetPos() const { return centerPos_; }
	float GetRadius() const { return radius_; }
protected:
	Vector3 centerPos_;
	uint32_t color_;
	int32_t myNumber_;
	float radius_;	
};

