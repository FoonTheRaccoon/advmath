/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Vec2.h																				  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once

template <typename T>
class _Vec2
{
public:
	_Vec2()
	{}
	_Vec2( T x,T y )
		:
		x( x ),
		y( y )
	{}
	_Vec2( const _Vec2& vect )
		:
		_Vec2( vect.x,vect.y )
	{}
	template <typename T2>
	explicit operator _Vec2<T2>() const
	{
		return{ (T2)x,(T2)y };
	}
	T		LenSq() const
	{
		return (x * x + y * y);
	}
	T		Len() const
	{
		return sqrt( LenSq() );
	}
	T		DistFromOtherVec2(const _Vec2& other) const
	{
		T tmp_x = x - other.x;
		T tmp_y = y - other.y;
		return sqrt(tmp_x * tmp_x + tmp_y * tmp_y);
	}
	_Vec2&	Normalize()
	{
		const T length = Len();
		x /= length;
		y /= length;
		return *this;
	}
	_Vec2	GetNormalized() const
	{
		_Vec2 norm = *this;
		norm.Normalize();
		return norm;
	}
	_Vec2&	Rotate(T theta)
	{
		const T x_tmp = x;
		const T costheta = cos(theta);
		const T sintheta = sin(theta);

		x = x * costheta - y * sintheta;
		y = y * costheta + x_tmp * sintheta; 

		return *this;
	}
	_Vec2&	Rotate(T costheta, T sintheta)
	{
		const T x_tmp = x;

		x = x * costheta - y * sintheta;
		y = y * costheta + x_tmp * sintheta;

		return *this;
	}
	_Vec2	GetRotated(T theta) const
	{
		return _Vec2(*this).Rotate(theta);
	}
	_Vec2	GetRotated(T costheta, T sintheta) const
	{
		return _Vec2(*this).Rotate(costheta, sintheta);
	}
	_Vec2	operator-() const
	{
		return _Vec2( -x,-y );
	}
	_Vec2&	operator=( const _Vec2 &rhs )
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	_Vec2&	operator+=( const _Vec2 &rhs )
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	_Vec2&	operator-=( const _Vec2 &rhs )
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	_Vec2	operator+( const _Vec2 &rhs ) const
	{
		return _Vec2( *this ) += rhs;
	}
	_Vec2	operator-( const _Vec2 &rhs ) const
	{
		return _Vec2( *this ) -= rhs;
	}
	_Vec2&	operator*=( const T &rhs )
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	_Vec2	operator*( const T &rhs ) const
	{
		return _Vec2( *this ) *= rhs;
	}
	T operator*(const _Vec2& rhs) const
	{
		return (x * rhs.x + y * rhs.y);
	}
	_Vec2&	operator/=( const T &rhs )
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}
	_Vec2	operator/( const T &rhs ) const
	{
		return _Vec2( *this ) /= rhs;
	}
	void SwapXY()
	{
		std::swap(x,y);
	}
	void MakeInverseVec()
	{
		SwapXY();
		x *= (T)-1;
	}
	bool	operator==( const _Vec2 &rhs ) const
	{
		return x == rhs.x && y == rhs.y;
	}
	bool	operator!=( const _Vec2 &rhs ) const
	{
		return !(*this == rhs);
	}

public:
	T x;
	T y;
};

typedef _Vec2<float> Vec2;
typedef _Vec2<double> Ved2;
typedef _Vec2<int> Vei2;