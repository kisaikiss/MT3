#include "Quaternion.h"
#include "QuaternionCalculations.h"

Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
    return Multiply(q1, q2);
}
