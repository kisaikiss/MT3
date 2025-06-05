#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include <cstdint>

class Triangle {
public:
	static int32_t triangleNum;

	Triangle();
	~Triangle() = default;

	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) const;

	/// <summary>
	/// 三頂点を取得する
	/// </summary>
	/// <param name="vertices">三頂点を取得した時にいれる変数</param>
	void GetVertices(Vector3* vertices) const;

	/// <summary>
	/// 回転を入れる
	/// </summary>
	/// <param name="rotate"></param>
	void SetRotate(Vector3& rotate);

	void SetTranslate(Vector3& translate);
private:
	Vector3 vertices_[3];
	Vector3 scale_;
	Vector3 rotate_;
	Vector3 translate_;
	int32_t myNumber_;
	uint32_t color_;
};

