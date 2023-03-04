#pragma once

#include "cti_type_info.h"

#include <ostream>

static std::ostream& operator <<(std::ostream& os, const cti::string& str)
{
	for (cti::string::size_type i = 0; i < str.size; ++i)
	{
		os << str.str[i];
	}

	return os;
}