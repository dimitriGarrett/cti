#pragma once

namespace cti
{
	struct string
	{
		using size_type = size_t;

		constexpr static size_type string_len(const char* str)
		{
			return (str[0]) == '\0' ? 0 : string_len(str + 1) + 1;
		}

		template <size_type S>
		constexpr string(const char Str[S])
			: str(Str), size(S - 1)
		{
		}

		constexpr string(const char* Str)
			: str(Str), size(string_len(Str))
		{
		}

		constexpr string(const char* Begin, const char* End)
			: str(Begin), size(static_cast<size_type>(End - Begin))
		{
		}

		constexpr size_type find(char ch) const
		{
			return find_impl(*this, ch);
		}

		constexpr size_type find_reverse(char ch) const
		{
			return find_reverse_impl(*this, ch, size);
		}

		constexpr bool operator==(const char* other) const
		{
			for (size_type i = 0; i < size; ++i)
			{
				if (str[i] != other[i])
					return false;
			}

			return true;
		}

		constexpr char operator[] (size_type index) const
		{
			return str[index];
		}

		const char* str;
		size_type size;

		constexpr const char* begin() const
		{
			return &str[0];
		}

		constexpr const char* end() const
		{
			return &str[0] + size;
		}

	private:
		static constexpr size_type find_impl(const string& s, char ch, size_type index = 0)
		{
			if (index == s.size)
			{
				return size_type(-1);
			}

			return (s.str[index] == ch) ? index : find_impl(s, ch, index + 1);
		}

		static constexpr size_type find_reverse_impl(const string& s, char ch, size_type index)
		{
			if (index == 0)
			{
				return size_type(-1);
			}

			return (s.str[index] == ch) ? index : find_reverse_impl(s, ch, index - 1);
		}
	};
}