#include "ext/file.hpp"

#include <system_error>

namespace ext
{

File::File() noexcept :
	File{-1}
{
}

File::File(int const fd) noexcept :
	m_handle{fd}
{
}

File::File(char const* const path_name, int const flags, mode_t const mode) :
	File{}
{
	open(path_name, flags, mode);
}

File::~File() noexcept
{
	try
	{
		close();
	}
	catch (...)
	{
	}
}

void File::open(char const* const path_name, int const flags, mode_t const mode)
{
	close();

	while ((m_handle = ::open(path_name, flags, mode)) == -1)
	{
		if (errno != EINTR)
			throw ::std::system_error{errno, ::std::system_category(), u8"open"};
	}
}

void File::close()
{
	if (m_handle != -1)
	{
		while (::close(m_handle) == -1)
		{
			if (errno != EINTR)
				throw ::std::system_error{errno, ::std::system_category(), u8"close"};
		}
		m_handle = -1;
	}
}

void File::truncate(off_t const length)
{
	while (::ftruncate(m_handle, length) == -1)
	{
		if (errno != EINTR)
			throw ::std::system_error{errno, ::std::system_category(), u8"ftruncate"};
	}
}

} // namespace ext
