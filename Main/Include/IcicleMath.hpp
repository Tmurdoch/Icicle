#pragma once

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>


#include <stddef.h>
#include <cstdint>
#include <functional>

namespace Icicle {

    // from: https://stackoverflow.com/a/57595105
    template <typename T, typename... Rest>
    void hashCombine(std::size_t& seed, const T& v, const Rest&... rest) {
        seed ^= std::hash<T>{}(v)+0x9e3779b9 + (seed << 6) + (seed >> 2);
        (hashCombine(seed, rest), ...);
    };

    //Declarations

    void* ptr_add(void* pos, size_t adjustment);
    const void* ptr_add(const void* p, size_t x);

    void* ptr_subtract(void* pos, size_t adjustment);
    const void* ptr_subtract(const void* pos, size_t adjustment);


    /**
     * calculates how much padding needs to be added before _current_pos
     *  to achieve the specified alignment while leaving space for the 
     * allocation header.
    */
    uint8_t alignForwardAdjustmentWithHeader(void* _current_pos,
                                                uint8_t alignment);



}