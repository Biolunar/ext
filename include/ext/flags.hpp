#ifndef HEADER_EXT_FLAGS_HPP_INCLUDED
#define HEADER_EXT_FLAGS_HPP_INCLUDED

namespace ext
{

template <typename BitType, typename MaskType>
class Flags
{
public:
	Flags() noexcept : m_mask{} {}
	Flags(BitType bit) noexcept : m_mask(static_cast<MaskType>(bit)) {}
	Flags(MaskType mask) noexcept : m_mask(mask) {}
	Flags(Flags<BitType, MaskType> const& rhs) noexcept : m_mask{rhs.m_mask} {}
	Flags<BitType, MaskType>& operator=(Flags<BitType, MaskType> const& rhs) noexcept { m_mask = rhs.m_mask; return *this; }

	Flags<BitType, MaskType>& operator|=(Flags<BitType, MaskType> const& rhs) noexcept
	{
		m_mask |= rhs.m_mask;
		return *this;
	}

	Flags<BitType, MaskType>& operator&=(Flags<BitType, MaskType> const& rhs) noexcept
	{
		m_mask &= rhs.m_mask;
		return *this;
	}

	Flags<BitType, MaskType>& operator^=(Flags<BitType, MaskType> const& rhs) noexcept
	{
		m_mask ^= rhs.m_mask;
		return *this;
	}

	Flags<BitType, MaskType> operator|(Flags<BitType, MaskType> const& rhs) const noexcept
	{
		Flags<BitType, MaskType> result(*this);
		result |= rhs;
		return result;
	}

	Flags<BitType, MaskType> operator&(Flags<BitType, MaskType> const& rhs) const noexcept
	{
		Flags<BitType, MaskType> result(*this);
		result &= rhs;
		return result;
	}

	Flags<BitType, MaskType> operator^(Flags<BitType, MaskType> const& rhs) const noexcept
	{
		Flags<BitType, MaskType> result(*this);
		result ^= rhs;
		return result;
	}

	bool operator!() const noexcept { return !m_mask; }
	bool operator==(Flags<BitType, MaskType> const& rhs) const noexcept { return m_mask == rhs.m_mask; }
	bool operator!=(Flags<BitType, MaskType> const& rhs) const noexcept { return m_mask != rhs.m_mask; }
	explicit operator bool() const noexcept { return !!m_mask; }
	explicit operator MaskType() const noexcept { return m_mask; }

private:
	MaskType  m_mask;
};

template <typename BitType, typename MaskType>
Flags<BitType, MaskType> operator|(BitType bit, Flags<BitType, MaskType> const& flags)
{
	return flags | bit;
}

template <typename BitType, typename MaskType>
Flags<BitType, MaskType> operator&(BitType bit, Flags<BitType, MaskType> const& flags)
{
	return flags & bit;
}

template <typename BitType, typename MaskType>
Flags<BitType, MaskType> operator^(BitType bit, Flags<BitType, MaskType> const& flags)
{
	return flags ^ bit;
}

} // namespace ext

#endif // HEADER_EXT_FLAGS_HPP_INCLUDED
