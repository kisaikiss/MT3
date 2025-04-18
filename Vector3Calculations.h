#pragma once
#include "Vector3Class.h"
#include <math.h>
#include <cassert>
#include <Novice.h>

/// <summary>
/// ベクトルの内積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Dot(Vector3 v1, Vector3 v2);

/// <summary>
/// ベクトルの外積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Cross(Vector3& v1, Vector3& v2);

/// <summary>
/// ベクトルの長さ
/// </summary>
/// <param name="vector3"></param>
/// <returns></returns>
float Length(Vector3 vector3);

/// <summary>
/// ベクトルの正規化
/// </summary>
/// <param name="vector3"></param>
/// <returns></returns>
Vector3 Normalize(Vector3& vector3);

/// <summary>
/// ベクトルを画面に表示
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="vector"></param>
/// <param name="label"></param>
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

