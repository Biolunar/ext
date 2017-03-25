#include "ext/wayland.hpp"

#include <cerrno>

#include <string>

namespace
{

	class ErrorCategory :
		public ::std::error_category
	{
	public:
		char const* name() const noexcept override { return u8"wayland"; }
		::std::string message(int const condition) const override
		{
			::ext::wl::Error err = static_cast<::ext::wl::Error>(condition);
			switch (err)
			{
				case ::ext::wl::Error::Success: return u8"Success";
				case ::ext::wl::Error::Wayland: return u8"Wayland";
				case ::ext::wl::Error::System: return u8"System: " + ::std::system_category().message(errno);
			}
		}
	};

} // namespace

namespace ext
{

	namespace wl
	{

		::std::error_category const& error_category()
		{
			static ::ErrorCategory cat;
			return cat;
		}

	} // namespace wl

} // namespace ext
