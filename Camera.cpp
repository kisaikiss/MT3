#include "Camera.h"
#include "MatrixCalculations.h"
#include "Define.h"
#include "Vector3Operator.h"

#include <Novice.h>

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include <Vector3Calculations.h>

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

void Camera::Update(char keys[256]) {
#ifdef _DEBUG
	ImGui::Begin("camera");

	ImGui::DragFloat3("position", &pos_.x, 0.01f);
	ImGui::DragFloat3("rotate", &rotate_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	if (Novice::IsPressMouse(1)) {
		

		if (Novice::IsTriggerMouse(1)) {
			Novice::GetMousePosition(&mousePositionX_, &mousePositionY_);
			mousePositionX_ = 0;
			mousePositionY_ = 0;
			preMousePositionX_ = mousePositionX_;
			preMousePositionY_ = mousePositionY_;
		} else {
			preMousePositionX_ = mousePositionX_;
			preMousePositionY_ = mousePositionY_;
			Novice::GetMousePosition(&mousePositionX_, &mousePositionY_);
		}

		Vector3 CameraRotate{};
		if (preMousePositionX_ && mousePositionX_) {
			//カメラの回転はXとY反転させた方が直感的
			CameraRotate.x = static_cast<float>(mousePositionY_ - preMousePositionY_) / 200.f;
			CameraRotate.y = static_cast<float>(mousePositionX_ - preMousePositionX_) / 200.f;
		}

		//移動速度
		const float kSpeed = 0.1f;
		Vector3 velocity{};



		rotate_ = rotate_ + CameraRotate;
		if (keys[DIK_W]) {
			velocity.z += kSpeed;
		}
		if (keys[DIK_A]) {
			velocity.x -= kSpeed;
		}
		if (keys[DIK_S]) {
			velocity.z -= kSpeed;
		}
		if (keys[DIK_D]) {
			velocity.x += kSpeed;
		}

		//速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransforNormal(velocity, worldMatrix_);

		if (keys[DIK_E]) {
			velocity.y += kSpeed;
		}
		if (keys[DIK_Q]) {
			velocity.y -= kSpeed;
		}
		pos_ = pos_ + velocity;
	}
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
