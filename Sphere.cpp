#include "Sphere.h"
#include "Draw.h"
#include <corecrt_math_defines.h>
#include <corecrt_math.h>
#include <MatrixCalculations.h>
#include <Novice.h>
#include <string>
#include <sstream>

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

int32_t Sphere::sphereNum = 1;

Sphere::Sphere() {
	centerPos_ = { 0.f,0.f,0.f };
	radius_ = 0.2f;
	color_ = WHITE;
	myNumber_ = sphereNum;
	sphereNum++;
}

Sphere::~Sphere() {
	sphereNum--;
}

void Sphere::Update() {
#ifdef _DEBUG
	std::stringstream myNumString;
	myNumString << myNumber_;
	std::string name = "Sphere";
	name = name + myNumString.str();
	ImGui::Begin(name.c_str());
	ImGui::DragFloat3("position", &centerPos_.x, 0.01f);
	ImGui::DragFloat("radius", &radius_, 0.01f);
	ImGui::End();
#endif // _DEBUG
	color_ = WHITE;
}

void Sphere::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	DrawSphere(viewProjectionMatrix, viewportMatrix, centerPos_, radius_, color_);
}

void Sphere::OnCollision() {
	color_ = RED;
}

void Sphere::SetPos(const Vector3& position) {
	centerPos_ = position;
}
