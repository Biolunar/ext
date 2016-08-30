#include <ext/memory_map.hpp>

#include <system_error>

namespace ext
{

MemoryMap::MemoryMap() noexcept :
	MemoryMap(MAP_FAILED, 0)
{
}

MemoryMap::MemoryMap(void* const handle, size_t const length) noexcept :
	m_address{handle},
	m_length{length}
{
}

MemoryMap::MemoryMap(void* const addr, size_t const length, int const prot, int const flags, int const fd, off_t const offset) :
	MemoryMap()
{
	map(addr, length, prot, flags, fd, offset);
}

MemoryMap::~MemoryMap() noexcept
{
	try
	{
		unmap();
	}
	catch (...)
	{
	}
}

void MemoryMap::map(void* const addr, size_t const length, int const prot, int const flags, int const fd, off_t const offset)
{
	unmap();

	m_address = ::mmap(addr, length, prot, flags, fd, offset);
	if (m_address == MAP_FAILED)
		throw ::std::system_error{errno, ::std::system_category(), u8"mmap"};
	m_length = length;
}

void MemoryMap::unmap()
{
	if (m_address != MAP_FAILED)
	{
		int const ret = ::munmap(m_address, m_length);
		if (ret == -1)
			throw ::std::system_error{errno, ::std::system_category(), u8"munmap"};
		m_address = MAP_FAILED;
	}
}

} // namespace ext
