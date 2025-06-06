#include <Novice.h>
#include "Vector3Calculations.h"
#include "Matrix4x4.h"
#include "MatrixCalculations.h"
#include "Camera.h"
#include "DrawGrid.h"
#include "Draw.h"
#include "Pendulum.h"


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

	Pendulum pendulum{};
	pendulum.anchor = { 0.0f,1.0f,0.0f };
	pendulum.length = 0.8f;
	pendulum.angle = 0.7f;
	pendulum.angularVelocity = 0.0f;
	pendulum.angularAcceleration = 0.0f;

	Vector3 p{};
	p.x = pendulum.anchor.x + std::sin(pendulum.angle) * pendulum.length;
	p.y = pendulum.anchor.y - std::cos(pendulum.angle) * pendulum.length;
	p.z = pendulum.anchor.z;

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
			pendulum.angularAcceleration = -(9.8f / pendulum.length) * std::sin(pendulum.angle);
			pendulum.angularVelocity += pendulum.angularAcceleration * deltaTime;
			pendulum.angle += pendulum.angularVelocity * deltaTime;

			p.x = pendulum.anchor.x + std::sin(pendulum.angle) * pendulum.length;
			p.y = pendulum.anchor.y - std::cos(pendulum.angle) * pendulum.length;
			p.z = pendulum.anchor.z;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());

		DrawSphere(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix(), p, 0.05f, WHITE);
		DrawLine3D(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix(), pendulum.anchor, p, WHITE);
		
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
