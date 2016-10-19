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

/*
 * Original work by The Khronos Group Inc. as part of the Vulkan-Hpp project.
 * Licensed under the Apache License 2.0:
 *
 * Copyright (c) 2015-2016 The Khronos Group Inc.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and/or associated documentation files (the
 * "Materials"), to deal in the Materials without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Materials, and to
 * permit persons to whom the Materials are furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Materials.
 * 
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
 */

#ifndef HEADER_EXT_FLAGS_HPP_INCLUDED
#define HEADER_EXT_FLAGS_HPP_INCLUDED

namespace ext
{

template <typename BitType, typename MaskType>
class Flags
{
public:
	Flags() noexcept : m_mask{} {}
	Flags(BitType bit) noexcept : m_mask(static_cast<MaskType>(bit)) {}
	explicit Flags(MaskType mask) noexcept : m_mask(mask) {}
	Flags(Flags<BitType, MaskType> const& rhs) noexcept : m_mask{rhs.m_mask} {}
	Flags<BitType, MaskType>& operator=(Flags<BitType, MaskType> const& rhs) noexcept { m_mask = rhs.m_mask; return *this; }

	Flags<BitType, MaskType>& operator|=(Flags<BitType, MaskType> const& rhs) noexcept
	{
		m_mask |= rhs.m_mask;
		return *this;
	}

	Flags<BitType, MaskType>& operator&=(Flags<BitType, MaskType> const& rhs) noexcept
	{
		m_mask &= rhs.m_mask;
		return *this;
	}

	Flags<BitType, MaskType>& operator^=(Flags<BitType, MaskType> const& rhs) noexcept
	{
		m_mask ^= rhs.m_mask;
		return *this;
	}

	Flags<BitType, MaskType> operator|(Flags<BitType, MaskType> const& rhs) const noexcept
	{
		Flags<BitType, MaskType> result(*this);
		result |= rhs;
		return result;
	}

	Flags<BitType, MaskType> operator&(Flags<BitType, MaskType> const& rhs) const noexcept
	{
		Flags<BitType, MaskType> result(*this);
		result &= rhs;
		return result;
	}

	Flags<BitType, MaskType> operator^(Flags<BitType, MaskType> const& rhs) const noexcept
	{
		Flags<BitType, MaskType> result(*this);
		result ^= rhs;
		return result;
	}

	bool operator!() const noexcept { return !m_mask; }
	bool operator==(Flags<BitType, MaskType> const& rhs) const noexcept { return m_mask == rhs.m_mask; }
	bool operator!=(Flags<BitType, MaskType> const& rhs) const noexcept { return m_mask != rhs.m_mask; }
	explicit operator bool() const noexcept { return !!m_mask; }
	explicit operator MaskType() const noexcept { return m_mask; }

private:
	MaskType  m_mask;
};

template <typename BitType, typename MaskType>
Flags<BitType, MaskType> operator|(BitType bit, Flags<BitType, MaskType> const& flags)
{
	return flags | bit;
}

template <typename BitType, typename MaskType>
Flags<BitType, MaskType> operator&(BitType bit, Flags<BitType, MaskType> const& flags)
{
	return flags & bit;
}

template <typename BitType, typename MaskType>
Flags<BitType, MaskType> operator^(BitType bit, Flags<BitType, MaskType> const& flags)
{
	return flags ^ bit;
}

} // namespace ext

#endif // HEADER_EXT_FLAGS_HPP_INCLUDED
