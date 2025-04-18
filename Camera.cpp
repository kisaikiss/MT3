#include "Camera.h"
#include "MatrixCalculations.h"
#include "Define.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

Camera::Camera() {
	pos_ = { 0.0f, 1.9f, -6.49f };
	rotate_ = { 0.26f,0.f,0.f };
	scale_ = { 1.f,1.f,1.f };
	worldMatrix_ = MakeAffineMatrix(scale_, rotate_, pos_);
	Matrix4x4 viewMatrix = Inverse(worldMatrix_);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(
		0.45f,
		static_cast<float>(Define::kWindowWidth) / static_cast<float>(Define::kWindowHeight),
		0.1f,
		100.f
	);
	viewProjectionMatrix_ = Multiply(viewMatrix, projectionMatrix);
	viewportMatrix_ = MakeViewportMatrix(0, 0, 1280.f, 720.f, 0.f, 1.f);
}

void Camera::Update() {
#ifdef _DEBUG
	ImGui::Begin("camera");
	ImGui::SetWindowPos({ 20.f, 20.f });
	ImGui::DragFloat3("position", &pos_.x, 0.01f);
	ImGui::DragFloat3("rotate", &rotate_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG

	worldMatrix_ = MakeAffineMatrix(scale_, rotate_, pos_);
	Matrix4x4 viewMatrix = Inverse(worldMatrix_);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(
		0.45f,
		1280.f / 720.f,
		0.1f,
		100.f
	);
	viewProjectionMatrix_ = Multiply(viewMatrix, projectionMatrix);
}
