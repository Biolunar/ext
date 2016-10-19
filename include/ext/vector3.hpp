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

#ifndef HEADER_EXT_VECTOR3_HPP_INCLUDED
#define HEADER_EXT_VECTOR3_HPP_INCLUDED


#include <cmath>

#include <boost/operators.hpp>


namespace ext
{


template <typename T>
class vector3 :
	boost::equality_comparable<vector3<T>,
	boost::additive<vector3<T>,
	boost::multiplicative<vector3<T>, T
	>>>
{
public:
	using type = T;

	type x;
	type y;
	type z;

	vector3() : x{0}, y{0}, z{0} {}
	vector3(type x_, type y_, type z_) : x{x_}, y{y_}, z{z_} {}
	template <typename U>
	vector3(vector3<U> const& v) : x{v.x}, y{v.y}, z{v.z} {}
};


using vector3f = vector3<float>;
using vector3d = vector3<double>;
using vector3ld = vector3<long double>;


template <typename T>
bool operator==(vector3<T> const& v1, vector3<T> const& v2)
{
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}


template <typename T>
vector3<T>& operator+=(vector3<T>& v1, vector3<T> const& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}


template <typename T>
vector3<T>& operator-=(vector3<T>& v1, vector3<T> const& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}


template <typename T>
vector3<T>& operator*=(vector3<T>& v, T t)
{
	v.x *= t;
	v.y *= t;
	v.z *= t;
	return v;
}


template <typename T>
vector3<T>& operator/=(vector3<T>& v, T t)
{
	v.x /= t;
	v.y /= t;
	v.z /= t;
	return v;
}


template <typename T>
vector3<T> operator+(vector3<T> const& v)
{
	return v;
}


template <typename T>
vector3<T> operator-(vector3<T> const& v)
{
	return {-v.x, -v.y, -v.z};
}


template <typename T>
T dot(vector3<T> const& v1, vector3<T> const& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


template <typename T>
T norm(vector3<T> const& v)
{
	return std::sqrt(dot(v, v));
}


template <typename T>
vector3<T> normalize(vector3<T> const& v)
{
	return v / norm(v);
}


} // namespace ext


#endif // HEADER_EXT_VECTOR3_HPP_INCLUDED
