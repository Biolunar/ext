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

	static_assert(::std::is_nothrow_copy_constructible<RawHandle>::value, u8"RawHandle must be nothrow copy constructible");
	static_assert(::std::is_nothrow_move_constructible<RawHandle>::value, u8"RawHandle must be nothrow move constructible");
	static_assert(::std::is_nothrow_copy_assignable<RawHandle>::value, u8"RawHandle must be nothrow copy assignable");
	static_assert(::std::is_nothrow_move_assignable<RawHandle>::value, u8"RawHandle must be nothrow move assignable");
	static_assert(::std::is_nothrow_destructible<RawHandle>::value, u8"RawHandle must be nothrow destructible");

	Handle() = default;
	Handle(Handle&& rhs) noexcept { swap(*this, rhs); }
	Handle& operator=(Handle rhs) noexcept { swap(*this, rhs); return *this; }
	explicit Handle(RawHandle const& raw_handle) noexcept : m_raw_handle{raw_handle} {}
	~Handle() noexcept
	{
		if (m_raw_handle != Traits::invalid())
			Traits::destroy(m_raw_handle);
	}

	friend void swap(Handle& lhs, Handle& rhs) noexcept // TODO: noexcept?
	{
		using ::std::swap; // enable ADL
		swap(lhs.m_raw_handle, rhs.m_raw_handle);
	}

	RawHandle const& raw_handle() const noexcept { return m_raw_handle; }

protected:
	RawHandle m_raw_handle = Traits::invalid();

private:
	template <typename U> friend class HandlePtr;
};

template<typename HandleType>
class HandlePtr
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
