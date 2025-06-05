#include "Bezier.h"
#include "Point.h"
#include "MatrixCalculations.h"
#include "Lerp.h"
#include <Novice.h>

Bezier::Bezier():kDivisionsNum(16) {
	for (uint32_t i = 0; i < 3; i++) {
		points_[i] = std::make_unique<Point>();
		points_[i]->SetColor(BLACK);
	}
}

Bezier::~Bezier() {

}

void Bezier::Update() {
	for (uint32_t i = 0; i < 3; i++) {
		points_[i]->Update();
	}
}

void Bezier::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) const {
	for (uint32_t i = 0; i < 3; i++) {
		points_[i]->Draw(viewProjectionMatrix, viewportMatrix);
	}
	for (uint32_t index = 0; index < kDivisionsNum; index++) {
		float t0 = index / static_cast<float>(kDivisionsNum);
		float t1 = (index + 1) / static_cast<float>(kDivisionsNum);
		Vector3 bezier0 = CreateBezier(t0);
		Vector3 bezier1 = CreateBezier(t1);
		// それぞれ上記の変数とvpVpMatrixを使用してTransformする
		Matrix4x4 vpVpMatrix = Multiply(viewProjectionMatrix, viewportMatrix);
		Vector3 bezierPointScreen = Transform(bezier0, vpVpMatrix);
		Vector3 bezierPointNextScreen = Transform(bezier1, vpVpMatrix);
		Novice::DrawLine(static_cast<int>(bezierPointScreen.x), static_cast<int>(bezierPointScreen.y),
			static_cast<int>(bezierPointNextScreen.x), static_cast<int>(bezierPointNextScreen.y), BLUE);
	}
}

void Bezier::SetControlPoints(const Vector3& controlPoint1, const Vector3& controlPoint2, const Vector3& controlPoint3) {
	points_[0]->SetPos(controlPoint1);
	points_[1]->SetPos(controlPoint2);
	points_[2]->SetPos(controlPoint3);
}

Vector3 Bezier::CreateBezier(float t) const {
	Vector3 result{};
	Vector3 p0p1 = Lerp(points_[0]->GetPos(), points_[1]->GetPos(), t);
	Vector3 p1p2 = Lerp(points_[1]->GetPos(), points_[2]->GetPos(), t);
	result = Lerp(p0p1, p1p2, t);
	return result;
}
