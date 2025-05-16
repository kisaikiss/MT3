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

	AABB aabb1 = {
		-0.5f, -0.5f, -0.5f,
		0.0f, 0.0f, 0.0f };
	

	std::shared_ptr<Box> box;
	box = std::make_shared<Box>();
	box->SetWorldAABB(aabb1); // AABBの最小点と最大点を指定して初期化

	aabb1 = {
		0.2f, 0.2f, 0.2f,
		1.0f, 1.0f, 1.0f
	};

	std::shared_ptr<Sphere> sphere;
	sphere = std::make_shared<Sphere>();
	
	

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
		box->Update();
		camera->Update(keys);
		
		if (CheckCollisionSphereAABB(box->GetWorldAABB(), *sphere)) {
			box->OnCollision();
		}
	
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		sphere->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		box->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		
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
