#pragma once
#include "Vector3.h"

struct AABB {
	Vector3 min; // AABBの最小点
	Vector3 max; // AABBの最大点
};