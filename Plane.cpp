#include "Plane.h"
#include "MatrixCalculations.h"
#include "Vector3Calculations.h"
#include "Vector3Operator.h"
#include <Novice.h>
#include <cstdint>

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

Plane::Plane() {
	normal_ = { 1.f, 0.f, 0.f };
	distance_ = 0.f;
}

void Plane::Initialize(const Vector3& normal, const Vector3& point) {
	normal_ = normal;
	distance_ = Dot(normal, point);
}

void Plane::Initialize(const Vector3& a, const Vector3& b, const Vector3& c) {
	Vector3 v1 = b - a;
	Vector3 v2 = c - b;
	normal_ = Cross(v1, v2);
	distance_ = Dot(normal_, a);
}

void Plane::Update() {
#ifdef _DEBUG
	ImGui::Begin("plane");
	ImGui::SliderFloat("normalX", &normal_.x, -1.0f, 1.0f);
	ImGui::SliderFloat("normalY", &normal_.y, -1.0f, 1.0f);
	ImGui::SliderFloat("normalZ", &normal_.z, -1.0f, 1.0f);
	ImGui::DragFloat("distance", &distance_, 0.01f);
	ImGui::End();
#endif // _DEBUG
	normal_ = Normalize(normal_);
}

void Plane::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) const {
	
#pragma region 平面を表す矩形の描画
	Vector3 center = normal_ * distance_;
	Vector3 perpendiculars[4]{};
	perpendiculars[0] = Normalize(Perpendicular(normal_));
	perpendiculars[1] = Vector3(-perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z);
	perpendiculars[2] = Cross(normal_, perpendiculars[0]);
	perpendiculars[3] = Vector3(-perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z);
	Vector3 points[4]{};
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = perpendiculars[index] * 2.f;
		Vector3 point = center + extend;
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}
	
	Novice::DrawLine(static_cast<int>(points[0].x), static_cast<int>(points[0].y),
		static_cast<int>(points[2].x), static_cast<int>(points[2].y), WHITE);

	Novice::DrawLine(static_cast<int>(points[1].x), static_cast<int>(points[1].y),
		static_cast<int>(points[2].x), static_cast<int>(points[2].y), WHITE);

	Novice::DrawLine(static_cast<int>(points[1].x), static_cast<int>(points[1].y),
		static_cast<int>(points[3].x), static_cast<int>(points[3].y), WHITE);

	Novice::DrawLine(static_cast<int>(points[3].x), static_cast<int>(points[3].y),
		static_cast<int>(points[0].x), static_cast<int>(points[0].y), WHITE);
#pragma endregion

#pragma region 法線を表す線分の描画
	Vector3 origin{};
	origin = origin + normal_ * distance_;
	Vector3 diff = normal_;

	//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
	Vector3 ndcSegmentOrigin = Transform(origin, viewProjectionMatrix);
	Vector3 ndcSegmentOrigin2diff = Transform(origin + diff, viewProjectionMatrix);
	//Viewport変換を行ってScreen空間へ
	Vector3 screenSegmentOrigin = Transform(ndcSegmentOrigin, viewportMatrix);
	Vector3 screenSegmentOrigin2diff = Transform(ndcSegmentOrigin2diff, viewportMatrix);

	Novice::DrawLine(static_cast<int>(screenSegmentOrigin.x), static_cast<int>(screenSegmentOrigin.y),
		static_cast<int>(screenSegmentOrigin2diff.x), static_cast<int>(screenSegmentOrigin2diff.y), BLUE);


	//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
	Vector3 ndcEllipsePos = Transform(origin, viewProjectionMatrix);
	//Viewport変換を行ってScreen空間へ
	Vector3 screenEllipsePos = Transform(ndcEllipsePos, viewportMatrix);
	Novice::DrawEllipse(static_cast<int>(screenEllipsePos.x), static_cast<int>(screenEllipsePos.y), 3, 3, 0.f, 0x00ff00ff, kFillModeSolid);
#pragma endregion

}
