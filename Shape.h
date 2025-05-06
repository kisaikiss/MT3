#pragma once
#include "Vector3Class.h"
#include "Point.h"
#include "Matrix4x4.h"
#include <cstdint>

enum class ShapeType {
	LINE,
	RAY,
	SEGMENT,
};

/// <summary>
/// 線を表す抽象クラス
/// </summary>
class Shape {
public:
	Shape() = default;
	virtual ~Shape() = default;
	virtual void Update() = 0;
	virtual void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) = 0;
	virtual void DrawClosestPoint(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, Point& point);

	virtual void OnCollision();

	virtual Vector3 GetOrigin() const { return origin_; }
	virtual Vector3 GetDiff() const { return diff_; }
	virtual ShapeType GetShapeType() const { return myType_; }

	virtual void SetOrigin(const Vector3& origin) { origin_ = origin; }
	virtual void SetDiff(const Vector3& diff) { diff_ = diff; }
protected:

	Vector3 origin_;
	Vector3 diff_;
	uint32_t color_;
	int32_t myNumber_;
	ShapeType myType_;
};

/// <summary>
/// 直線を表すクラス
/// </summary>
class Line : public Shape {
public:
	static int32_t lineNum;
	Line();
	~Line();

	void Update() override;
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) override;
};

/// <summary>
/// 半直線を表すクラス
/// </summary>
class Ray : public Shape {
public:
	static int32_t rayNum;
	Ray();
	~Ray();

	void Update() override;
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) override;
};

/// <summary>
/// 線分を表すクラス
/// </summary>
class Segment : public Shape {
public:
	static int32_t segmentNum;
	Segment();
	~Segment();

	void Update() override;
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) override;
};