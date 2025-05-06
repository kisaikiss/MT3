#include "Point.h"
#include <Novice.h>
#include <numbers>

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include <sstream>
#include <MatrixCalculations.h>

int32_t Point::pointNum = 0;

Point::Point() {
	pointNum++;
	myNumber_ = pointNum;
	color_ = RED;
	radius_ = 0.01f;
}

void Point::Update() {
#ifdef _DEBUG
	std::stringstream myNumString;
	myNumString << myNumber_;
	std::string name = "Point";
	name = name + myNumString.str();
	ImGui::Begin(name.c_str());
	ImGui::DragFloat3("position", &centerPos_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
}

void Point::DrawPos(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Vector3& position, const uint32_t color) {
	const uint32_t kSubdivision = 8;//分割数
	const float pi = std::numbers::pi_v<float>;
	const float kLatEvery = pi / static_cast<float>(kSubdivision);//緯度分割1つ分の角度
	const float kLonEvery = (2.f * pi) / static_cast<float>(kSubdivision);//経度分割1つ分の角度


	//緯度の方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.f + kLatEvery * latIndex;//現在の緯度
		//経度の方向に分割 0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;//現在の経度
			//world座標系でのa,b,cを求める
			Vector3 a = {
				position.x + radius_ * cosf(lat) * cosf(lon),
				position.y + radius_ * sinf(lat),
				position.z + radius_ * cosf(lat) * sinf(lon)
			};
			Vector3 b = {
				position.x + radius_ * cosf(lat + kLatEvery) * cosf(lon),
				position.y + radius_ * sinf(lat + kLatEvery),
				position.z + radius_ * cosf(lat + kLatEvery) * sinf(lon)
			};
			Vector3 c = {
				position.x + radius_ * cosf(lat) * cosf(lon + kLonEvery),
				position.y + radius_ * sinf(lat),
				position.z + radius_ * cosf(lat) * sinf(lon + kLonEvery)
			};
			//a,b,cをScreen座標系まで変換
			//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
			Vector3 ndcA = Transform(a, viewProjectionMatrix);
			Vector3 ndcB = Transform(b, viewProjectionMatrix);
			Vector3 ndcC = Transform(c, viewProjectionMatrix);
			//Viewport変換を行ってScreen空間へ
			Vector3 screenA = Transform(ndcA, viewportMatrix);
			Vector3 screenB = Transform(ndcB, viewportMatrix);
			Vector3 screenC = Transform(ndcC, viewportMatrix);
			//ab,acで線を引く
			Novice::DrawLine(static_cast<int>(screenA.x), static_cast<int>(screenA.y),
				static_cast<int>(screenB.x), static_cast<int>(screenB.y), color);
			Novice::DrawLine(static_cast<int>(screenC.x), static_cast<int>(screenC.y),
				static_cast<int>(screenA.x), static_cast<int>(screenA.y), color);
		}
	}
}
