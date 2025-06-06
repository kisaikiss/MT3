#include "SpringClass.h"
#include "Draw.h"
#include "Ball.h"
#include "Spring.h"
#include "Novice.h"
#include "Vector3Operator.h"
#include "Vector3Calculations.h"

SpringClass::SpringClass(Spring* spring, Ball* ball) : spring_(spring), ball_(ball), deltaTime_(1.0f/60.f) {}

void SpringClass::Update() {
	Vector3 diff = ball_->position - spring_->anchor;
	float length = Length(diff);
	if (length != 0.0f) {
		Vector3 direction = Normalize(diff);
		Vector3 restPosition = spring_->anchor + direction * spring_->naturalLength;
		Vector3 displacement = length * (ball_->position - restPosition);
		Vector3 restoringForce = -spring_->stiffness * displacement;
		//減衰抵抗を計算する
		Vector3 dampingForce = -spring_->dampingCoefficient * ball_->velocity;
		//減衰抵抗も加味して、物体にかかる力を決定する
		Vector3 force = restoringForce + dampingForce;
		ball_->acceleration = force / ball_->mass;
	}
	//加速度も速度もどちらも秒を基準とした値である
	//それが、1/60秒間(deltaTime)適用されたと考える
	ball_->velocity = ball_->velocity + ball_->acceleration * deltaTime_;
	ball_->position = ball_->position + ball_->velocity * deltaTime_;
}

void SpringClass::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) const {
	DrawSphere(viewProjectionMatrix, viewportMatrix, ball_->position, ball_->radius, ball_->color);
	DrawLine3D(viewProjectionMatrix, viewportMatrix, spring_->anchor, ball_->position, WHITE);
};
