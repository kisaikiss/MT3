#include "Collision.h"
#include <Vector3Calculations.h>

Vector3 ClosestPoint(const Point& point, const Shape& shape) {
	// 点と線分の最近接点を求める
	Vector3 result{};
	Vector3 diff = point.GetPos() - shape.GetOrigin();
	Vector3 project = Project(diff, shape.GetDiff());

	if (shape.GetShapeType() == ShapeType::SEGMENT) {
		// 線分の長さを超えた場合は、線分の端点を返す
		if (Length(project) > Length(shape.GetDiff())) {
			result = shape.GetOrigin() + Normalize(shape.GetDiff()) * Length(shape.GetDiff());
		} else if (Length(shape.GetOrigin()  - project) < Length(shape.GetOrigin())) {
			result = shape.GetOrigin();
		} else {
			result = shape.GetOrigin() + project;
		}
	} else if (shape.GetShapeType() == ShapeType::RAY) {
		if (Length(shape.GetOrigin() - project) < Length(shape.GetOrigin())) {
			result = shape.GetOrigin();
		} else {
			result = shape.GetOrigin() + project;
		}
	} else if (shape.GetShapeType() == ShapeType::LINE) {
		result = shape.GetOrigin() + project;
	} 

	return result;
}

bool CheckCollisionSpheres(const Sphere& sphere1, const Sphere& sphere2) {
	float distance = Length(sphere1.GetPos() - sphere2.GetPos());
	if (distance <= sphere1.GetRadius() + sphere2.GetRadius()) {
		return true;
	}
	return false;
}

float CalculateDistancePointPlane(const Vector3& point, const Plane& plane) {
	float result = Dot(plane.GetNormal(), point) - plane.GetDistance();
	return result;
}

bool CheckCollisionPlaneSphere(const Sphere& sphere, const Plane& plane) {
	float distance = fabsf(CalculateDistancePointPlane(sphere.GetPos(), plane));
	if (distance <= sphere.GetRadius()) {
		return true;
	}
	return false;
}


bool CheckCollisionPlaneShape(const Shape& shape, const Plane& plane) {
	//垂直判定を行うために、法線と線の内積を求める
	float dot = Dot(plane.GetNormal(), shape.GetDiff());

	//垂直 = 平行であるので衝突していない
	if (dot == 0.0f) {
		return false;
	}

	//tを求める
	float t = (plane.GetDistance() - Dot(shape.GetOrigin(), plane.GetNormal())) / dot;

	//tの値と線の種類によって衝突しているか判断する
	if (0 <= t && t <= 1) {
		return true;
	} else if (t > 1) {
		if (shape.GetShapeType() == ShapeType::SEGMENT) {
			return false;
		} else {
			return true;
		}
	} else {
		if (shape.GetShapeType() == ShapeType::LINE) {
			return true;
		} else {
			return false;
		}
	}
}