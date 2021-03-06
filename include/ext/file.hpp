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

#ifndef HEADER_EXT_FILE_HPP_INCLUDED
#define HEADER_EXT_FILE_HPP_INCLUDED

#include "handle.hpp"

#include <cassert>
#include <cerrno>
#include <cstddef>

#include <system_error>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace ext
{

	namespace detail
	{

		struct FileTraits
		{
			using RawHandle = int;
			static RawHandle const& invalid() noexcept { static RawHandle const handle = -1; return handle; }
			static void destroy(RawHandle const& handle) noexcept { ::close(handle); }
		};

	} // namespace detail

	class File :
		public Handle<detail::FileTraits>
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

		::off_t lseek(::off_t const offset, int const whence)
		{
			assert(raw_handle() != Traits::invalid());

			auto const ret = ::lseek(raw_handle(), offset, whence);
			if (ret == static_cast<::off_t>(-1))
				throw ::std::system_error{errno, ::std::system_category(), u8"lseek"};
			return ret;
		}

		::std::size_t read(void* const buffer, ::std::size_t const count)
		{
			assert(raw_handle() != Traits::invalid());

			auto const ret = ::read(raw_handle(), buffer, count);
			if (ret == -1)
				throw ::std::system_error{errno, ::std::system_category(), u8"read"};
			return static_cast<::std::size_t>(ret);
		}

		::std::size_t pread(void* const buffer, ::std::size_t const count, ::off_t const offset)
		{
			assert(raw_handle() != Traits::invalid());

			auto const ret = ::pread(raw_handle(), buffer, count, offset);
			if (ret == -1)
				throw ::std::system_error{errno, ::std::system_category(), u8"pread"};
			return static_cast<::std::size_t>(ret);
		}

		::std::size_t write(void const* const buffer, ::std::size_t const count)
		{
			assert(raw_handle() != Traits::invalid());

			auto const ret = ::write(raw_handle(), buffer, count);
			if (ret == -1)
				throw ::std::system_error{errno, ::std::system_category(), u8"write"};
			return static_cast<::std::size_t>(ret);
		}

		::std::size_t pwrite(void const* const buffer, ::std::size_t const count, ::off_t const offset)
		{
			assert(raw_handle() != Traits::invalid());

			auto const ret = ::pwrite(raw_handle(), buffer, count, offset);
			if (ret == -1)
				throw ::std::system_error{errno, ::std::system_category(), u8"pwrite"};
			return static_cast<::std::size_t>(ret);
		}
	};

	using FilePtr = HandlePtr<File>;

} // namespace ext

#endif // !HEADER_EXT_FILE_HPP_INCLUDED
