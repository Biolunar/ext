/*
 * Copyright 2017 Mahdi Khanalizadeh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HEADER_EXT_VECTOR4_HPP_INCLUDED
#define HEADER_EXT_VECTOR4_HPP_INCLUDED

#include <cmath>

#include <boost/operators.hpp>

namespace ext
{

	template <typename T>
	class Vector4 :
		boost::equality_comparable<Vector4<T>,
		boost::additive<Vector4<T>,
		boost::multiplicative<Vector4<T>, T
		>>>
	{
	public:
		using Type = T;

		Type x;
		Type y;
		Type z;
		Type w;

		Vector4() : x{0}, y{0}, z{0}, w{0} {}
		Vector4(Type x_, Type y_, Type z_, Type w_) : x{x_}, y{y_}, z{z_}, w{w_} {}
		template <typename U>
		Vector4(Vector4<U> const& v) : x{v.x}, y{v.y}, z{v.z}, w{v.w} {}
	};

	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;
	using Vector4ld = Vector4<long double>;

	template <typename T>
	bool operator==(Vector4<T> const& v1, Vector4<T> const& v2)
	{
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
	}

	template <typename T>
	Vector4<T>& operator+=(Vector4<T>& v1, Vector4<T> const& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		v1.z += v2.z;
		v1.w += v2.w;
		return v1;
	}

	template <typename T>
	Vector4<T>& operator-=(Vector4<T>& v1, Vector4<T> const& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		v1.z -= v2.z;
		v1.w -= v2.w;
		return v1;
	}

	template <typename T>
	Vector4<T>& operator*=(Vector4<T>& v, T t)
	{
		v.x *= t;
		v.y *= t;
		v.z *= t;
		v.w *= t;
		return v;
	}

	template <typename T>
	Vector4<T>& operator/=(Vector4<T>& v, T t)
	{
		v.x /= t;
		v.y /= t;
		v.z /= t;
		v.w /= t;
		return v;
	}

	template <typename T>
	Vector4<T> operator+(Vector4<T> const& v)
	{
		return v;
	}

	template <typename T>
	Vector4<T> operator-(Vector4<T> const& v)
	{
		return {-v.x, -v.y, -v.z, -v.w};
	}

	template <typename T>
	T dot(Vector4<T> const& v1, Vector4<T> const& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	template <typename T>
	T norm(Vector4<T> const& v)
	{
		return std::sqrt(dot(v, v));
	}

	template <typename T>
	Vector4<T> normalize(Vector4<T> const& v)
	{
		return v / norm(v);
	}

} // namespace ext

#endif // !HEADER_EXT_VECTOR4_HPP_INCLUDED
