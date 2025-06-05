#include "Box.h"
#include "MatrixCalculations.h"
#include "Vector3Operator.h"
#include <string>
#include <sstream>
#include <Novice.h>

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

int32_t Box::boxNum = 0;

Box::Box() {
	boxNum++;
	myNumber_ = boxNum;
	localAABB_.min = { -0.5f,-0.5f,-0.5f };
	localAABB_.max = { 0.5f,0.5f,0.5f };
	pos_ = { 0.f,0.f,0.f };
	worldAABB_.min = localAABB_.min;
	worldAABB_.max = localAABB_.max;
	color_ = WHITE;
}

Box::~Box() {
	boxNum--;
}

void Box::Update() {
	AABB preLocalAABB = localAABB_;
#ifdef _DEBUG
	std::stringstream myNumString;
	myNumString << myNumber_;
	std::string name = "Box";
	name = name + myNumString.str();
	ImGui::Begin(name.c_str());
	ImGui::DragFloat3("position", &pos_.x, 0.01f);
	ImGui::DragFloat3("localMin", &localAABB_.min.x, 0.01f);
	ImGui::DragFloat3("localMax", &localAABB_.max.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	//maxがminを下回ったら1フレーム前に戻す
	if (localAABB_.max.x < localAABB_.min.x) {
		localAABB_.max.x = preLocalAABB.max.x;
		localAABB_.min.x = preLocalAABB.min.x;
	}
	if (localAABB_.max.y < localAABB_.min.y) {
		localAABB_.max.y = preLocalAABB.max.y;
		localAABB_.min.y = preLocalAABB.min.y;
	}
	if (localAABB_.max.z < localAABB_.min.z) {
		localAABB_.max.z = preLocalAABB.max.z;
		localAABB_.min.z = preLocalAABB.min.z;
	}
	worldAABB_.min = localAABB_.min + pos_;
	worldAABB_.max = localAABB_.max + pos_;
	color_ = WHITE;
}

void Box::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) const {
	const int cubeIndex[12][2]{
		{0, 1}, {1, 3}, {3, 2}, {2, 0}, // キューブの表
		{4, 5}, {5, 7}, {7, 6}, {6, 4}, // キューブの裏
		{0, 4}, {1, 5}, {2, 6}, {3, 7}  // キューブの左右
	};

	//キューブの各頂点の位置
	Vector3 cubeVertices[8] = {
		{worldAABB_.min.x, worldAABB_.min.y, worldAABB_.min.z},
		{worldAABB_.max.x, worldAABB_.min.y, worldAABB_.min.z},
		{worldAABB_.min.x, worldAABB_.max.y, worldAABB_.min.z},
		{worldAABB_.max.x, worldAABB_.max.y, worldAABB_.min.z},
		{worldAABB_.min.x, worldAABB_.min.y, worldAABB_.max.z},
		{worldAABB_.max.x, worldAABB_.min.y, worldAABB_.max.z},
		{worldAABB_.min.x, worldAABB_.max.y, worldAABB_.max.z},
		{worldAABB_.max.x, worldAABB_.max.y, worldAABB_.max.z}
	};

	// スクリーン座標を求める
	Vector3 screenVerties[8];
	for (int i = 0; i < 8; i++) {
		Vector3 ndcVertex = Transform(cubeVertices[i], viewProjectionMatrix);
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

void Box::OnCollision() {
	color_ = RED;
}

void Box::SetWorldAABB(const AABB& worldAABB) {
	localAABB_.min = worldAABB.min;
	localAABB_.max = worldAABB.max;

	pos_.x = localAABB_.min.x + (localAABB_.max.x - localAABB_.min.x) / 2;
	pos_.y = localAABB_.min.y + (localAABB_.max.y - localAABB_.min.y) / 2;
	pos_.z = localAABB_.min.z + (localAABB_.max.z - localAABB_.min.z) / 2;

	Vector3 width = { localAABB_.max.x - localAABB_.min.x, localAABB_.max.y - localAABB_.min.y, localAABB_.max.z - localAABB_.min.z };

	localAABB_.min.x = -width.x / 2;
	localAABB_.min.y = -width.y / 2;
	localAABB_.min.z = -width.z / 2;
	localAABB_.max.x = width.x / 2;
	localAABB_.max.y = width.y / 2;
	localAABB_.max.z = width.z / 2;
}
