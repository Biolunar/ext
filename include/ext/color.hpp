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

#ifndef HEADER_EXT_COLOR_HPP_INCLUDED
#define HEADER_EXT_COLOR_HPP_INCLUDED


#include <cmath>

#include <boost/operators.hpp>


namespace ext
{


template <typename T>
class color :
	boost::multipliable<color<T>>
{
public:
	using type = T;

	type r;
	type g;
	type b;
	type a;

	color() : r{0}, g{0}, b{0}, a{0} {}
	color(type red, type green, type blue, type alpha) : r{red}, g{green}, b{blue}, a{alpha} {}
	template <typename U>
	color(color<U> const& c) : r{c.r}, g{c.g}, b{c.b}, a{c.a} {}
};


using colorf = color<float>;
using colord = color<double>;
using colorld = color<long double>;


template <typename T>
color<T>& operator*=(color<T>& c1, color<T> const& c2)
{
	c1.r *= c2.r;
	c1.g *= c2.g;
	c1.b *= c2.b;
	c1.a *= c2.a;
	return c1;
}


} // namespace ext


#endif // HEADER_EXT_COLOR_HPP_INCLUDED
