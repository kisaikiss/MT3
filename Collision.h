#pragma once
#include "Shape.h"
#include "Point.h"
#include "Sphere.h"
#include "Plane.h"

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