#include "Lerp.h"

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result{};
	result = v1 + (v2 - v1) * t;
	return result;
}
