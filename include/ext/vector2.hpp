/*
 * Copyright 2016 Mahdi Khanalizadeh
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
class vector2 :
	boost::equality_comparable<vector2<T>,
	boost::additive<vector2<T>,
	boost::multiplicative<vector2<T>, T
	>>>
{
public:
	using type = T;

	type x;
	type y;

	vector2() : x{0}, y{0} {}
	vector2(type x_, type y_) : x{x_}, y{y_} {}
	template <typename U>
	vector2(vector2<U> const& v) : x{v.x}, y{v.y} {}
};


using vector2f = vector2<float>;
using vector2d = vector2<double>;
using vector2ld = vector2<long double>;


template <typename T>
bool operator==(vector2<T> const& v1, vector2<T> const& v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}


template <typename T>
vector2<T>& operator+=(vector2<T>& v1, vector2<T> const& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}


template <typename T>
vector2<T>& operator-=(vector2<T>& v1, vector2<T> const& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}


template <typename T>
vector2<T>& operator*=(vector2<T>& v, T t)
{
	v.x *= t;
	v.y *= t;
	return v;
}


template <typename T>
vector2<T>& operator/=(vector2<T>& v, T t)
{
	v.x /= t;
	v.y /= t;
	return v;
}


template <typename T>
vector2<T> operator+(vector2<T> const& v)
{
	return v;
}


template <typename T>
vector2<T> operator-(vector2<T> const& v)
{
	return {-v.x, -v.y};
}


template <typename T>
T dot(vector2<T> const& v1, vector2<T> const& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}


template <typename T>
T norm(vector2<T> const& v)
{
	return std::sqrt(dot(v, v));
}


template <typename T>
vector2<T> normalize(vector2<T> const& v)
{
	return v / norm(v);
}


} // namespace ext


#endif // HEADER_EXT_VECTOR2_HPP_INCLUDED
