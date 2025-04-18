#include "DrawGrid.h"
#include <cstdint>
#include <Vector3Class.h>
#include <MatrixCalculations.h>
#include <Novice.h>

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;//Gridの半分の幅
	const uint32_t kSubdivision = 10;//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / static_cast<float>(kSubdivision);//1つ分の長さ
	//奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		Vector3 worldLinePos[2]{};
		worldLinePos[0] = { static_cast<float>(xIndex) * kGridEvery - static_cast<float>(kSubdivision / 4), 0.f, kGridEvery * static_cast<float>(kSubdivision) / 2.f };
		worldLinePos[1] = { static_cast<float>(xIndex) * kGridEvery - static_cast<float>(kSubdivision / 4), 0.f,-kGridEvery * static_cast<float>(kSubdivision) / 2.f };
		//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
		Vector3 ndcVertex1 = Transform(worldLinePos[0], viewProjectionMatrix);
		Vector3 ndcVertex2 = Transform(worldLinePos[1], viewProjectionMatrix);
		//Viewport変換を行ってScreen空間へ
		Vector3 screenVertices1 = Transform(ndcVertex1, viewportMatrix);
		Vector3 screenVertices2 = Transform(ndcVertex2, viewportMatrix);
		//線の描画
		if (xIndex == 5) {
			Novice::DrawLine(static_cast<int>(screenVertices1.x), static_cast<int>(screenVertices1.y),
				static_cast<int>(screenVertices2.x), static_cast<int>(screenVertices2.y), BLACK);
		} else {
			Novice::DrawLine(static_cast<int>(screenVertices1.x), static_cast<int>(screenVertices1.y),
				static_cast<int>(screenVertices2.x), static_cast<int>(screenVertices2.y), 0xaaaaaaff);
		}

	}

	//左から右への線を順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		Vector3 worldLinePos[2]{};
		worldLinePos[0] = { kGridEvery * static_cast<float>(kSubdivision) / 2.f, 0.f, static_cast<float>(zIndex) * kGridEvery - static_cast<float>(kSubdivision / 4) };
		worldLinePos[1] = { -kGridEvery * static_cast<float>(kSubdivision) / 2.f, 0.f,static_cast<float>(zIndex) * kGridEvery - static_cast<float>(kSubdivision / 4) };
		//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
		Vector3 ndcVertex1 = Transform(worldLinePos[0], viewProjectionMatrix);
		Vector3 ndcVertex2 = Transform(worldLinePos[1], viewProjectionMatrix);
		//Viewport変換を行ってScreen空間へ
		Vector3 screenVertices1 = Transform(ndcVertex1, viewportMatrix);
		Vector3 screenVertices2 = Transform(ndcVertex2, viewportMatrix);
		//線の描画
		if (zIndex == 5) {
			Novice::DrawLine(static_cast<int>(screenVertices1.x), static_cast<int>(screenVertices1.y),
				static_cast<int>(screenVertices2.x), static_cast<int>(screenVertices2.y), BLACK);
		} else {
			Novice::DrawLine(static_cast<int>(screenVertices1.x), static_cast<int>(screenVertices1.y),
				static_cast<int>(screenVertices2.x), static_cast<int>(screenVertices2.y), 0xaaaaaaff);
		}

	}
}