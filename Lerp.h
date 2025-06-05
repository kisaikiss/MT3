#pragma once
#include "Vector3Class.h"

/// <summary>
/// 線形補間(三次元)
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <param name="t"></param>
/// <returns></returns>
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);