#include <Novice.h>
#include "Vector3Calculations.h"
#include "Matrix4x4.h"
#include "MatrixCalculations.h"
#include "Camera.h"
#include "DrawGrid.h"
#include "Draw.h"

#include "Spring.h"
#include "Ball.h"
#include "SpringClass.h"

#include "Arm.h"

#include "Define.h"

#include <memory>

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

	Spring spring{};
	spring.anchor = { 0.f,0.f,0.f };
	spring.naturalLength = 1.0f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	Ball ball{};
	ball.position = { 1.2f,0.0f,0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	bool isStart = false;

	std::unique_ptr<SpringClass> springClass = std::make_unique<SpringClass>(&spring, &ball);

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
			springClass->Update();
		}
		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		springClass->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		
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
