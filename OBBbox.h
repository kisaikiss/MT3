#pragma once
#include <stdint.h>
#include <Matrix4x4.h>
#include <OBB.h>



class OBBbox {
public:
	static int32_t obbBoxNum;
	OBBbox();
	~OBBbox();

	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) const;

	void OnCollision();

	void SetPosition(const Vector3& position) { obb_.center = position; }
	void SetRotate(const Vector3& rotate) { rotate_ = rotate; }
	OBB GetOBB() const { return obb_; }
	
private:
	OBB obb_;
	Vector3 rotate_;
	int32_t myNumber_;
	uint32_t color_;
};

