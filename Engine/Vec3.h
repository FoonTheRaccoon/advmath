#pragma once
#include "Vec2.h"

template <typename T>
class _Vec3
{
public:
	_Vec3()
	{}
	_Vec3(T x, T y)
		:
		x(x),
		y(y)
	{}
	_Vec3(const _Vec3& vect)
		:
		_Vec3(vect.x, vect.y)
	{}
	explicit _Vec3(const _Vec2<T>& v2)
		:
		_Vec3(v2.x, v2.y)
	{}
	explicit operator _Vec2<T>() const
	{
		return {x,y};
	}
	template <typename T2>
	explicit operator _Vec3<T2>() const
	{
		return{ (T2)x,(T2)y };
	}
	T		LenSq() const
	{
		return (x * x + y * y);
	}
	T		Len() const
	{
		return sqrt(LenSq());
	}
	T		DistFromOtherVec3(const _Vec3& other) const
	{
		T tmp_x = x - other.x;
		T tmp_y = y - other.y;
		return sqrt(tmp_x * tmp_x + tmp_y * tmp_y);
	}
	_Vec3& Normalize()
	{
		const T length = Len();
		x /= length;
		y /= length;
		return *this;
	}
	_Vec3	GetNormalized() const
	{
		_Vec3 norm = *this;
		norm.Normalize();
		return norm;
	}
	_Vec3& Rotate(T theta)
	{
		const T x_tmp = x;
		const T costheta = cos(theta);
		const T sintheta = sin(theta);

		x = x * costheta - y * sintheta;
		y = y * costheta + x_tmp * sintheta;

		return *this;
	}
	_Vec3& Rotate(T costheta, T sintheta)
	{
		const T x_tmp = x;

		x = x * costheta - y * sintheta;
		y = y * costheta + x_tmp * sintheta;

		return *this;
	}
	_Vec3	GetRotated(T theta) const
	{
		return _Vec3(*this).Rotate(theta);
	}
	_Vec3	GetRotated(T costheta, T sintheta) const
	{
		return _Vec3(*this).Rotate(costheta, sintheta);
	}
	_Vec3	operator-() const
	{
		return _Vec3(-x, -y);
	}
	_Vec3& operator=(const _Vec3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		w = rhs.w;
		return *this;
	}
	_Vec3& operator+=(const _Vec3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	_Vec3& operator-=(const _Vec3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	_Vec3	operator+(const _Vec3& rhs) const
	{
		return _Vec3(*this) += rhs;
	}
	_Vec3	operator-(const _Vec3& rhs) const
	{
		return _Vec3(*this) -= rhs;
	}
	_Vec3& operator*=(const T& rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	_Vec3	operator*(const T& rhs) const
	{
		return _Vec3(*this) *= rhs;
	}
	T operator*(const _Vec3& rhs) const
	{
		return (x * rhs.x + y * rhs.y);
	}
	_Vec3& operator/=(const T& rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}
	_Vec3	operator/(const T& rhs) const
	{
		return _Vec3(*this) /= rhs;
	}
	void SwapXY()
	{
		std::swap(x, y);
	}
	void MakeInverseVec()
	{
		SwapXY();
		x *= (T)-1;
	}
	bool	operator==(const _Vec3& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	bool	operator!=(const _Vec3& rhs) const
	{
		return !(*this == rhs);
	}

public:
	T x;
	T y;
	T w = (T)1;
};

typedef _Vec3<float> Vec3;
typedef _Vec3<double> Ved3;
typedef _Vec3<int> Vei3;