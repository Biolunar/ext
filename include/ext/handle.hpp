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

#ifndef HEADER_EXT_HANDLE_HPP_INCLUDED
#define HEADER_EXT_HANDLE_HPP_INCLUDED

#include <cstddef>

#include <utility>
#include <type_traits>

namespace ext
{

template<typename RawHandleType>
struct HandleTraits
{
	using RawHandle = RawHandleType;
	static RawHandle const& invalid() noexcept;
	static void destroy(RawHandle const& handle) noexcept;
};

template<typename HandleTraitsType>
class Handle
{
public:
	using Traits = HandleTraitsType;
	using RawHandle = typename Traits::RawHandle;

	// TODO: Visual Studio 2015 Update 3 does not support u8"" in static_assert
	//static_assert(::std::is_nothrow_copy_assignable<RawHandle>::value, "RawHandle must be nothrow copy assignable"); // does not work in VS for std::pair

	// for default ctor if Traits::invalid() does not move its value && for explicit ctor
	static_assert(::std::is_nothrow_copy_constructible<RawHandle>::value, "RawHandle must be nothrow copy constructible");

	// for dtor
	static_assert(::std::is_nothrow_destructible<RawHandle>::value, "RawHandle must be nothrow destructible");

	// for swap()
	static_assert(::std::is_nothrow_move_constructible<RawHandle>::value, "RawHandle must be nothrow move constructible");
	static_assert(::std::is_nothrow_move_assignable<RawHandle>::value, "RawHandle must be nothrow move assignable");


	Handle() = default;
	Handle(Handle&& rhs) noexcept { swap(*this, rhs); }
	Handle& operator=(Handle rhs) noexcept { swap(*this, rhs); return *this; }
	explicit Handle(RawHandle const& raw_handle) noexcept : m_raw_handle{raw_handle} {}
	~Handle() noexcept
	{
		if (m_raw_handle != Traits::invalid())
			Traits::destroy(m_raw_handle);
	}

	friend void swap(Handle& lhs, Handle& rhs) noexcept
	{
		using ::std::swap; // enable ADL
		swap(lhs.m_raw_handle, rhs.m_raw_handle);
	}

protected:
	RawHandle const& raw_handle() const noexcept { return m_raw_handle; }

	RawHandle m_raw_handle = Traits::invalid();

private:
	template <typename U> friend class HandlePtr;
};

template<typename HandleType>
class HandlePtr final
{
public:
	using Handle = HandleType;
	using Traits = typename Handle::Traits;
	using RawHandle = typename Traits::RawHandle;

	HandlePtr() = default;
	HandlePtr(HandlePtr&&) = default;
	HandlePtr& operator=(HandlePtr&&) = default;
	explicit HandlePtr(RawHandle const& handle) noexcept { reset(handle); }

	// Modifiers
	RawHandle release() noexcept
	{
		auto const old = m_handle.raw_handle();
		m_handle.m_raw_handle = Traits::invalid();
		return old;
	}
	void reset(RawHandle raw_handle = Traits::invalid()) noexcept
	{
		auto const old = m_handle.raw_handle();
		m_handle.m_raw_handle = raw_handle;
		if (old != Traits::invalid())
			Traits::destroy(old);
	}
	friend void swap(HandlePtr& lhs, HandlePtr& rhs) noexcept // TODO: noexcept?
	{
		using ::std::swap;
		swap(lhs.m_handle, rhs.m_handle);
	}

	// Observers
	RawHandle const& get() const noexcept { return m_handle.raw_handle(); }
	explicit operator bool() const noexcept { return m_handle.raw_handle() != Traits::invalid(); }
	RawHandle const& operator*() const noexcept { return get(); }
	Handle const* operator->() const noexcept { return &m_handle; }
	Handle* operator->() noexcept { return &m_handle; }

private:
	Handle m_handle;
};

} // namespace ext

#endif // HEADER_EXT_HANDLE_HPP_INCLUDED
