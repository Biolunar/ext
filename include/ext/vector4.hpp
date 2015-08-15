#ifndef HEADER_EXT_VECTOR4_HPP_INCLUDED
#define HEADER_EXT_VECTOR4_HPP_INCLUDED


#include <cmath>

#include <boost/operators.hpp>


namespace ext
{


template <typename T>
class vector4 :
	boost::equality_comparable<vector4<T>,
	boost::additive<vector4<T>,
	boost::multiplicative<vector4<T>, T
	>>>
{
public:
	using type = T;

	type x;
	type y;
	type z;
	type w;

	vector4() : x{0}, y{0}, z{0}, w{0} {}
	vector4(type x_, type y_, type z_, type w_) : x{x_}, y{y_}, z{z_}, w{w_} {}
	template <typename U>
	vector4(vector4<U> const& v) : x{v.x}, y{v.y}, z{v.z}, w{v.w} {}
};


using vector4f = vector4<float>;
using vector4d = vector4<double>;
using vector4ld = vector4<long double>;


template <typename T>
bool operator==(vector4<T> const& v1, vector4<T> const& v2)
{
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}


template <typename T>
vector4<T>& operator+=(vector4<T>& v1, vector4<T> const& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	v1.w += v2.w;
	return v1;
}


template <typename T>
vector4<T>& operator-=(vector4<T>& v1, vector4<T> const& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	v1.w -= v2.w;
	return v1;
}


template <typename T>
vector4<T>& operator*=(vector4<T>& v, T t)
{
	v.x *= t;
	v.y *= t;
	v.z *= t;
	v.w *= t;
	return v;
}


template <typename T>
vector4<T>& operator/=(vector4<T>& v, T t)
{
	v.x /= t;
	v.y /= t;
	v.z /= t;
	v.w /= t;
	return v;
}


template <typename T>
vector4<T> operator+(vector4<T> const& v)
{
	return v;
}


template <typename T>
vector4<T> operator-(vector4<T> const& v)
{
	return {-v.x, -v.y, -v.z, -v.w};
}


template <typename T>
T dot(vector4<T> const& v1, vector4<T> const& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}


template <typename T>
T norm(vector4<T> const& v)
{
	return std::sqrt(dot(v, v));
}


template <typename T>
vector4<T> normalize(vector4<T> const& v)
{
	return v / norm(v);
}


} // namespace ext


#endif // HEADER_EXT_VECTOR4_HPP_INCLUDED
