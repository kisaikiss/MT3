#include <Novice.h>
#include "Vector3Class.h"
#include "Vector3Calculations.h"
#include "Matrix4x4.h"
#include "MatrixCalculations.h"
#include "Triangle.h"
#include "Camera.h"
#include "Sphere.h"
#include "DrawGrid.h"
#include "Shape.h"
#include "Point.h"

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
	char keys[256] = {0};
	char preKeys[256] = {0};

	std::shared_ptr<Camera> camera;
	camera = std::make_shared<Camera>();

	std::shared_ptr<Sphere> sphere;
	sphere = std::make_shared<Sphere>();
	sphere->SetRadius(0.5f);

	std::shared_ptr<Sphere> sphere2;
	sphere2 = std::make_shared<Sphere>();
	sphere2->SetPos({ 1.f, 0.f, 0.f });
	

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
		
		sphere->Update();
		sphere2->Update();
		camera->Update(keys);
		
		if (CheckCollisionSpheres(*sphere, *sphere2)) {
			sphere->OnCollision();
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		sphere->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		sphere2->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		
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
