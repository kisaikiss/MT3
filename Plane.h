#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
class Plane {
public:
	/// <summary>
	/// 法線の初期値をx=1,y=0,z=0、距離の初期値を0で初期化するコンストラクタ
	/// </summary>
	Plane();

	/// <summary>
	///  法線と平面上の点から平面の変数を求める
	/// </summary>
	/// <param name="normal">法線</param>
	/// <param name="point">平面上の点</param>
	void Initialize(const Vector3& normal, const Vector3& point);

	/// <summary>
	/// 平面上の3つの点から平面の変数を求める
	/// </summary>
	/// <param name="a">平面上の点1</param>
	/// <param name="b">平面上の点2</param>
	/// <param name="c">平面上の点3</param>
	void Initialize(const Vector3& a, const Vector3& b, const Vector3& c);

	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) const;

	Vector3 GetNormal() const { return normal_; }
	float GetDistance() const { return distance_; }

private:
	Vector3 normal_;//法線
	float distance_;//距離
};

