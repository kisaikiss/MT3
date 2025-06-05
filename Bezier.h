#pragma once
#include "Matrix4x4.h"
#include "Vector3Class.h"
#include <memory>
#include <stdint.h>

class Point;

class Bezier {
public:
	Bezier();
	~Bezier();

	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) const;

	void SetControlPoints(const Vector3& controlPoint1, const Vector3& controlPoint2, const Vector3& controlPoint3);
private:
	std::unique_ptr<Point> points_[3];

	const uint32_t kDivisionsNum;

	Vector3 CreateBezier(float t) const;
};

