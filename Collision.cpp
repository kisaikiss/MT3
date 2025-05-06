#include "Collision.h"
#include <Vector3Calculations.h>

Vector3 ClosestPoint(const Point& point, const Shape& shape) {
	// 点と線分の最近接点を求める
	Vector3 result{};
	Vector3 diff = point.GetPos() - shape.GetOrigin();
	Vector3 project = Project(diff, shape.GetDiff());

	if (shape.GetShapeType() == ShapeType::SEGMENT) {
		// 線分の長さを超えた場合は、線分の端点を返す
		if (Length(project) > Length(shape.GetDiff())) {
			result = shape.GetOrigin() + Normalize(shape.GetDiff()) * Length(shape.GetDiff());
		} else if (Length(shape.GetOrigin()  - project) < Length(shape.GetOrigin())) {
			result = shape.GetOrigin();
		} else {
			result = shape.GetOrigin() + project;
		}
	} else if (shape.GetShapeType() == ShapeType::RAY) {
		if (Length(shape.GetOrigin() - project) < Length(shape.GetOrigin())) {
			result = shape.GetOrigin();
		} else {
			result = shape.GetOrigin() + project;
		}
	} else if (shape.GetShapeType() == ShapeType::LINE) {
		result = shape.GetOrigin() + project;
	} 

	return result;
}
