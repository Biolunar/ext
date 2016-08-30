#ifndef HEADER_EXT_FILE_HPP_INCLUDED
#define HEADER_EXT_FILE_HPP_INCLUDED

// TODO: which headers are really required for mode_t and off_t?
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace ext
{

class File
{
public:
	File() noexcept;
	File(int fd) noexcept;
	File(char const* path_name, int flags, mode_t mode);
	File(File const&) = delete;
	~File() noexcept;
	File& operator=(File const&) = delete;

	void open(char const* path_name, int flags, mode_t mode);
	void close();

	int handle() const noexcept { return m_handle; }

	void truncate(off_t length);

private:
	int m_handle;
};

} // namespace ext

#endif // HEADER_EXT_FILE_HPP_INCLUDED
