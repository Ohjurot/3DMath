%include "3DMath.inc"

bits 64
default rel

; Define functions as globals
global __m3d_cpurand_seed_uint64
global __m3d_cpurand_get_uint64
global __m3d_cpurand_get_uint32
global __m3d_cpurand_get_uint16
global __m3d_cpurand_get_float

; Application programm
section .text

; extern void __m3d_cpurand_seed_uint64(uint64_t seed);
__m3d_cpurand_seed_uint64:
    rdseed RPARAM0
    ret

; extern uint64_t __m3d_cpurand_get_uint64();
__m3d_cpurand_get_uint64:
    RDRAND RRETURN
    ret

; extern uint32_t __m3d_cpurand_get_uint32();
__m3d_cpurand_get_uint32:
    rdrand R32RETURN
    ret

; extern uint16_t __m3d_cpurand_get_uint16();
__m3d_cpurand_get_uint16:
    rdrand R16RETURN
    ret

; extern float __m3d_cpurand_get_float();
__m3d_cpurand_get_float:
    ; Getting 32-Bit random value
    rdrand R32RETURN
    ; Create mask of mask for sign
    or R32PARAM0, 0xFFFFFFFF
    shr R32PARAM0, 1
    and R32RETURN, R32PARAM0  
    ; Move to XMM and convert to float
    movd XMM0, R32RETURN
    movd XMM1, R32PARAM0
    CVTDQ2PS XMM0, XMM0
    CVTDQ2PS XMM1, XMM1
    ; Divide
    divps XMM0, XMM1
    ret
