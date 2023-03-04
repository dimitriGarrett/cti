#pragma once

#include "cti_string.h"

namespace cti
{
    using hash_t = unsigned long long;

    static constexpr hash_t hash(const cti::string& str)
    {
        static_assert(sizeof(hash_t) == 8);
        // FNV-1a 64 bit algorithm
        size_t result = 0xcbf29ce484222325; // FNV offset basis

        for (char c : str) {
            result ^= c;
            result *= 1099511628211; // FNV prime
        }

        return result;
    }
}