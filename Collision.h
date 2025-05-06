#pragma once
#include "Shape.h"
#include "Point.h"
#include "Sphere.h"

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