#include <Novice.h>
#include "Vector3Calculations.h"
#include "Vector3Operator.h"
#include "Matrix4x4.h"
#include "MatrixCalculations.h"
#include "Camera.h"
#include "DrawGrid.h"
#include "Draw.h"

#include "Ball.h"
#include "Sphere.h"
#include "Plane.h"
#include "Collision.h"

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

	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();

	std::shared_ptr<Plane> plane = std::make_shared<Plane>();
	plane->SetNormal(Normalize({ -0.2f,0.9f,-0.3f }));


	Ball ball{};
	ball.position = { 0.8f,1.2f,0.3f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = WHITE;
	ball.acceleration = { 0.0f,-9.8f,0.0f };

	sphere->SetRadius(ball.radius);
	sphere->SetPos(ball.position);

	//反発係数
	float e = 0.5f;

	bool isStart = false;

	float deltaTime = 1.0f / 60.0f;
	
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
		plane->Update();
		if (isStart) {
			ball.velocity = ball.velocity + ball.acceleration * deltaTime;
			ball.position = ball.position + ball.velocity * deltaTime;
			sphere->SetRadius(ball.radius);
			sphere->SetPos(ball.position);
			if (CheckCollisionPlaneSphere(*sphere.get(), *plane.get())) {
				Vector3 reflected = Reflect(ball.velocity, plane->GetNormal());
				Vector3 projectToNormal = Project(reflected, plane->GetNormal());
				Vector3 movingDirection = reflected - projectToNormal;
				ball.velocity = projectToNormal * e + movingDirection;
				
				// 押し戻し処理
				Vector3 planePoint = -plane->GetDistance() / Dot(plane->GetNormal(), plane->GetNormal()) * plane->GetNormal();
				float distance = Dot(ball.position - planePoint, Normalize(plane->GetNormal()));
				float penetration = ball.radius - distance;
				if (penetration > 0.0f)
				{
					ball.position = ball.position + Normalize(plane->GetNormal()) * penetration;
				}
				 
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		sphere->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		plane->Draw(camera->GetVeiwProjectionMatrix(), camera->GetVeiwportMatrix());
		
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
