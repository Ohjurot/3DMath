#pragma once

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif
    // Set random seed
    extern void __m3d_cpurand_seed_uint64(uint64_t seed);
    // Get random
    extern uint64_t __m3d_cpurand_get_uint64();
    extern uint32_t __m3d_cpurand_get_uint32();
    extern uint16_t __m3d_cpurand_get_uint16();
    extern float __m3d_cpurand_get_float();

#ifdef __cplusplus
}
#endif