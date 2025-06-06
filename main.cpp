#include <Novice.h>
#include "Vector3Calculations.h"
#include "Matrix4x4.h"
#include "MatrixCalculations.h"
#include "Camera.h"
#include "DrawGrid.h"
#include "Draw.h"
#include "ConicalPendulum.h"


#include "Arm.h"

#include "Define.h"

#include <memory>
#include <numbers>

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include <Collision.h>


const char kWindowTitle[] = "LE2A_04_コバヤシ_マサト_タイトル";



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::shared_ptr<Camera> camera;
	camera = std::make_shared<Camera>();


	bool isStart = false;

	float deltaTime = 1.0f / 60.0f;

	ConicalPendulum conicalPendulum{};
	conicalPendulum.anchor = { 0.0f,1.0f,0.0f };
	conicalPendulum.length = 0.8f;
	conicalPendulum.halfApexAngle = 0.7f;
	conicalPendulum.angle = 0.0f;
	conicalPendulum.angularVelocity = 0.0f;

	Vector3 p{};

	float radius = std::sin(conicalPendulum.halfApexAngle) * conicalPendulum.length;
	float height = std::cos(conicalPendulum.halfApexAngle) * conicalPendulum.length;

	p.x = conicalPendulum.anchor.x + std::cos(conicalPendulum.angle) * radius;
	p.y = conicalPendulum.anchor.y - height;
	p.z = conicalPendulum.anchor.z - std::sin(conicalPendulum.angle) * radius;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

#ifdef _DEBUG
		ImGui::Begin("Window");
		if (ImGui::Button("Start")) {
			isStart = true;
		}
		ImGui::End();
#endif // _DEBUG



		camera->Update(keys);
		if (isStart) {
			conicalPendulum.angularVelocity = std::sqrt(9.8f / (conicalPendulum.length * std::cos(conicalPendulum.halfApexAngle)));
			conicalPendulum.angle += conicalPendulum.angularVelocity * deltaTime;

			radius = std::sin(conicalPendulum.halfApexAngle) * conicalPendulum.length;
			height = std::cos(conicalPendulum.halfApexAngle) * conicalPendulum.length;

			p.x = conicalPendulum.anchor.x + std::cos(conicalPendulum.angle) * radius;
			p.y = conicalPendulum.anchor.y - height;
			p.z = conicalPendulum.anchor.z - std::sin(conicalPendulum.angle) * radius;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());

		DrawSphere(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix(), p, 0.05f, WHITE);
		DrawLine3D(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix(), conicalPendulum.anchor, p, WHITE);
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
