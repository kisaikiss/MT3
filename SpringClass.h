#pragma once
#include "Matrix4x4.h"
//前方宣言
struct Spring;
struct Ball;


class SpringClass {
public:
	SpringClass(Spring* spring, Ball* ball);
	~SpringClass() = default;

	void Update();
	void Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) const;

	void SetSpring(Spring* spring) { spring_ = spring; }
	void SetBall(Ball* ball) { ball_ = ball; }
private:
	Spring* spring_;
	Ball* ball_;
	float deltaTime_;
};

