#pragma once

#include "3DRand_cpurand.h"

namespace M3D {
    // Random seeding
    inline void RandomSeed(uint64_t seed) {
        __m3d_cpurand_seed_uint64(seed);
    }

    // Random getting
    inline uint64_t RandomUInt64() {
        return __m3d_cpurand_get_uint64();
    }
    inline uint32_t RandomUInt32() {
        return __m3d_cpurand_get_uint32();
    }
    inline uint16_t RandomUInt16() {
        return __m3d_cpurand_get_uint16();
    }
    inline float RandomFloat() {
        return __m3d_cpurand_get_float();
    }
}
