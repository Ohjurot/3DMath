#pragma once

#ifdef __cplusplus
extern "C"{
#endif
    // Per component / scalar operations
    // Vector addition (Component wise)
    extern void __m3d_sse_vector_add_cw(const void* vec4in0, const void* vec4in1, void* vec4out);
    // Vector addition (Scalar)
    extern void __m3d_sse_vector_add_sc(float scalar, const void* vec4in0, void* vec4out);
    // Vector substraction (Component wise)
    extern void __m3d_sse_vector_sub_cw(const void* vec4in0, const void* vec4in1, void* vec4out);
    // Vector substraction (Scalar)
    extern void __m3d_sse_vector_sub_sc(float scalar, const void* vec4in0, void* vec4out);
    // Vector multiplication (Component wise)
    extern void __m3d_sse_vector_mul_cw(const void* vec4in0, const void* vec4in1, void* vec4out);
    // Vector multiplication (Scalar)
    extern void __m3d_sse_vector_mul_sc(float scalar, const void* vec4in0, void* vec4out);
    // Vector multiplication (Component wise)
    extern void __m3d_sse_vector_div_cw(const void* vec4in0, const void* vec4in1, void* vec4out);
    // Vector multiplication (Scalar)
    extern void __m3d_sse_vector_div_sc(float scalar, const void* vec4in0, void* vec4out);

    // Operations
    // Normalize vector
    extern void __m3d_sse_vector_normalize(const void* vec4in0, void* vec4out);
    // Vector length
    extern float __m3d_sse_vector_length(const void* vec4in0);
    // Vector dot product
    extern float __m3d_sse_vector_dot(const void* vec4in0, const void* vec4in1);
    // Vector cross product
    extern void __m3d_sse_vector_cross(const void* vec4in0, const void* vec4in1, void* vec4out);

#ifdef __cplusplus
}
#endif