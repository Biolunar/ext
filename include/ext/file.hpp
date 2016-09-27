#ifndef HEADER_EXT_FILE_HPP_INCLUDED
#define HEADER_EXT_FILE_HPP_INCLUDED

#include "handle.hpp"

#include <cassert>
#include <cerrno>

#include <system_error>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace ext
{

template<>
struct HandleTraits<int>
{
	using RawHandle = int;
	static RawHandle const& invalid() noexcept { static RawHandle const handle = -1; return handle; }
	static void destroy(RawHandle const& handle) noexcept { ::close(handle); }
};

class File :
	public Handle<HandleTraits<int>>
{
public:
	using Handle::Handle; // import ctors

	void open(char const* const path_name, int const flags, mode_t const mode)
	{
		assert(raw_handle() == Traits::invalid());

		m_raw_handle = ::open(path_name, flags, mode);
		if (raw_handle() == Traits::invalid())
			throw ::std::system_error{errno, ::std::system_category(), u8"open"};
	}

	void close()
	{
		assert(raw_handle() != Traits::invalid());

		auto const ret = ::close(raw_handle());
		if (ret == -1)
			throw ::std::system_error{errno, ::std::system_category(), u8"close"};
		m_raw_handle = Traits::invalid();
	}

	void truncate(off_t const length)
	{
		assert(raw_handle() != Traits::invalid());

		if (::ftruncate(raw_handle(), length) == -1)
			throw ::std::system_error{errno, ::std::system_category(), u8"ftruncate"};
	}
};

using FilePtr = HandlePtr<File>;

} // namespace ext

#endif // HEADER_EXT_FILE_HPP_INCLUDED
