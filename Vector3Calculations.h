#pragma once
#include "Vector3.h"
#include <math.h>
#include <cassert>
#include <Novice.h>
#include <Matrix4x4.h>

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
Vector3 Cross(const Vector3& v1, const Vector3& v2);

/// <summary>
/// ベクトルの長さ
/// </summary>
/// <param name="vector3"></param>
/// <returns></returns>
float Length(Vector3 vector3);

/// <summary>
/// ベクトルの長さの2乗
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
float LengthSquared(const Vector3& v);

/// <summary>
/// ベクトルの正規化
/// </summary>
/// <param name="vector3"></param>
/// <returns></returns>
Vector3 Normalize(const Vector3& vector3);

/// <summary>
/// ベクトルを画面に表示
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="vector"></param>
/// <param name="label"></param>
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);


/// <summary>
/// 正射影ベクトル(v1をv2に投影)
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Project(const Vector3& v1, const Vector3& v2);

Vector3 TransforNormal(const Vector3& vector, const Matrix4x4& matrix);

Vector3 Perpendicular(const Vector3& vector);

/// <summary>
/// 反射ベクトルを求める関数
/// </summary>
/// <param name="input"></param>
/// <param name="normal"></param>
/// <returns></returns>
Vector3 Reflect(const Vector3& input, const Vector3& normal);
