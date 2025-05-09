#pragma once
#include "AABB.h"
#include "Matrix4x4.h"
#include <cstdint>

class Box {
public:
	static int32_t boxNum;
	Box();
	~Box();

	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) const;

	void OnCollision();

	AABB GetWorldAABB()const { return worldAABB_; }

	void SetWorldAABB(const AABB& worldAABB);

private:
	AABB worldAABB_;
	AABB localAABB_;
	Vector3 pos_;
	int32_t myNumber_;
	uint32_t color_;
};

