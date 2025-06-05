#include <Novice.h>
#include "Vector3Class.h"
#include "Vector3Calculations.h"
#include "Matrix4x4.h"
#include "MatrixCalculations.h"
#include "Camera.h"
#include "DrawGrid.h"
#include "Draw.h"

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

	std::unique_ptr<Arm> arm;
	arm = std::make_unique<Arm>();

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


		camera->Update(keys);
		arm->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		arm->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
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
