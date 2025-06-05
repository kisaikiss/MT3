#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "stdint.h"

void DrawSphere(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Vector3& position, const float& radius, const uint32_t& color);

void DrawSphere(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Matrix4x4& worldMatrix, const float& radius, const uint32_t& color);

void DrawLine3D(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Vector3& stratPosition, const Vector3& endPosition, const uint32_t& color);