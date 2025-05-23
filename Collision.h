#pragma once
#define NOMINMAX
#include "Shape.h"
#include "Point.h"
#include "Sphere.h"
#include "Plane.h"
#include <Triangle.h>
#include "AABB.h"
#include "OBB.h"

/// <summary>
/// 点と線の最近接点を求める関数
/// </summary>
/// <param name="point"></param>
/// <param name="shape"></param>
/// <returns></returns>
Vector3 ClosestPoint(const Point& point, const Shape& shape);

/// <summary>
/// 球と球の当たり判定
/// </summary>
/// <param name="sphere1"></param>
/// <param name="sphere2"></param>
/// <returns></returns>
bool CheckCollisionSpheres(const Sphere& sphere1, const Sphere& sphere2);

/// <summary>
/// 点と平面の距離
/// </summary>
/// <param name="point"></param>
/// <param name="plane"></param>
/// <returns></returns>
float CalculateDistancePointPlane(const Vector3& point, const Plane& plane);

/// <summary>
/// 球と平面の当たり判定
/// </summary>
/// <param name="sphere"></param>
/// <param name="plane"></param>
/// <returns></returns>
bool CheckCollisionPlaneSphere(const Sphere& sphere, const Plane& plane);

/// <summary>
/// 線と平面の当たり判定
/// </summary>
/// <param name="shape"></param>
/// <param name="plane"></param>
/// <returns></returns>
bool CheckCollisionPlaneShape(const Shape& shape, const Plane& plane);


/// <summary>
/// 線と三角形の当たり判定
/// </summary>
/// <param name="shape"></param>
/// <param name="triangle"></param>
/// <returns></returns>
bool CheckCollisionTriangleShape(const Shape& shape, const Triangle& triangle);


/// <summary>
/// AABB同士の当たり判定
/// </summary>
/// <param name="aabb"></param>
/// <param name="aabb2"></param>
/// <returns></returns>
bool CheckCollisionAABB(const AABB& aabb, const AABB& aabb2);


/// <summary>
/// AABBと球の当たり判定
/// </summary>
/// <param name="aabb"></param>
/// <param name="sphere"></param>
/// <returns></returns>
bool CheckCollisionSphereAABB(const AABB& aabb, const Sphere& sphere);

/// <summary>
/// 線とAABBの当たり判定
/// </summary>
/// <param name="aabb"></param>
/// <param name="shape"></param>
/// <returns></returns>
bool CheckCollisionShapeAABB(const AABB& aabb, const Shape& shape);

/// <summary>
/// OBBと球の当たり判定
/// </summary>
/// <param name="obb"></param>
/// <param name="sphere"></param>
/// <returns></returns>
bool CheckCollisionSphereOBB(const OBB& obb, const Sphere& sphere);

/// <summary>
/// 線とOBBの当たり判定
/// </summary>
/// <param name="obb"></param>
/// <param name="shape"></param>
/// <returns></returns>
bool CheckCollisionShapeOBB(const OBB& obb, const Shape& shape);
