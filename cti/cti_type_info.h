#pragma once

#include "cti_hash.h"

#include <type_info>

namespace cti
{
	namespace detail
	{
		template <typename... T>
		constexpr string full_name()
		{
#if defined(__clang__) || defined(__GNUC__)
			return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
			return __FUNCSIG__;
#else
#ifdef __func__
			return __func__;
#else
#error "Unknown Compiler, cannot use the cti!"
#endif
#endif
		}

		template <typename... T>
		constexpr string type_name()
		{
			constexpr string full = full_name<T...>();
			constexpr string::size_type start = full.find('<') + 1;
			constexpr string::size_type end = full.find_reverse('>');
			return { full.str + start, full.str + end };
		}

		template <typename... T>
		constexpr string type_name_decayed()
		{
			return type_name<std::decay_t<T...>>();
		}
	}

	struct type_info_base
	{
		constexpr type_info_base()
			: str("void")
		{
		}

		constexpr ~type_info_base() = default;

		constexpr type_info_base(const char* Str)
			: str(Str)
		{
		}

		constexpr type_info_base(const cti::string& Str)
			: str(Str)
		{
		}

		type_info_base& operator=(const type_info_base& rhs)
		{
			str = rhs.str;

			return *this;
		}

		type_info_base(const type_info_base& rhs)
			: str(rhs.str)
		{
		}

		type_info_base(type_info_base&& rhs) noexcept
			: str(std::exchange(rhs.str, "void"))
		{
		}

		type_info_base& operator=(type_info_base&& rhs) noexcept
		{
			str = std::exchange(rhs.str, "void");

			return *this;
		}

		constexpr const cti::string& name() const
		{
			return str;
		}

		constexpr hash_t hash() const
		{
			return cti::hash(str);
		}

		constexpr hash_t operator() () const
		{
			return hash();
		}

		cti::string str;
	};

	constexpr bool operator==(const type_info_base& lhs, const type_info_base& rhs)
	{
		return lhs.hash() == rhs.hash();
	}

	constexpr bool operator!=(const type_info_base& lhs, const type_info_base& rhs)
	{
		return lhs.hash() != rhs.hash();
	}

	using tib = type_info_base;

	template <typename... T>
	constexpr type_info_base type_info()
	{
		return { detail::type_name<T...>() };
	};

	constexpr type_info_base type_info(const cti::string& str)
	{
		return { str };
	}

	template <typename... T>
	constexpr type_info_base type_info_decayed()
	{
		return { detail::type_name_decayed<T...>() };
	};
}

namespace std
{
	template<>
	struct hash<cti::type_info_base>
	{
		constexpr size_t operator() (const ::cti::type_info_base& lhs) const
		{
			return lhs.hash();
		}
	};
}