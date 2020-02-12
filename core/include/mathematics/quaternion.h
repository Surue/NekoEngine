#include <engine/entity.h>
#include <mathematics/matrix.h>
#include <engine/component.h>
#include <mathematics/vector.h>
#include <cmath>

namespace neko
{
struct Quaternion
{
	union
	{
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float coord[4];
	};

	Quaternion()
	{
		x = y = z = w = 0;
	}

	explicit Quaternion(float same)
		: x(same), y(same), z(same), w(same)
	{
	}

	Quaternion(float X, float Y, float Z, float W) noexcept
		: x(X), y(Y), z(Z), w(W)
	{
	}


	const float& operator[](size_t p_axis) const
	{
		return coord[p_axis];
	}

	float& operator[](size_t p_axis)
	{

		return coord[p_axis];
	}

	//The dot product between two rotations.
	float Dot(Quaternion a, Quaternion b) const
	{
		return	a.x * b.x +
				a.y * b.y +
				a.z * b.z + 
				a.w * b.w;
	}

	//Converts this quaternion to one with the same orientation but with a magnitude of 1.
	Quaternion Normalize(Quaternion quaternion) const
	{
		return quaternion / Magnitude(quaternion);
	}

	float Magnitude(Quaternion quaternion) const
	{
		return sqrtf(quaternion.x * quaternion.x +
					quaternion.y * quaternion.y +
					quaternion.z * quaternion.z +
					quaternion.w * quaternion.w);
	}

	//Creates a rotation which rotates angle degrees around axis.
	Vec3f AngleAxis(Quaternion quaternion, float angle, Vec3f axis) const
	{

	}


	//Returns the angle in degrees between two rotations a and b.
	float Angle(Quaternion a, Quaternion b) const
	{

	}

	Quaternion Conjugate() const
	{
		return Quaternion(-x, -y, -z, w);
	}

	//Returns the Inverse of rotation.
	Quaternion Quaternion::Inverse() const
	{
		const Quaternion conj = Conjugate();
		const float mag = Magnitude(*this);

		return conj / (mag * mag);
	}


	/*
	Returns a rotation that rotates z degrees around the z axis,
	x degrees around the x axis, and y degrees around the y axis; 
	applied in that order
	*/
	Quaternion Euler(Vec3f angle) const //TODO Change to EulerAngle
	{
		float cy = cos(angle.x * 0.5f);
		float sy = sin(angle.x * 0.5f);
		float cp = cos(angle.y * 0.5f);
		float sp = sin(angle.y * 0.5f);
		float cr = cos(angle.z * 0.5f);
		float sr = sin(angle.z * 0.5f);

		Quaternion q;
		q.w = cy * cp * cr + sy * sp * sr;
		q.x = cy * cp * sr - sy * sp * cr;
		q.y = sy * cp * sr + cy * sp * cr;
		q.z = sy * cp * cr - cy * sp * sr;

		return q;
	}

	//Operators
	Quaternion operator/(Quaternion rhs) const
	{
		return *this * rhs.Inverse();
	}

	Quaternion operator/(const float rhs) const {
		return Quaternion(
			x / rhs,
			y / rhs,
			z / rhs,
			w / rhs);
	}

	Quaternion operator-(const Quaternion& rhs) const
	{
		return Quaternion(
			x - rhs.x,
			y - rhs.y, 
			z - rhs.z, 
			w - rhs.w);
	}

	Quaternion operator+(const Quaternion& rhs) const
	{
		return Quaternion(
			x + rhs.x,
			y + rhs.y,
			z + rhs.z,
			w + rhs.w);
	}

	Quaternion operator*(const Quaternion& rhs) const
	{
		return Quaternion(
			w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
			w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
			w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x,
			w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z);
	}
};
}