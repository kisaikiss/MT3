#include "Collision.h"
#include <Vector3Calculations.h>
#include <memory>
#include <algorithm>
#include <MatrixCalculations.h>

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

bool CheckCollisionShapeAABB(const AABB& aabb, const Shape& shape) {

	//衝突点を計算する
	float tXMin = (aabb.min.x - shape.GetOrigin().x) / shape.GetDiff().x;
	float tXMax = (aabb.max.x - shape.GetOrigin().x) / shape.GetDiff().x;
	float tYMin = (aabb.min.y - shape.GetOrigin().y) / shape.GetDiff().y;
	float tYMax = (aabb.max.y - shape.GetOrigin().y) / shape.GetDiff().y;
	float tZMin = (aabb.min.z - shape.GetOrigin().z) / shape.GetDiff().z;
	float tZMax = (aabb.max.z - shape.GetOrigin().z) / shape.GetDiff().z;

	//衝突点の近い方と遠い方を計算する
	float tNearX = std::min(tXMin, tXMax);
	float tFarX = std::max(tXMin, tXMax);
	float tNearY = std::min(tYMin, tYMax);
	float tFarY = std::max(tYMin, tYMax);
	float tNearZ = std::min(tZMin, tZMax);
	float tFarZ = std::max(tZMin, tZMax);

	//AABBとの衝突点(貫通点)のtが小さい方
	float tmin = std::max(std::max(tNearX, tNearY), tNearZ);
	//AABBとの衝突点(貫通点)のtが大きい方
	float tmax = std::min(std::min(tFarX, tFarY), tFarZ);
	if (shape.GetShapeType() == ShapeType::SEGMENT) {
		if (tmax < 0.f || tmin > 1.f) {
			return false;
		}
	}
	if (tmin <= tmax) {
		return true;
	}
	return false;
}

bool CheckCollisionSphereOBB(const OBB& obb, const Sphere& sphere) {
	Matrix4x4 obbWorldMatrix = MakeWorldOBB(obb);
	Matrix4x4 obbWorldMatrixInverse = Inverse(obbWorldMatrix);
	Vector3 centerInOBBLocalSpace = Transform(sphere.GetPos(), obbWorldMatrixInverse);

	AABB aabbOBBLocal{-obb.size.x, -obb.size.y, - obb.size.z,
					   obb.size.x,  obb.size.y,   obb.size.z };
	Sphere* sphereOBBLocal = new Sphere();
	sphereOBBLocal->SetPos(centerInOBBLocalSpace);
	sphereOBBLocal->SetRadius(sphere.GetRadius());

	bool result = CheckCollisionSphereAABB(aabbOBBLocal, *sphereOBBLocal);
	delete sphereOBBLocal;;

	return result;
}

bool CheckCollisionShapeOBB(const OBB& obb, const Shape& shape) {
	Matrix4x4 obbWorldMatrix = MakeWorldOBB(obb);
	Matrix4x4 obbWorldMatrixInverse = Inverse(obbWorldMatrix);
	Vector3 localOrigin = Transform(shape.GetOrigin(), obbWorldMatrixInverse);
	Vector3 localEnd = Transform(shape.GetOrigin() + shape.GetDiff(), obbWorldMatrixInverse);

	AABB aabbOBBLocal{ -obb.size.x, -obb.size.y, -obb.size.z,
					   obb.size.x,  obb.size.y,   obb.size.z };

	Shape* localShape = nullptr;
	if (shape.GetShapeType() == ShapeType::SEGMENT) {
		localShape = new Segment();
	} else if (shape.GetShapeType() == ShapeType::RAY) {
		localShape = new Ray();
	} else {
		localShape = new Line();
	}
	
	localShape->SetOrigin(localOrigin);
	localShape->SetDiff(localEnd - localOrigin);
	
	bool result = CheckCollisionShapeAABB(aabbOBBLocal, *localShape);
	delete localShape;
	return result;
}

bool CheckCollisionOBB(const OBB& obb1, const OBB& obb2) {
	Vector3 axes[15];

	// 各OBBの座標軸を分離軸として追加
	for (int i = 0; i < 3; ++i) {
		axes[i] = obb1.orientations[i];
		axes[i + 3] = obb2.orientations[i];
	}

	// 各座標軸の外積を分離軸として追加
	int index = 6;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			axes[index++] = Cross(obb1.orientations[i], obb2.orientations[j]);
		}
	}

	// すべての分離軸で投影のチェック
	for (int i = 0; i < 15; ++i) {
		if (!OverlapOnAxis(obb1, obb2, axes[i])) {
			return false; // 分離軸がある場合は衝突していない
		}
	}

	return true; // すべての軸で区間が重なっていれば衝突

}

bool CheckCollisionOBBAABB(const OBB& obb, const AABB& aabb) {
	OBB obb2 = AABB2OBB(aabb);
	return CheckCollisionOBB(obb, obb2);
}

OBB AABB2OBB(AABB aabb) {
	OBB result{};
	result.center = (aabb.max + aabb.min) / 2.f;

	result.size = (aabb.max - aabb.min) / 2.f;

	Vector3 rotate = { 0.f,0.f,0.f };
	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotate);

	result.orientations[0] = { rotateMatrix.m[0][0], rotateMatrix.m[0][1] ,rotateMatrix.m[0][2] };
	result.orientations[1] = { rotateMatrix.m[1][0], rotateMatrix.m[1][1] ,rotateMatrix.m[1][2] };
	result.orientations[2] = { rotateMatrix.m[2][0], rotateMatrix.m[2][1] ,rotateMatrix.m[2][2] };

	return result;
}

bool OverlapOnAxis(const OBB& obb1, const OBB& obb2, const Vector3& axis) {
	// 軸の正規化 (長さがゼロに近い場合は衝突しない)
	if (LengthSquared(axis) < 1e-6f) { 
		return true;
	}

	// OBBの8頂点を計算
	Vector3 corners1[8], corners2[8];
	ComputeOBBCorners(obb1, corners1);
	ComputeOBBCorners(obb2, corners2);

	// 各OBBの頂点を分離軸に投影して最小値・最大値を求める
	float min1 = FLT_MAX, max1 = -FLT_MAX;
	float min2 = FLT_MAX, max2 = -FLT_MAX;

	for (int i = 0; i < 8; ++i) {
		float projection1 = Dot(corners1[i], axis);
		float projection2 = Dot(corners2[i], axis);

		min1 = std::min(min1, projection1);
		max1 = std::max(max1, projection1);

		min2 = std::min(min2, projection2);
		max2 = std::max(max2, projection2);
	}

	// 投影範囲が重なっていない場合、OBBは衝突していない
	return !(max1 < min2 || max2 < min1);
}

void ComputeOBBCorners(const OBB& obb, Vector3 corners[8]) {
	Vector3 xAxis = obb.orientations[0] * obb.size.x;
	Vector3 yAxis = obb.orientations[1] * obb.size.y;
	Vector3 zAxis = obb.orientations[2] * obb.size.z;

	corners[0] = obb.center + xAxis + yAxis + zAxis;
	corners[1] = obb.center + xAxis + yAxis - zAxis;
	corners[2] = obb.center + xAxis - yAxis + zAxis;
	corners[3] = obb.center + xAxis - yAxis - zAxis;
	corners[4] = obb.center - xAxis + yAxis + zAxis;
	corners[5] = obb.center - xAxis + yAxis - zAxis;
	corners[6] = obb.center - xAxis - yAxis + zAxis;
	corners[7] = obb.center - xAxis - yAxis - zAxis;
}
