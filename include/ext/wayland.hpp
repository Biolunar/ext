#ifndef HEADER_EXT_WAYLAND_HPP_INCLUDED
#define HEADER_EXT_WAYLAND_HPP_INCLUDED

#include "handle.hpp"
#include "file.hpp"

#include <cassert>
#include <cerrno>
#include <cstdint>

#include <system_error>

#include <wayland-client.h>
#include <poll.h>

namespace ext
{

	namespace wl
	{

		enum class Error
		{
			Success = 0,
			Wayland, // An error without errno.
			System, // An error with errno.
		};

		::std::error_category const& error_category();

		inline ::std::error_code make_error_code(Error err)
		{
			return ::std::error_code{static_cast<int>(err), error_category()};
		}

		inline ::std::error_condition make_error_condition(Error err)
		{
			return ::std::error_condition{static_cast<int>(err), error_category()};
		}

	} // namespace wl

} // namespace ext

namespace std
{

	template<>
	struct is_error_code_enum<::ext::wl::Error> : public true_type {};

} // namespace std

namespace ext
{

	namespace wl
	{

		namespace detail
		{

			struct EventQueueTraits
			{
				using RawHandle = ::wl_event_queue*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_event_queue_destroy(handle); }
			};

			struct DisplayTraits
			{
				using RawHandle = ::wl_display*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_display_disconnect(handle); }
			};

			struct RegistryTraits
			{
				using RawHandle = ::wl_registry*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_registry_destroy(handle); }
			};

			struct CallbackTraits
			{
				using RawHandle = ::wl_callback*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_callback_destroy(handle); }
			};

			struct CompositorTraits
			{
				using RawHandle = ::wl_compositor*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_compositor_destroy(handle); }
			};

			struct ShmPoolTraits
			{
				using RawHandle = ::wl_shm_pool*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_shm_pool_destroy(handle); }
			};

			struct ShmTraits
			{
				using RawHandle = ::wl_shm*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_shm_destroy(handle); }
			};

			struct BufferTraits
			{
				using RawHandle = ::wl_buffer*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_buffer_destroy(handle); }
			};

			struct DataOfferTraits
			{
				using RawHandle = ::wl_data_offer*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_data_offer_destroy(handle); }
			};

			struct DataSourceTraits
			{
				using RawHandle = ::wl_data_source*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_data_source_destroy(handle); }
			};

			struct DataDeviceTraits
			{
				using RawHandle = ::wl_data_device*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_data_device_destroy(handle); }
			};

			struct DataDeviceManagerTraits
			{
				using RawHandle = ::wl_data_device_manager*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_data_device_manager_destroy(handle); }
			};

			struct ShellTraits
			{
				using RawHandle = ::wl_shell*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_shell_destroy(handle); }
			};

			struct ShellSurfaceTraits
			{
				using RawHandle = ::wl_shell_surface*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_shell_surface_destroy(handle); }
			};

			struct SurfaceTraits
			{
				using RawHandle = ::wl_surface*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_surface_destroy(handle); }
			};

			struct SeatTraits
			{
				using RawHandle = ::wl_seat*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_seat_destroy(handle); }
			};

			struct PointerTraits
			{
				using RawHandle = ::wl_pointer*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_pointer_destroy(handle); }
			};

			struct KeyboardTraits
			{
				using RawHandle = ::wl_keyboard*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_keyboard_destroy(handle); }
			};

			struct TouchTraits
			{
				using RawHandle = ::wl_touch*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_touch_destroy(handle); }
			};

			struct OutputTraits
			{
				using RawHandle = ::wl_output*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_output_destroy(handle); }
			};

			struct RegionTraits
			{
				using RawHandle = ::wl_region*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_region_destroy(handle); }
			};

			struct SubcompositorTraits
			{
				using RawHandle = ::wl_subcompositor*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_subcompositor_destroy(handle); }
			};

			struct SubsurfaceTraits
			{
				using RawHandle = ::wl_subsurface*;
				static constexpr RawHandle invalid() { return nullptr; }
				static void destroy(RawHandle handle) { ::wl_subsurface_destroy(handle); }
			};

		} // namespace detail

		// TODO: There needs to be a native way to use EventQueues; for now the only way is to use wl_proxy_set_queue.
		class EventQueue :
			public ::ext::Handle<detail::EventQueueTraits>
		{
		public:
			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_event_queue_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}
		};

		using EventQueuePtr = ::ext::HandlePtr<EventQueue>;

		class Callback :
			public ::ext::Handle<detail::CallbackTraits>
		{
		public:
			void add_listener(::wl_callback_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_callback_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_callback_add_listener"};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_callback_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}
		};

		using CallbackPtr = ::ext::HandlePtr<Callback>;

		class Registry :
			public ::ext::Handle<detail::RegistryTraits>
		{
		public:
			void add_listener(::wl_registry_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_registry_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_registry_add_listener"};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_registry_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void* bind(::std::uint32_t const name, ::wl_interface const* const interface, ::std::uint32_t const version)
			{
				assert(raw_handle() != Traits::invalid());

				return ::wl_registry_bind(raw_handle(), name, interface, version);
			}
		};

		using RegistryPtr = ::ext::HandlePtr<Registry>;

		class Display :
			public ::ext::Handle<detail::DisplayTraits>
		{
		public:
			void connect(char const* const name = nullptr)
			{
				assert(raw_handle() == Traits::invalid());

				m_raw_handle = ::wl_display_connect(name);
				if (raw_handle() == Traits::invalid())
					throw ::std::system_error{Error::Wayland, u8"wl_display_connect"};
			}
			
			void connect(FilePtr fd)
			{
				assert(raw_handle() == Traits::invalid());

				m_raw_handle = ::wl_display_connect_to_fd(fd.release());
				if (raw_handle() == Traits::invalid())
					throw ::std::system_error{Error::Wayland, u8"wl_display_connect_to_fd"};
			}

			void disconnect()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_display_disconnect(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			int get_fd()
			{
				assert(raw_handle() != Traits::invalid());

				return ::wl_display_get_fd(raw_handle());
			}

			int dispatch()
			{
				assert(raw_handle() != Traits::invalid());

				int const ret = ::wl_display_dispatch(raw_handle());
				if (ret == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_display_dispatch"};
				return ret;
			}

			int dispatch_queue(::wl_event_queue* const queue)
			{
				assert(raw_handle() != Traits::invalid());

				int const ret = ::wl_display_dispatch_queue(raw_handle(), queue);
				if (ret == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_display_dispatch_queue"};
				return ret;
			}

			int dispatch_queue_pending(::wl_event_queue* const queue)
			{
				assert(raw_handle() != Traits::invalid());

				int const ret = ::wl_display_dispatch_queue_pending(raw_handle(), queue);
				if (ret == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_display_dispatch_queue_pending"};
				return ret;
			}

			int dispatch_pending()
			{
				assert(raw_handle() != Traits::invalid());

				int const ret = ::wl_display_dispatch_pending(raw_handle());
				if (ret == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_display_dispatch_pending"};
				return ret;
			}

			int get_error()
			{
				assert(raw_handle() != Traits::invalid());

				return ::wl_display_get_error(raw_handle());
			}

			::std::uint32_t get_protocol_error(::wl_interface const** const interface, ::std::uint32_t* const id)
			{
				assert(raw_handle() != Traits::invalid());

				return ::wl_display_get_protocol_error(raw_handle(), interface, id);
			}

			int flush()
			{
				assert(raw_handle() != Traits::invalid());

				int const ret = ::wl_display_flush(raw_handle());
				if (ret == -1 && errno != EAGAIN)
					throw ::std::system_error{Error::Wayland, u8"wl_display_flush"};
				return ret;
			}

			int roundtrip_queue(::wl_event_queue* const queue)
			{
				assert(raw_handle() != Traits::invalid());

				int const ret = ::wl_display_roundtrip_queue(raw_handle(), queue);
				if (ret == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_display_roundtrip_queue"};
				return ret;
			}

			int roundtrip()
			{
				assert(raw_handle() != Traits::invalid());

				int const ret = ::wl_display_roundtrip(raw_handle());
				if (ret == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_display_roundtrip"};
				return ret;
			}

			EventQueuePtr create_queue()
			{
				assert(raw_handle() != Traits::invalid());

				return EventQueuePtr{::wl_display_create_queue(raw_handle())};
			}

			bool prepare_read_queue(::wl_event_queue* const queue)
			{
				assert(raw_handle() != Traits::invalid());

				return ::wl_display_prepare_read_queue(raw_handle(), queue) == 0 ? true : false;
			}

			bool prepare_read()
			{
				assert(raw_handle() != Traits::invalid());

				return ::wl_display_prepare_read(raw_handle()) == 0 ? true : false;
			}

			void cancel_read()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_display_cancel_read(raw_handle());
			}

			void read_events()
			{
				assert(raw_handle() != Traits::invalid());

				int const ret = ::wl_display_read_events(raw_handle());
				if (ret == -1)
					throw ::std::system_error{Error::System, u8"wl_display_read_events"};
			}

			CallbackPtr sync()
			{
				assert(raw_handle() != Traits::invalid());

				return CallbackPtr{::wl_display_sync(raw_handle())};
			}

			RegistryPtr get_registry()
			{
				assert(raw_handle() != Traits::invalid());

				return RegistryPtr{::wl_display_get_registry(raw_handle())};
			}
		};

		using DisplayPtr = ::ext::HandlePtr<Display>;

		class Surface :
			public ::ext::Handle<detail::SurfaceTraits>
		{
		public:
			void add_listener(::wl_surface_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_surface_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_surface_add_listener"};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_surface_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void attach(::wl_buffer* const buffer, ::std::int32_t const x, ::std::int32_t const y)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_surface_attach(raw_handle(), buffer, x, y);
			}

			void damage(::std::int32_t const x, ::std::int32_t const y, ::std::int32_t const width, ::std::int32_t const height)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_surface_damage(raw_handle(), x, y, width, height);
			}

			CallbackPtr frame()
			{
				assert(raw_handle() != Traits::invalid());

				return CallbackPtr{::wl_surface_frame(raw_handle())};
			}

			void set_opaque_region(::wl_region* const region)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_surface_set_opaque_region(raw_handle(), region);
			}

			void set_input_region(::wl_region* const region)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_surface_set_input_region(raw_handle(), region);
			}

			void commit()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_surface_commit(raw_handle());
			}

			void set_buffer_transform(::std::int32_t const transform)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_surface_set_buffer_transform(raw_handle(), transform);
			}

			void set_buffer_scale(::std::int32_t const scale)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_surface_set_buffer_scale(raw_handle(), scale);
			}

			void damage_buffer(::std::int32_t const x, ::std::int32_t const y, ::std::int32_t const width, ::std::int32_t const height)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_surface_damage_buffer(raw_handle(), x, y, width, height);
			}
		};

		using SurfacePtr = ::ext::HandlePtr<Surface>;

		class Region :
			public ::ext::Handle<detail::RegionTraits>
		{
		public:
			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_region_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void add(::std::int32_t const x, ::std::int32_t const y, ::std::int32_t const width, ::std::int32_t const height)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_region_add(raw_handle(), x, y, width, height);
			}

			void subtract(::std::int32_t const x, ::std::int32_t const y, ::std::int32_t const width, ::std::int32_t const height)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_region_subtract(raw_handle(), x, y, width, height);
			}
		};

		using RegionPtr = ::ext::HandlePtr<Region>;

		class Compositor :
			public ::ext::Handle<detail::CompositorTraits>
		{
		public:
			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_compositor_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			SurfacePtr create_surface()
			{
				assert(raw_handle() != Traits::invalid());

				return SurfacePtr{::wl_compositor_create_surface(raw_handle())};
			}

			RegionPtr create_region()
			{
				assert(raw_handle() != Traits::invalid());

				return RegionPtr{::wl_compositor_create_region(raw_handle())};
			}
		};

		using CompositorPtr = ::ext::HandlePtr<Compositor>;

		class Buffer :
			public ::ext::Handle<detail::BufferTraits>
		{
		public:
			void add_listener(::wl_buffer_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_buffer_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_buffer_add_listener"};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_buffer_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}
		};

		using BufferPtr = ::ext::HandlePtr<Buffer>;

		class ShmPool :
			public ::ext::Handle<detail::ShmPoolTraits>
		{
		public:
			BufferPtr create_buffer(::std::int32_t const offset, ::std::int32_t const width, ::std::int32_t const height, ::std::int32_t const stride, ::std::uint32_t const format)
			{
				assert(raw_handle() != Traits::invalid());

				return BufferPtr{::wl_shm_pool_create_buffer(raw_handle(), offset, width, height, stride, format)};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shm_pool_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void resize(::std::int32_t const size)
			{
				assert(raw_handle() != Traits::invalid());

				return ::wl_shm_pool_resize(raw_handle(), size);
			}
		};

		using ShmPoolPtr = ::ext::HandlePtr<ShmPool>;

		class Shm :
			public ::ext::Handle<detail::ShmTraits>
		{
		public:
			void add_listener(::wl_shm_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_shm_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_shm_add_listener"};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shm_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			ShmPoolPtr create_pool(::std::int32_t const fd, ::std::int32_t const size)
			{
				assert(raw_handle() != Traits::invalid());

				return ShmPoolPtr{::wl_shm_create_pool(raw_handle(), fd, size)};
			}
		};

		using ShmPtr = ::ext::HandlePtr<Shm>;

		class DataOffer :
			public ::ext::Handle<detail::DataOfferTraits>
		{
		public:
			void add_listener(::wl_data_offer_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_data_offer_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_data_offer_add_listener"};
			}

			void accept(::std::uint32_t const serial, char const* const mime_type)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_offer_accept(raw_handle(), serial, mime_type);
			}

			void receive(char const* const mime_type, FilePtr fd)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_offer_receive(raw_handle(), mime_type, fd.release());
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_offer_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void finish()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_offer_finish(raw_handle());
			}

			void set_actions(::std::uint32_t const dnd_actions, ::std::uint32_t const preferred_action)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_offer_set_actions(raw_handle(), dnd_actions, preferred_action);
			}
		};

		using DataOfferPtr = ::ext::HandlePtr<DataOffer>;

		class DataSource :
			public ::ext::Handle<detail::DataSourceTraits>
		{
		public:
			void add_listener(::wl_data_source_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_data_source_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_data_source_add_listener"};
			}

			void offer(char const* const mime_type)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_source_offer(raw_handle(), mime_type);
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_source_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void set_actions(::std::uint32_t const dnd_actions)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_source_set_actions(raw_handle(), dnd_actions);
			}
		};

		using DataSourcePtr = ::ext::HandlePtr<DataSource>;

		class DataDevice :
			public ::ext::Handle<detail::DataDeviceTraits>
		{
		public:
			void add_listener(::wl_data_device_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_data_device_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_data_device_add_listener"};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_device_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void start_drag(::wl_data_source* const source, ::wl_surface* const origin, ::wl_surface* const icon, ::std::uint32_t const serial)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_device_start_drag(raw_handle(), source, origin, icon, serial);
			}

			void set_selection(::wl_data_source* const source, ::std::uint32_t const serial)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_device_set_selection(raw_handle(), source, serial);
			}

			void release()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_device_release(raw_handle());
				m_raw_handle = Traits::invalid();
			}
		};

		using DataDevicePtr = ::ext::HandlePtr<DataDevice>;

		class DataDeviceManager :
			public ::ext::Handle<detail::DataDeviceManagerTraits>
		{
		public:
			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_data_device_manager_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			DataSourcePtr create_data_source()
			{
				assert(raw_handle() != Traits::invalid());

				return DataSourcePtr{::wl_data_device_manager_create_data_source(raw_handle())};
			}

			DataDevicePtr get_data_device(::wl_seat* const seat)
			{
				assert(raw_handle() != Traits::invalid());

				return DataDevicePtr{::wl_data_device_manager_get_data_device(raw_handle(), seat)};
			}
		};

		using DataDeviceManagerPtr = ::ext::HandlePtr<DataDeviceManager>;

		class ShellSurface :
			public ::ext::Handle<detail::ShellSurfaceTraits>
		{
		public:
			void add_listener(::wl_shell_surface_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_shell_surface_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_shell_surface_add_listener"};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shell_surface_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void pong(::std::uint32_t const serial)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shell_surface_pong(raw_handle(), serial);
			}

			void move(::wl_seat* const seat, ::std::uint32_t const serial)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shell_surface_move(raw_handle(), seat, serial);
			}

			void resize(::wl_seat* const seat, ::std::uint32_t const serial, ::std::uint32_t const edges)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shell_surface_resize(raw_handle(), seat, serial, edges);
			}

			void set_toplevel()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shell_surface_set_toplevel(raw_handle());
			}

			void set_transient(::wl_surface* const parent, ::std::int32_t const x, ::std::int32_t const y, ::std::uint32_t const flags)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shell_surface_set_transient(raw_handle(), parent, x, y, flags);
			}

			void set_fullscreen(::std::uint32_t const method, ::std::uint32_t const framerate, ::wl_output* const output)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shell_surface_set_fullscreen(raw_handle(), method, framerate, output);
			}

			void set_popup(::wl_seat* const seat, ::std::uint32_t const serial, ::wl_surface* const parent, ::std::int32_t const x, ::std::int32_t const y, ::std::uint32_t const flags)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shell_surface_set_popup(raw_handle(), seat, serial, parent, x, y, flags);
			}

			void set_maximized(::wl_output* const output)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shell_surface_set_maximized(raw_handle(), output);
			}

			void set_title(char const* const title)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shell_surface_set_title(raw_handle(), title);
			}

			void set_class(char const* const class_)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shell_surface_set_class(raw_handle(), class_);
			}
		};

		using ShellSurfacePtr = ::ext::HandlePtr<ShellSurface>;

		class Shell :
			public ::ext::Handle<detail::ShellTraits>
		{
		public:
			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_shell_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			ShellSurfacePtr get_shell_surface(::wl_surface* const surface)
			{
				assert(raw_handle() != Traits::invalid());

				return ShellSurfacePtr{::wl_shell_get_shell_surface(raw_handle(), surface)};
			}
		};

		using ShellPtr = ::ext::HandlePtr<Shell>;

		class Pointer :
			public ::ext::Handle<detail::PointerTraits>
		{
		public:
			void add_listener(::wl_pointer_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_pointer_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_pointer_add_listener"};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_pointer_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void set_cursor(::std::uint32_t const serial, ::wl_surface* const surface, ::std::int32_t const hotspot_x, ::std::int32_t const hotspot_y)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_pointer_set_cursor(raw_handle(), serial, surface, hotspot_x, hotspot_y);
			}

			void release()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_pointer_release(raw_handle());
				m_raw_handle = Traits::invalid();
			}
		};

		using PointerPtr = ::ext::HandlePtr<Pointer>;

		class Keyboard :
			public ::ext::Handle<detail::KeyboardTraits>
		{
		public:
			void add_listener(::wl_keyboard_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_keyboard_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_keyboard_add_listener"};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_keyboard_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void release()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_keyboard_release(raw_handle());
				m_raw_handle = Traits::invalid();
			}
		};

		using KeyboardPtr = ::ext::HandlePtr<Keyboard>;

		class Touch :
			public ::ext::Handle<detail::TouchTraits>
		{
		public:
			void add_listener(::wl_touch_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_touch_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_touch_add_listener"};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_touch_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void release()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_touch_release(raw_handle());
				m_raw_handle = Traits::invalid();
			}
		};

		using TouchPtr = ::ext::HandlePtr<Touch>;

		class Seat :
			public ::ext::Handle<detail::SeatTraits>
		{
		public:
			void add_listener(::wl_seat_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_seat_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_seat_add_listener"};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_seat_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			PointerPtr get_pointer()
			{
				assert(raw_handle() != Traits::invalid());

				return PointerPtr{::wl_seat_get_pointer(raw_handle())};
			}

			KeyboardPtr get_keyboard()
			{
				assert(raw_handle() != Traits::invalid());

				return KeyboardPtr{::wl_seat_get_keyboard(raw_handle())};
			}

			TouchPtr get_touch()
			{
				assert(raw_handle() != Traits::invalid());

				return TouchPtr{::wl_seat_get_touch(raw_handle())};
			}

			void release()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_seat_release(raw_handle());
				m_raw_handle = Traits::invalid();
			}
		};

		using SeatPtr = ::ext::HandlePtr<Seat>;

		class Output :
			public ::ext::Handle<detail::OutputTraits>
		{
		public:
			void add_listener(::wl_output_listener const& listener, void* const data)
			{
				assert(raw_handle() != Traits::invalid());

				if (::wl_output_add_listener(raw_handle(), &listener, data) == -1)
					throw ::std::system_error{Error::Wayland, u8"wl_output_add_listener"};
			}

			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_output_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void release()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_output_release(raw_handle());
				m_raw_handle = Traits::invalid();
			}
		};

		using OutputPtr = ::ext::HandlePtr<Output>;

		class Subsurface :
			public ::ext::Handle<detail::SubsurfaceTraits>
		{
		public:
			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_subsurface_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			void set_position(::std::int32_t const x, ::std::int32_t const y)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_subsurface_set_position(raw_handle(), x, y);
			}

			void place_above(::wl_surface* const sibling)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_subsurface_place_above(raw_handle(), sibling);
			}

			void place_below(::wl_surface* const sibling)
			{
				assert(raw_handle() != Traits::invalid());

				::wl_subsurface_place_below(raw_handle(), sibling);
			}

			void set_sync()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_subsurface_set_sync(raw_handle());
			}

			void set_desync()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_subsurface_set_desync(raw_handle());
			}
		};

		using SubsurfacePtr = ::ext::HandlePtr<Subsurface>;

		class Subcompositor :
			public ::ext::Handle<detail::SubcompositorTraits>
		{
		public:
			void destroy()
			{
				assert(raw_handle() != Traits::invalid());

				::wl_subcompositor_destroy(raw_handle());
				m_raw_handle = Traits::invalid();
			}

			SubsurfacePtr get_subsurface(::wl_surface* const surface, ::wl_surface* const parent)
			{
				assert(raw_handle() != Traits::invalid());

				return SubsurfacePtr{::wl_subcompositor_get_subsurface(raw_handle(), surface, parent)};
			}
		};

		using SubcompositorPtr = ::ext::HandlePtr<Subcompositor>;

	} // namespace wl

} // namespace ext

#endif // !HEADER_EXT_WAYLAND_HPP_INCLUDED
