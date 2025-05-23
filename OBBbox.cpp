#include "OBBbox.h"
#include <Novice.h>
#include <sstream>
#include <imgui.h>
#include <MatrixCalculations.h>

int32_t OBBbox::obbBoxNum = 0;

OBBbox::OBBbox() {
	obbBoxNum++;
	myNumber_ = obbBoxNum;
	obb_.center = {0.f,0.f,0.f};
	rotate_ = { 0.f,0.f,0.f };
	obb_.size = { 1.f,1.f,1.f };
	color_ = WHITE;
}

OBBbox::~OBBbox() {

}

void OBBbox::Update() {
#ifdef _DEBUG
	std::stringstream myNumString;
	myNumString << myNumber_;
	std::string name = "OBBbox";
	name = name + myNumString.str();
	ImGui::Begin(name.c_str());
	ImGui::DragFloat3("position", &obb_.center.x, 0.01f);
	ImGui::DragFloat3("rotate", &rotate_.x, 0.01f);
	ImGui::DragFloat3("size", &obb_.size.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	color_ = WHITE;

	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotate_);

	obb_.orientations[0] = { rotateMatrix.m[0][0], rotateMatrix.m[0][1] ,rotateMatrix.m[0][2] };
	obb_.orientations[1] = { rotateMatrix.m[1][0], rotateMatrix.m[1][1] ,rotateMatrix.m[1][2] };
	obb_.orientations[2] = { rotateMatrix.m[2][0], rotateMatrix.m[2][1] ,rotateMatrix.m[2][2] };
}

void OBBbox::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) const {
	Matrix4x4 worldMatrix = MakeAffineMatrix({1.f,1.f,1.f} , rotate_, obb_.center);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);

	const int cubeIndex[12][2]{
			{0, 1}, {1, 3}, {3, 2}, {2, 0}, // キューブの表
			{4, 5}, {5, 7}, {7, 6}, {6, 4}, // キューブの裏
			{0, 4}, {1, 5}, {2, 6}, {3, 7}  // キューブの左右
	};

	//キューブの各頂点の位置
	Vector3 cubeVertices[8] = {
		{obb_.center.x - obb_.size.x, obb_.center.y - obb_.size.y, obb_.center.z - obb_.size.z},
		{obb_.center.x + obb_.size.x, obb_.center.y - obb_.size.y, obb_.center.z - obb_.size.z},
		{obb_.center.x - obb_.size.x, obb_.center.y + obb_.size.y, obb_.center.z - obb_.size.z},
		{obb_.center.x + obb_.size.x, obb_.center.y + obb_.size.y, obb_.center.z - obb_.size.z},
		{obb_.center.x - obb_.size.x, obb_.center.y - obb_.size.y, obb_.center.z + obb_.size.z},
		{obb_.center.x + obb_.size.x, obb_.center.y - obb_.size.y, obb_.center.z + obb_.size.z},
		{obb_.center.x - obb_.size.x, obb_.center.y + obb_.size.y, obb_.center.z + obb_.size.z},
		{obb_.center.x + obb_.size.x, obb_.center.y + obb_.size.y, obb_.center.z + obb_.size.z}
	};

	// スクリーン座標を求める
	Vector3 screenVerties[8];
	for (int i = 0; i < 8; i++) {
		Vector3 ndcVertex = Transform(cubeVertices[i], worldViewProjectionMatrix);
		screenVerties[i] = Transform(ndcVertex, viewportMatrix);
	}

	// 線分を描画する
	for (int i = 0; i < 12; i++) {
		int index1 = cubeIndex[i][0];
		int index2 = cubeIndex[i][1];
		Novice::DrawLine(static_cast<int>(screenVerties[index1].x), static_cast<int>(screenVerties[index1].y),
			static_cast<int>(screenVerties[index2].x), static_cast<int>(screenVerties[index2].y), color_);
	}
}

void OBBbox::OnCollision() {
	color_ = RED;
}

