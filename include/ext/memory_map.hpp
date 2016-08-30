#ifndef HEADER_EXT_MEMORY_MAP_HPP_INCLUDED
#define HEADER_EXT_MEMORY_MAP_HPP_INCLUDED

#include <sys/mman.h>

namespace ext
{

class MemoryMap
{
public:
	MemoryMap() noexcept;
	MemoryMap(void* handle, size_t length) noexcept;
	MemoryMap(void* addr, size_t length, int prot, int flags, int fd, off_t offset);
	MemoryMap(MemoryMap const&) = delete;
	~MemoryMap() noexcept;
	MemoryMap& operator=(MemoryMap const&) = delete;

	void map(void* addr, size_t length, int prot, int flags, int fd, off_t offset);
	void unmap();

	void* address() const noexcept { return m_address; }

private:
	void* m_address;
	size_t m_length;
};

} // namespace ext

#endif // HEADER_EXT_MEMORY_MAP_HPP_INCLUDED
