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

#ifndef HEADER_EXT_MEMORY_MAP_HPP_INCLUDED
#define HEADER_EXT_MEMORY_MAP_HPP_INCLUDED

#include "handle.hpp"

#include <cassert>
#include <cerrno>

#include <utility>
#include <system_error>

#include <sys/mman.h>

namespace ext
{

namespace detail
{

using MmapPair = ::std::pair<void*, size_t>;

} // namespace detail

template<>
struct HandleTraits<detail::MmapPair>
{
	using RawHandle = detail::MmapPair;
	static RawHandle const& invalid() noexcept { static RawHandle const handle = ::std::make_pair(MAP_FAILED, 0); return handle; }
	static void destroy(RawHandle const& handle) noexcept { ::munmap(handle.first, handle.second); }
};

class MemoryMap :
	public Handle<HandleTraits<detail::MmapPair>>
{
public:
	using Handle::Handle; // import ctors

	void map(void* addr, size_t length, int prot, int flags, int fd, off_t offset)
	{
		assert(raw_handle() == Traits::invalid());

		m_raw_handle = ::std::make_pair(::mmap(addr, length, prot, flags, fd, offset), length);
		if (m_raw_handle.first == MAP_FAILED)
			throw ::std::system_error{errno, ::std::system_category(), u8"mmap"};
	}

	void unmap()
	{
		assert(raw_handle() != Traits::invalid());

		int const ret = ::munmap(m_raw_handle.first, m_raw_handle.second);
		if (ret == -1)
			throw ::std::system_error{errno, ::std::system_category(), u8"munmap"};
		m_raw_handle = Traits::invalid();
	}
};

using MemoryMapPtr = HandlePtr<MemoryMap>;

} // namespace ext

#endif // HEADER_EXT_MEMORY_MAP_HPP_INCLUDED
