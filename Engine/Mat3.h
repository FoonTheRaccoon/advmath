#pragma once
#include "Vec3.h"

template<typename T>
class _Mat3
{
public:
	_Vec2<T> operator*(const _Vec2<T>& v)
	{
		return _Vec2<T>(*this * (_Vec3<T>)v);
	}
	_Vec3<T> operator* (const _Vec3<T>& v) const
	{
		_Vec3<T> vout;
		
		vout.x = v.x * cells[0][0] + v.y * cells[0][1] + v.w * cells[0][2];
		vout.y = v.x * cells[1][0] + v.y * cells[1][1] + v.w * cells[1][2];
		vout.w = v.x * cells[2][0] + v.y * cells[2][1] + v.w * cells[2][2];

		return vout;
	}
	_Mat3 operator*(const _Mat3& rhs) const
	{
		_Mat3 out;

		for (int row_left = 0; row_left < 3; ++row_left)
		{
			for (int col_right = 0; col_right < 3; ++col_right)
			{
				out.cells[row_left][col_right] = (T)0;
				for (int i = 0; i < 3; ++i)
				{
					out.cells[row_left][col_right] += cells[row_left][i] * rhs.cells[i][col_right];
				}
			}
		}

		return out;
	}
	static _Mat3 Identity()
	{
		return Scale((T)1);
	}
	static _Mat3 Scale(T factor)
	{
		return {
			factor,	 (T)0,  (T)0,
			 (T)0,	factor, (T)0,
			 (T)0,   (T)0,  (T)1
		};
	}
	static _Mat3 ScaleIndependent(T x, T y)
	{
		return {
			 x,	  (T)0, (T)0,
			(T)0,  y,   (T)0,
			(T)0, (T)0, (T)1
		};
	}
	static _Mat3 FlipY()
	{
		return {
			(T)1, (T)0,  (T)0,
			(T)0, (T)-1, (T)0,
			(T)0, (T)0,  (T)1
		};
	}
	static _Mat3 Rotate(T angle)
	{
		const T costheta = cos(angle);
		const T sintheta = sin(angle);

		return{
			costheta,  -sintheta, (T)0,
			sintheta,  costheta,  (T)0,
			 (T)0,       (T)0,    (T)1
		};
	}
	static _Mat3 Translation(T x, T y)
	{
		return {
			(T)1, (T)0,   x,
			(T)0, (T)1,   y,
			(T)0, (T)0, (T)1
		};
	}
public:
	// [row] [column]
	T cells[3][3];
};

typedef _Mat3<float> Mat3;
typedef _Mat3<double> Mat3_D;
typedef _Mat3<int> Mat3_I;
