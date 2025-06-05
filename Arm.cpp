#include "Arm.h"
#include "MatrixCalculations.h"
#include "Draw.h"

#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG


Arm::Arm() {
	translates_[0] = { 0.2f,1.0f,0.0f };
	translates_[1] = { 0.4f,0.0f,0.0f };
	translates_[2] = { 0.3f,0.0f,0.0f };

	rotates_[0] = { 0.0f,0.0f,-6.8f };
	rotates_[1] = { 0.0f,0.0f,-1.4f };
	rotates_[2] = { 0.0f,0.0f,0.0f };

	for (uint32_t i = 0; i < 3; i++) {
		scales_[i] = { 1.f,1.f,1.f };

		worldMatrixs_[i] = MakeAffineMatrix(scales_[i], rotates_[i], translates_[i]);
	}

	worldMatrixs_[1] = Multiply(worldMatrixs_[1], worldMatrixs_[0]);
	worldMatrixs_[2] = Multiply(worldMatrixs_[2], worldMatrixs_[1]);

}

void Arm::Update() {
#ifdef _DEBUG
	ImGui::Begin("arm");
	ImGui::DragFloat3("translats[0]", &translates_[0].x, 0.01f);
	ImGui::DragFloat3("rotates[0]", &rotates_[0].x, 0.01f);
	ImGui::DragFloat3("scales[0]", &scales_[0].x, 0.01f);
	ImGui::DragFloat3("translats[1]", &translates_[1].x, 0.01f);
	ImGui::DragFloat3("rotates[1]", &rotates_[1].x, 0.01f);
	ImGui::DragFloat3("scales[1]", &scales_[1].x, 0.01f);
	ImGui::DragFloat3("translats[2]", &translates_[2].x, 0.01f);
	ImGui::DragFloat3("rotates[2]", &rotates_[2].x, 0.01f);
	ImGui::DragFloat3("scales[2]", &scales_[2].x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	for (uint32_t i = 0; i < 3; i++) {
		worldMatrixs_[i] = MakeAffineMatrix(scales_[i], rotates_[i], translates_[i]);
	}
	worldMatrixs_[1] = Multiply(worldMatrixs_[1], worldMatrixs_[0]);
	worldMatrixs_[2] = Multiply(worldMatrixs_[2], worldMatrixs_[1]);
}

void Arm::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kRadius = 0.05f;
	const uint32_t kRed = 0xff0000ff;
	const uint32_t kGreen= 0x00ff00ff;
	const uint32_t kBlue = 0x0000ffff;
	const uint32_t kWhite = 0xffffffff;

	Vector3 worldPositions[3]{};
	for (uint32_t i = 0; i < 3; i++) {
		worldPositions[i].x = worldMatrixs_[i].m[3][0];
		worldPositions[i].y = worldMatrixs_[i].m[3][1];
		worldPositions[i].z = worldMatrixs_[i].m[3][2];
	}
	
	DrawLine3D(viewProjectionMatrix, viewportMatrix, worldPositions[0], worldPositions[1], kWhite);
	DrawLine3D(viewProjectionMatrix, viewportMatrix, worldPositions[1], worldPositions[2], kWhite);

	DrawSphere(viewProjectionMatrix, viewportMatrix, worldMatrixs_[0], kRadius, kRed);
	DrawSphere(viewProjectionMatrix, viewportMatrix, worldMatrixs_[1], kRadius, kGreen);
	DrawSphere(viewProjectionMatrix, viewportMatrix, worldMatrixs_[2], kRadius, kBlue);
}
