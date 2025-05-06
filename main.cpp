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

	/*std::shared_ptr<Sphere> sphere;
	sphere = std::make_shared<Sphere>();*/

	std::shared_ptr<Point> point;
	point = std::make_shared<Point>();
	point->SetPos({ -1.5f, 0.6f, 0.6f });

	std::shared_ptr<Shape> segment;
	segment = std::make_shared<Segment>();
	segment->SetOrigin({ -2.0f, -1.0f, 0.0f });
	segment->SetDiff({ 3.0f, 2.0f, 2.0f });

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
		Vector3 project = Project(point->GetPos() - segment->GetOrigin(), segment->GetDiff());
		
		
		//sphere->Update();
		camera->Update(keys);
		segment->Update();
		point->Update();
		ImGui::Begin("project");
		ImGui::InputFloat3("Project", &project.x, "%.3f",ImGuiInputTextFlags_ReadOnly);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		//sphere->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		segment->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		point->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		segment->DrawClosestPoint(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix(), *point);
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
