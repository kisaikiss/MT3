#include "Draw.h"
#include "MatrixCalculations.h"
#include <Novice.h>
#include <numbers>
#include <cmath>

void DrawSphere(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Vector3& position, const float& radius, const uint32_t& color) {
	const uint32_t kSubdivision = 16;//分割数
	const float kLatEvery = std::numbers::pi_v<float> / static_cast<float>(kSubdivision);//緯度分割1つ分の角度
	const float kLonEvery = (2.f * std::numbers::pi_v<float>) / static_cast<float>(kSubdivision);//経度分割1つ分の角度


	//緯度の方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -std::numbers::pi_v<float> / 2.f + kLatEvery * latIndex;//現在の緯度
		//経度の方向に分割 0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;//現在の経度
			//world座標系でのa,b,cを求める
			Vector3 a = {
				position.x + radius * std::cos(lat) * cosf(lon),
				position.y + radius * std::sin(lat),
				position.z + radius * cosf(lat) * sinf(lon)
			};
			Vector3 b = {
				position.x + radius * cosf(lat + kLatEvery) * cosf(lon),
				position.y + radius * sinf(lat + kLatEvery),
				position.z + radius * cosf(lat + kLatEvery) * sinf(lon)
			};
			Vector3 c = {
				position.x + radius * cosf(lat) * cosf(lon + kLonEvery),
				position.y + radius * sinf(lat),
				position.z + radius * cosf(lat) * sinf(lon + kLonEvery)
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

void DrawSphere(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Matrix4x4& worldMatrix, const float& radius, const uint32_t& color) {
	const uint32_t kSubdivision = 16;//分割数
	const float kLatEvery = std::numbers::pi_v<float> / static_cast<float>(kSubdivision);//緯度分割1つ分の角度
	const float kLonEvery = (2.f * std::numbers::pi_v<float>) / static_cast<float>(kSubdivision);//経度分割1つ分の角度


	//緯度の方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -std::numbers::pi_v<float> / 2.f + kLatEvery * latIndex;//現在の緯度
		//経度の方向に分割 0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;//現在の経度
			//world座標系でのa,b,cを求める
			Vector3 a = {
				radius* std::cos(lat) * cosf(lon),
				radius* std::sin(lat),
				radius* cosf(lat) * sinf(lon)
			};
			Vector3 b = {
				radius* cosf(lat + kLatEvery) * cosf(lon),
				radius* sinf(lat + kLatEvery),
				radius* cosf(lat + kLatEvery) * sinf(lon)
			};
			Vector3 c = {
				radius* cosf(lat) * cosf(lon + kLonEvery),
				radius* sinf(lat),
				radius* cosf(lat) * sinf(lon + kLonEvery)
			};
			//a,b,cをScreen座標系まで変換
			//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
			Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);
			Vector3 ndcA = Transform(a, worldViewProjectionMatrix);
			Vector3 ndcB = Transform(b, worldViewProjectionMatrix);
			Vector3 ndcC = Transform(c, worldViewProjectionMatrix);
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

void DrawLine3D(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Vector3& stratPosition, const Vector3& endPosition, const uint32_t& color) {
	//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
	Vector3 ndcStrat = Transform(stratPosition, viewProjectionMatrix);
	Vector3 ndcEnd = Transform(endPosition, viewProjectionMatrix);
	//Viewport変換を行ってScreen空間へ
	Vector3 screenStart = Transform(ndcStrat, viewportMatrix);
	Vector3 screenEnd = Transform(ndcEnd, viewportMatrix);

	Novice::DrawLine(static_cast<int>(screenStart.x), static_cast<int>(screenStart.y),
		static_cast<int>(screenEnd.x), static_cast<int>(screenEnd.y), color);
}
