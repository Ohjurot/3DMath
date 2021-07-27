#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    // Per component / scalar operations
    // Matrix addition (Component wise)
    extern void __m3d_sse_matrix_add_cw(const void* mat4x4in0, const void* mat4x4in1, void* mat4x4out);
    // Matrix multiplycation scalar
    extern void __m3d_sse_matrix_mul_sc(float value, const void* mat4x4in0, void* mat4x4out);
    // Matrix transpose
    extern void __m3d_sse_matrix_transpose(const void* mat4x4in0, void* mat4x4out);
    // Matrix multiplycation
    extern void __m3d_sse_matrix_mul(const void* mat4x4in0, const void* mat4x4in1, void* mat4x4out);
    // Matrix * Vector
    extern void __m3d_sse_matrix_vector_mul(const void* mat4x4in0, const void* vec4in0, void* vec4out);

#ifdef __cplusplus
}
#endif