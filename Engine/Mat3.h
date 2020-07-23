#pragma once
#include "Vec3.h"

template<typename T>
class _Mat3
{
public:
	_Vec2<T> operator* (const _Vec2<T>& v) const
	{
		_Vec2<T> vout;
		
		vout.x = v.x * cells[0][0] + v.y * cells[0][1];
		vout.y = v.x * cells[1][0] + v.y * cells[1][1];

		return vout;
	}
	_Mat3 operator*(const _Mat3& rhs) const
	{
		_Mat3 out;

		for (int row_left = 0; row_left < 2; ++row_left)
		{
			for (int col_right = 0; col_right < 2; ++col_right)
			{
				out.cells[row_left][col_right] = (T)0;
				for (int i = 0; i < 2; ++i)
				{
					out.cells[row_left][col_right] += cells[row_left][i] * rhs.cells[i][col_right];
				}
			}
		}

		return out;
	}
	_Mat3& operator*=(const _Mat3& rhs)
	{
		return *this = *this * rhs);
	}
	static _Mat3 Scale(T factor)
	{
		return {
			factor,	 (T)0,
			 (T)0,	factor
		};
	}
	static _Mat3 Identity()
	{
		return Scale((T)1);
	}
	static _Mat3 FlipY()
	{
		return {
			(T)1, (T)0,
			(T)0, (T)-1
		};
	}
	static _Mat3 Rotate(T angle)
	{
		const T costheta = cos(theta);
		const T sintheta = sin(theta);

		return{
			costheta,  -sintheta,
			sintheta,  costheta
		};
	}
public:
	// [row] [column]
	T cells[3][3];
};

typedef _Mat3<float> Mat3;
typedef _Mat3<double> Mat3_D;
typedef _Mat3<int> Mat3_I;
