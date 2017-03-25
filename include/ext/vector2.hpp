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

#ifndef HEADER_EXT_VECTOR2_HPP_INCLUDED
#define HEADER_EXT_VECTOR2_HPP_INCLUDED

#include <cmath>

#include <boost/operators.hpp>

namespace ext
{

	template <typename T>
	class Vector2 :
		boost::equality_comparable<Vector2<T>,
		boost::additive<Vector2<T>,
		boost::multiplicative<Vector2<T>, T
		>>>
	{
	public:
		using Type = T;

		Type x;
		Type y;

		Vector2() : x{0}, y{0} {}
		Vector2(Type x_, Type y_) : x{x_}, y{y_} {}
		template <typename U>
		Vector2(Vector2<U> const& v) : x{v.x}, y{v.y} {}
	};

	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2ld = Vector2<long double>;

	template <typename T>
	bool operator==(Vector2<T> const& v1, Vector2<T> const& v2)
	{
		return v1.x == v2.x && v1.y == v2.y;
	}

	template <typename T>
	Vector2<T>& operator+=(Vector2<T>& v1, Vector2<T> const& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		return v1;
	}

	template <typename T>
	Vector2<T>& operator-=(Vector2<T>& v1, Vector2<T> const& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		return v1;
	}

	template <typename T>
	Vector2<T>& operator*=(Vector2<T>& v, T t)
	{
		v.x *= t;
		v.y *= t;
		return v;
	}

	template <typename T>
	Vector2<T>& operator/=(Vector2<T>& v, T t)
	{
		v.x /= t;
		v.y /= t;
		return v;
	}

	template <typename T>
	Vector2<T> operator+(Vector2<T> const& v)
	{
		return v;
	}

	template <typename T>
	Vector2<T> operator-(Vector2<T> const& v)
	{
		return {-v.x, -v.y};
	}

	template <typename T>
	T dot(Vector2<T> const& v1, Vector2<T> const& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	template <typename T>
	T norm(Vector2<T> const& v)
	{
		return std::sqrt(dot(v, v));
	}

	template <typename T>
	Vector2<T> normalize(Vector2<T> const& v)
	{
		return v / norm(v);
	}

} // namespace ext

#endif // !HEADER_EXT_VECTOR2_HPP_INCLUDED
