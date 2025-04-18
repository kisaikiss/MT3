#include <Novice.h>
#include "Vector3Class.h"
#include "Vector3Calculations.h"
#include "Matrix4x4.h"
#include "MatrixCalculations.h"
#include "Triangle.h"
#include "Camera.h"

#include "Define.h"

#include <memory>

const char kWindowTitle[] = "LE2A_04_コバヤシ_マサト_タイトル";



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	std::shared_ptr<Camera> camera;
	camera = std::make_shared<Camera>();

	std::shared_ptr<Triangle> triangle;
	triangle = std::make_shared<Triangle>();

	Vector3 triangleTranslate{};
	Vector3 triangleRotate{};
	const float kTriangleSpeed = 0.02f;

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = Cross(v1, v2);

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
		triangle->Update();
		
		if (keys[DIK_W]) {
			triangleTranslate.z += kTriangleSpeed;
		}
		if (keys[DIK_S]) {
			triangleTranslate.z -= kTriangleSpeed;
		}
		if (keys[DIK_A]) {
			triangleTranslate.x -= kTriangleSpeed;
		}
		if (keys[DIK_D]) {
			triangleTranslate.x += kTriangleSpeed;
		}
		triangleRotate.y += 0.1f;
		triangle->SetRotate(triangleRotate);
		triangle->SetTranslate(triangleTranslate);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		triangle->Draw(camera->GetVeiwProjectionMatrix(),camera->GetVeiwportMatrix());
		VectorScreenPrintf(0, 0, cross, "Cross");
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
