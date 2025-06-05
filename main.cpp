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
#include "Plane.h"
#include "Box.h"
#include "OBBbox.h"

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


	std::shared_ptr<OBBbox> box1;
	box1 = std::make_shared<OBBbox>();
	box1->SetPosition({ -1.3f,0.f,0.f });
	box1->SetRotate({ 0.0f,0.0f,2.0f });

	std::shared_ptr<Box> box2;
	box2 = std::make_shared<Box>();
	//box2->SetPosition({ 1.f,0.f,0.f });

	
	//Box

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
		
		box1->Update();
		box2->Update();
		camera->Update(keys);
		
		if (CheckCollisionOBBAABB(box1->GetOBB(), box2->GetWorldAABB())) {
			box1->OnCollision();
		}
	
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		box1->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		box2->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());

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
