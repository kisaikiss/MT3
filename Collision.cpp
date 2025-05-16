#include "Collision.h"
#include <Vector3Calculations.h>
#include <memory>
#include <algorithm>

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


bool CheckCollisionTriangleShape(const Shape& shape, const Triangle& triangle) {
	//三角形の各頂点を取得
	Vector3 vertices[3]{};
	triangle.GetVertices(vertices);

	//三角形の各頂点の座標から平面を求める
	std::unique_ptr<Plane> plane;
	plane = std::make_unique<Plane>();
	plane->Initialize(vertices[0], vertices[1], vertices[2]);

	//平面と当たっていなければ三角形とも当たっていないのでfalseで戻す
	if (!CheckCollisionPlaneShape(shape, *plane)) {
		return false;
	}

	Vector3 v01 = vertices[1] - vertices[0];
	Vector3 v12 = vertices[2] - vertices[1];
	Vector3 v20 = vertices[0] - vertices[2];

	float t = (plane->GetDistance() - Dot(shape.GetOrigin(), plane->GetNormal())) / Dot(plane->GetNormal(), shape.GetDiff());

	//平面との衝突点
	Vector3 p = shape.GetOrigin() + shape.GetDiff() * t;


	Vector3 v0p = p - vertices[0];
	Vector3 v1p = p - vertices[1];
	Vector3 v2p = p - vertices[2];

	//各辺をむすんだベクトルと、頂点と衝突点pを結んだベクトルの外積をとる
	Vector3 cross01 = Cross(v01, v1p);
	Vector3 cross12 = Cross(v12, v2p);
	Vector3 cross20 = Cross(v20, v0p);
	//全ての小三角形のクロス積と法線が同じ方向を向いていたら衝突
	if (Dot(cross01, plane->GetNormal()) >= 0.0f &&
		Dot(cross12, plane->GetNormal()) >= 0.0f &&
		Dot(cross20, plane->GetNormal()) >= 0.0f) {
		return true;
	}
	return false;
}

bool CheckCollisionAABB(const AABB& aabb, const AABB& aabb2) {
	if ((aabb.min.x <= aabb2.max.x && aabb.max.x >= aabb2.min.x) &&
		(aabb.min.y <= aabb2.max.y && aabb.max.y >= aabb2.min.y) &&
		(aabb.min.z <= aabb2.max.z && aabb.max.z >= aabb2.min.z)) {
		return true;
	}
	return false;
}


bool CheckCollisionSphereAABB(const AABB& aabb, const Sphere& sphere) {
	//最近接点を求める
	Vector3 closestPoint{
		std::clamp(sphere.GetPos().x,aabb.min.x,aabb.max.x),
		std::clamp(sphere.GetPos().y,aabb.min.y,aabb.max.y),
		std::clamp(sphere.GetPos().z,aabb.min.z,aabb.max.z)
	};
	//最近接点と球の中心との距離を求める
	float distance = Length(closestPoint - sphere.GetPos());
	//距離が半径よりも小さければ衝突
	if (distance <= sphere.GetRadius()) {
		return true;
	}
	return false;
}
