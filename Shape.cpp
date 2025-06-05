#include "Shape.h"
#include <Vector3Calculations.h>
#include <MatrixCalculations.h>
#include "Vector3Operator.h"
#include <Novice.h>
#include <string>
#include <sstream>

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include <Collision.h>

void Shape::DrawClosestPoint(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, Point& point) {
	Vector3 closetPoint = ClosestPoint(point, *this);
	point.DrawPos(viewProjectionMatrix, viewportMatrix, closetPoint, BLACK);
}

void Shape::OnCollision() {
	color_ = RED;
}

int32_t Line::lineNum = 0;

Line::Line() {
	origin_ = { 0.f, 0.f, 0.f };
	diff_ = { 0.1f, 0.1f, 0.1f };
	lineNum++;
	myNumber_ = lineNum;
	color_ = WHITE;
	myType_ = ShapeType::LINE;
}

Line::~Line() {
	lineNum--;
}

void Line::Update() {
#ifdef _DEBUG
	std::stringstream myNumString;
	myNumString << myNumber_;
	std::string name = "Line";
	name = name + myNumString.str();
	ImGui::Begin(name.c_str());
	ImGui::DragFloat3("origin", &origin_.x, 0.01f);
	ImGui::DragFloat3("diff", &diff_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	color_ = WHITE;
}

void Line::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	Vector3 diff = Normalize(diff_) * 5.f;
	Vector3 diff2 = diff * -1.f;
	//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
	Vector3 ndcOrigin = Transform(origin_ + diff2, viewProjectionMatrix);
	Vector3 ndcOrigin2diff = Transform(origin_ + diff, viewProjectionMatrix);
	//Viewport変換を行ってScreen空間へ
	Vector3 screenOrigin = Transform(ndcOrigin, viewportMatrix);
	Vector3 screenOrigin2diff = Transform(ndcOrigin2diff, viewportMatrix);

	Novice::DrawLine(static_cast<int>(screenOrigin.x), static_cast<int>(screenOrigin.y),
		static_cast<int>(screenOrigin2diff.x), static_cast<int>(screenOrigin2diff.y), color_);

	//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
	Vector3 ndcEllipsePos = Transform(origin_, viewProjectionMatrix);
	//Viewport変換を行ってScreen空間へ
	Vector3 screenEllipsePos = Transform(ndcEllipsePos, viewportMatrix);
	Novice::DrawEllipse(static_cast<int>(screenEllipsePos.x), static_cast<int>(screenEllipsePos.y), 3, 3, 0.f, 0x00ff00ff, kFillModeSolid);
}

int32_t Ray::rayNum = 0;

Ray::Ray() {
	origin_ = { 0.f, 0.f, 0.f };
	diff_ = { 0.1f, 0.f, 0.f };
	rayNum++;
	myNumber_ = rayNum;
	myType_ = ShapeType::RAY;
	color_ = WHITE;
}

Ray::~Ray() {
	rayNum--;
}

void Ray::Update() {
#ifdef _DEBUG
	std::stringstream myNumString;
	myNumString << myNumber_;
	std::string name = "Ray";
	name = name + myNumString.str();
	ImGui::Begin(name.c_str());
	ImGui::DragFloat3("origin", &origin_.x, 0.01f);
	ImGui::DragFloat3("diff", &diff_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	color_ = WHITE;
}

void Ray::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	Vector3 diff = Normalize(diff_) * 5.f;
	//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
	Vector3 ndcOrigin = Transform(origin_, viewProjectionMatrix);
	Vector3 ndcOrigin2diff = Transform(origin_ + diff, viewProjectionMatrix);
	//Viewport変換を行ってScreen空間へ
	Vector3 screenOrigin = Transform(ndcOrigin, viewportMatrix);
	Vector3 screenOrigin2diff = Transform(ndcOrigin2diff, viewportMatrix);

	Novice::DrawLine(static_cast<int>(screenOrigin.x), static_cast<int>(screenOrigin.y),
		static_cast<int>(screenOrigin2diff.x), static_cast<int>(screenOrigin2diff.y), color_);

	//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
	Vector3 ndcEllipsePos = Transform(origin_, viewProjectionMatrix);
	//Viewport変換を行ってScreen空間へ
	Vector3 screenEllipsePos = Transform(ndcEllipsePos, viewportMatrix);
	Novice::DrawEllipse(static_cast<int>(screenEllipsePos.x), static_cast<int>(screenEllipsePos.y), 3, 3, 0.f, 0x00ff00ff, kFillModeSolid);
}

int32_t Segment::segmentNum = 0;

Segment::Segment() {
	origin_ = { 0.f, 0.f, 0.f };
	diff_ = { 0.1f, 0.f, 0.f };
	segmentNum++;
	myNumber_ = segmentNum;
	myType_ = ShapeType::SEGMENT;
	color_ = WHITE;
}

Segment::~Segment() {
	segmentNum--;
}

void Segment::Update() {
#ifdef _DEBUG
	std::stringstream myNumString;
	myNumString << myNumber_;
	std::string name = "Segment";
	name = name + myNumString.str();
	ImGui::Begin(name.c_str());
	ImGui::DragFloat3("origin", &origin_.x, 0.01f);
	ImGui::DragFloat3("diff", &diff_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	color_ = WHITE;
}

void Segment::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
	Vector3 ndcOrigin = Transform(origin_, viewProjectionMatrix);
	Vector3 ndcOrigin2diff = Transform(origin_ + diff_, viewProjectionMatrix);
	//Viewport変換を行ってScreen空間へ
	Vector3 screenOrigin = Transform(ndcOrigin, viewportMatrix);
	Vector3 screenOrigin2diff = Transform(ndcOrigin2diff, viewportMatrix);

	Novice::DrawLine(static_cast<int>(screenOrigin.x), static_cast<int>(screenOrigin.y),
		static_cast<int>(screenOrigin2diff.x), static_cast<int>(screenOrigin2diff.y), color_);

	//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることとなる
	Vector3 ndcEllipsePos = Transform(origin_, viewProjectionMatrix);
	//Viewport変換を行ってScreen空間へ
	Vector3 screenEllipsePos = Transform(ndcEllipsePos, viewportMatrix);
	Novice::DrawEllipse(static_cast<int>(screenEllipsePos.x), static_cast<int>(screenEllipsePos.y), 3, 3, 0.f, 0x00ff00ff, kFillModeSolid);
}