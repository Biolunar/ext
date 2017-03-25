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

#ifndef HEADER_EXT_MATRIX2_HPP_INCLUDED
#define HEADER_EXT_MATRIX2_HPP_INCLUDED

#include "vector2.hpp"

#include <cassert>

#include <algorithm>

#include <boost/operators.hpp>

namespace ext
{

	template <typename T>
	class Matrix2 :
		boost::equality_comparable<Matrix2<T>,
		boost::ring_operators<Matrix2<T>,
		boost::multipliable<Matrix2<T>, T
		>>>
	{
	public:
		using Type = T;

		Type x[4];
	};

	using Matrix2f = Matrix2<float>;
	using Matrix2d = Matrix2<double>;
	using Matrix2ld = Matrix2<long double>;

	template <typename T>
	bool operator==(Matrix2<T> const& m1, Matrix2<T> const& m2)
	{
		return std::equal(m1.x, m1.x + (sizeof m1.x / sizeof m1.x[0]), m2.x);
	}

	template <typename T>
	Matrix2<T>& operator+=(Matrix2<T>& m1, Matrix2<T> const& m2)
	{
		std::transform(m1.x, m1.x + (sizeof m1.x / sizeof m1.x[0]), m2.x, m1.x, [](T one, T two){ return one + two; });
		return m1;
	}

	template <typename T>
	Matrix2<T>& operator-=(Matrix2<T>& m1, Matrix2<T> const& m2)
	{
		std::transform(m1.x, m1.x + (sizeof m1.x / sizeof m1.x[0]), m2.x, m1.x, [](T one, T two){ return one - two; });
		return m1;
	}

	template <typename T>
	Matrix2<T>& operator*=(Matrix2<T>& m1, Matrix2<T> const& m2)
	{
		auto const m = m1;
		m1.x[0] = m.x[0] * m2.x[0] + m.x[1] * m2.x[2];
		m1.x[1] = m.x[0] * m2.x[1] + m.x[1] * m2.x[3];
		m1.x[2] = m.x[2] * m2.x[0] + m.x[3] * m2.x[2];
		m1.x[3] = m.x[2] * m2.x[1] + m.x[3] * m2.x[3];
		return m1;
	}

	template <typename T>
	Matrix2<T>& operator*=(Matrix2<T>& m, T const a)
	{
		std::transform(m.x, m.x + (sizeof m.x / sizeof m.x[0]), m.x, [a](T x){ return x * a; });
		return m;
	}

	template <typename T>
	Vector2<T> operator * (Matrix2<T> const& m, Vector2<T> const& v)
	{
		return {m.x[0] * v.x + m.x[1] * v.y, m.x[2] * v.x + m.x[3] * v.y};
	}

	template <typename T>
	Vector2<T> operator * (Vector2<T> const& v, Matrix2<T> const& m)
	{
		return {v.x * m.x[0] + v.y * m.x[2], v.x * m.x[1] + v.y * m.x[3]};
	}

	template <typename T>
	Matrix2<T> transpose(Matrix2<T> const& m)
	{
		auto t = m;
		t.x[1] = m.x[2];
		t.x[2] = m.x[1];
		return t;
	}

	template <typename T>
	T trace(Matrix2<T> const& m)
	{
		return m.x[0] + m.x[3];
	}

	template <typename T>
	T determinant(Matrix2<T> const& m)
	{
		return m.x[0] * m.x[3] - m.x[1] * m.x[2];
	}

	template <typename T>
	Matrix2<T> inverse(Matrix2<T> const& m)
	{
		assert(determinant(m) != 0);
		Matrix2<T> n;
		n.x[0] = m.x[3];
		n.x[1] = -m.x[1];
		n.x[2] = -m.x[2];
		n.x[3] = m.x[0];
		n *= 1/determinant(m);
		return n;
	}

} // namespace ext

#endif // !HEADER_EXT_MATRIX2_HPP_INCLUDED
