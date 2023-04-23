#pragma once

#include "cti_string.h"
#include <cstdint>

namespace cti
{
    using hash_t = uint64_t;

    //polynomial rolling hash function
    static constexpr hash_t hash(const cti::string& str)
    {
        constexpr hash_t p = 255; //255 different characters in char
        constexpr hash_t m = 575237319495109; // m
        hash_t res = 0; //accumulator
        hash_t pw = 1;

        for (string::size_type i = 0; i < str.size; ++i)
        {
            res += (str[i] * pw) % m;
            pw *= p;
        }

        return res;
    }
}