#pragma once
#include "Sphere.h"
class Point :
    public Sphere {
public:
	static	int32_t pointNum;
	Point();

	void Update();

	void DrawPos(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,const Vector3& position, const uint32_t color);
};

