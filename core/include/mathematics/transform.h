#pragma once
#include "mathematics/matrix.h"


namespace neko::Transform3d
{
Mat4f const TranslationMatrixFrom(const Vec3f translation);
Mat4f const ScalingMatrixFrom(const Vec3f& scale);

Mat4f const RotationMatrixFrom(const degree_t angle, const Vec3f axis);

Mat4f const RotationMatrixFrom(const radian_t angle, const Vec3f axis);


Mat4<float> const RotationMatrixFrom(const EulerAngles cardinalRotation);

Mat4f const RotationMatrixFrom(const Quaternion& quaternion);



Mat4f Translate(const Mat4f& transform, const Vec3f translation);

Mat4f Scale(const Mat4f& transform, const Vec3f scale);

Mat4f Rotate(const Mat4f& transform, const degree_t angle, const Vec3f axis);

Mat4f Rotate(const Mat4f& transform, const radian_t angle, const Vec3f axis);


Mat4f Rotate(const Mat4f& transform, const Quaternion& quaternion);

Mat4f Rotate(const Mat4f& transform, const EulerAngles eulerAngles);


Mat4f Perspective(radian_t fovy, float aspect, float near, float far);
}

namespace neko::Transform2d
{
Mat3f const TranslationMatrixFrom(const Vec2f translation);

Mat3f const ScalingMatrixFrom(const Vec2f scale);

Mat3f const RotationMatrixFrom(float angle);

Mat3f Translate(const Mat3f& transform, const Vec2f translation);

Mat3f Scale(const Mat3f& transform, const Vec2f scale);

Mat3f Rotate(const Mat3f& transform, const float angle);
}