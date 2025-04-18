#include "Triangle.h"
#include "MatrixCalculations.h"
#include <string>
#include <sstream>
#include <Novice.h>

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

int32_t Triangle::triangleNum = 0;

Triangle::Triangle() {
	triangleNum++;
	myNumber_ = triangleNum;
	vertices_[0] = { 0.f,0.5f,0.f };
	vertices_[1] = { 0.5f,-0.5f,0.f };
	vertices_[2] = { -0.5f,-0.5f,0.f };
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = { 0.0f,0.0f,0.0f };
	translate_ = { 0.0f,0.0f,0.0f };
	color_ = RED;
}

void Triangle::Update() {
#ifdef _DEBUG
	/*std::stringstream myNumString;
	myNumString << myNumber_;
	std::string name = "Triangle";
	name = name + myNumString.str();
	ImGui::Begin(name.c_str());
	ImGui::DragFloat3("vertices1", &vertices_[0].x, 0.01f);
	ImGui::DragFloat3("vertices2", &vertices_[1].x, 0.01f);
	ImGui::DragFloat3("vertices3", &vertices_[2].x, 0.01f);
	ImGui::DragFloat3("translate", &translate_.x, 0.01f);
	ImGui::End();*/
#endif // _DEBUG
}

void Triangle::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) const {
	//三角形をスクリーン空間へと頂点を変換する
	Matrix4x4 worldMatrix_ = MakeAffineMatrix(scale_, rotate_, translate_);
	Matrix4x4 worldProjectionMatrix = Multiply(worldMatrix_, viewProjectionMatrix);
	Vector3 screenVertices[3]{};
	for (uint32_t i = 0; i < 3; ++i) {
		//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
		Vector3 ndcVertex = Transform(vertices_[i], worldProjectionMatrix);
		//Viewport変換を行ってScreen空間へ
		screenVertices[i] = Transform(ndcVertex, viewportMatrix);
	}
	Novice::DrawTriangle(static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
		static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
		static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y), color_, kFillModeSolid);
}

void Triangle::GetVertices(Vector3* vertices) const {
	if (vertices == nullptr) {
		return;
	}

	for (int32_t i = 0; i < 3; i++) {
		*vertices = vertices_[i];
		vertices++;
	}
}

void Triangle::SetRotate(Vector3& rotate) {
	rotate_ = rotate;
}

void Triangle::SetTranslate(Vector3& translate) {
	translate_ = translate;
}
