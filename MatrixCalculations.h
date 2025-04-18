#pragma once
#include "Matrix4x4.h"
#include "Vector3Class.h"
#include <cmath>
#include <cassert>

/// <summary>
/// 行列の加法
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

/// <summary>
/// 行列の減法
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

/// <summary>
/// 行列の積
/// </summary>
/// <param name="matrix1"></param>
/// <param name="matrix2"></param>
/// <returns></returns>
Matrix4x4 Multiply(Matrix4x4 const& matrix1, Matrix4x4 const& matrix2);

/// <summary>
/// 拡縮行列を作る
/// </summary>
/// <param name="scale"></param>
/// <returns></returns>
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

/// <summary>
/// X軸方向の回転行列を作る
/// </summary>
/// <param name="theta"></param>
/// <returns></returns>
Matrix4x4 MakeRotateXMatrix(float theta);

/// <summary>
/// Y軸方向の回転行列を作る
/// </summary>
/// <param name="theta"></param>
/// <returns></returns>
Matrix4x4 MakeRotateYMatrix(float theta);

/// <summary>
/// Z軸方向の回転行列を作る
/// </summary>
/// <param name="theta"></param>
/// <returns></returns>
Matrix4x4 MakeRotateZMatrix(float theta);


/// <summary>
/// X,Y,Z全て回転する回転行列を作る
/// </summary>
/// <param name="theta"></param>
/// <returns></returns>
Matrix4x4 MakeRotateMatrix(const Vector3& rotate);

/// <summary>
/// 移動行列を作る
/// </summary>
/// <param name="translate"></param>
/// <returns></returns>
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

/// <summary>
/// 3次元アフィン変換行列を生成する
/// </summary>
/// <param name="scale">拡大縮小率</param>
/// <param name="rotate">回転</param>
/// <param name="translate">移動</param>
/// <returns></returns>
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

/// <summary>
/// 座標変換
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

/// <summary>
/// 逆行列
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
Matrix4x4 Inverse(Matrix4x4 matrix);

/// <summary>
/// 転置行列
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
Matrix4x4 Transpose(Matrix4x4 matrix);

/// <summary>
/// 単位行列の作成
/// </summary>
/// <returns></returns>
Matrix4x4 MakeIdentity4x4();

/// <summary>
/// 行列の数値表示
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="matrix"></param>
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);
