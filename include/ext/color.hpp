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

#ifndef HEADER_EXT_COLOR_HPP_INCLUDED
#define HEADER_EXT_COLOR_HPP_INCLUDED

#include <cmath>

#include <boost/operators.hpp>

namespace ext
{

	template <typename T>
	class Color :
		boost::multipliable<Color<T>>
	{
	public:
		using Type = T;

		Type r;
		Type g;
		Type b;
		Type a;

		Color() : r{0}, g{0}, b{0}, a{0} {}
		Color(Type red, Type green, Type blue, Type alpha) : r{red}, g{green}, b{blue}, a{alpha} {}
		template <typename U>
		Color(Color<U> const& c) : r{c.r}, g{c.g}, b{c.b}, a{c.a} {}
	};

	using Colorf = Color<float>;
	using Colord = Color<double>;
	using Colorld = Color<long double>;

	template <typename T>
	Color<T>& operator*=(Color<T>& c1, Color<T> const& c2)
	{
		c1.r *= c2.r;
		c1.g *= c2.g;
		c1.b *= c2.b;
		c1.a *= c2.a;
		return c1;
	}

} // namespace ext

#endif // !HEADER_EXT_COLOR_HPP_INCLUDED
