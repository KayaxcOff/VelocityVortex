//
// Created by muham on 28.10.2025.
//

#ifndef VELOCITYVORTEX_ASSERT_HPP
#define VELOCITYVORTEX_ASSERT_HPP

#include <stdexcept>
#include <cassert>
#include <iostream>

#define VORTEX_ASSERT(ptr, msg) \
do { \
    if (!(ptr)) { \
        std::cerr << "VORTEX ERROR: " << msg << std::endl; \
        assert(ptr && msg); \
        throw std::runtime_error(msg); \
    } \
} while(0)

#endif //VELOCITYVORTEX_ASSERT_HPP