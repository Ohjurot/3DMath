%include "3DMath.inc"

; Define functions as globals
global __m3d_sse_vector_add_cw
global __m3d_sse_vector_add_sc
global __m3d_sse_vector_sub_cw
global __m3d_sse_vector_sub_sc
global __m3d_sse_vector_mul_cw
global __m3d_sse_vector_mul_sc
global __m3d_sse_vector_div_cw
global __m3d_sse_vector_div_sc
global __m3d_sse_vector_normalize
global __m3d_sse_vector_length
global __m3d_sse_vector_dot
global __m3d_sse_vector_cross
global __m3d_sse_vector_mad

; Application programm
section .text

; extern void __m3d_sse_vector_add_cw(const void* vec4in0, const void* vec4in1, void* vec4out);
__m3d_sse_vector_add_cw:
    movaps XMM0, [RPARAM0]
    movaps XMM1, [RPARAM1]
    addps XMM0, XMM1
    movaps [RPARAM2], XMM0
    ret

; extern void __m3d_sse_vector_add_sc(float scalar, const void* vec4in0, const void* vec4out);
__m3d_sse_vector_add_sc:
    movaps XMM1, [RPARAM1]
    shufps XMM0, XMM0, 0b00000000
    addps XMM0, XMM1
    movaps [RPARAM2], XMM0
    ret

; extern void __m3d_sse_vector_sub_cw(const void* vec4in0, const void* vec4in1, void* vec4out);
__m3d_sse_vector_sub_cw:
    movaps XMM0, [RPARAM0]
    movaps XMM1, [RPARAM1]
    subps XMM0, XMM1
    movaps [RPARAM2], XMM0
    ret

; extern void __m3d_sse_vector_sub_sc(float scalar, const void* vec4in0, const void* vec4out);
__m3d_sse_vector_sub_sc:
    movaps XMM1, [RPARAM1]
    shufps XMM0, XMM0, 0b00000000
    subps XMM0, XMM1
    movaps [RPARAM2], XMM0
    ret

; extern void __m3d_sse_vector_mul_cw(const void* vec4in0, const void* vec4in1, void* vec4out);
__m3d_sse_vector_mul_cw:
    movaps XMM0, [RPARAM0]
    movaps XMM1, [RPARAM1]
    mulps XMM0, XMM1
    movaps [RPARAM2], XMM0
    ret

; extern void __m3d_sse_vector_mul_sc(float scalar, const void* vec4in0, const void* vec4out);
__m3d_sse_vector_mul_sc:
    movaps XMM1, [RPARAM1]
    shufps XMM0, XMM0, 0b00000000
    mulps XMM0, XMM1
    movaps [RPARAM2], XMM0
    ret

; extern void __m3d_sse_vector_div_cw(const void* vec4in0, const void* vec4in1, void* vec4out);
__m3d_sse_vector_div_cw:
    movaps XMM0, [RPARAM0]
    movaps XMM1, [RPARAM1]
    divps XMM0, XMM1
    movaps [RPARAM2], XMM0
    ret

; extern void __m3d_sse_vector_div_sc(float scalar, const void* vec4in0, const void* vec4out);
__m3d_sse_vector_div_sc:
    movaps XMM1, [RPARAM1]
    shufps XMM0, XMM0, 0b00000000
    divps XMM0, XMM1
    movaps [RPARAM2], XMM0
    ret



; extern void __m3d_sse_vector_normalize(const void* vec4in0, void* vec4out);
__m3d_sse_vector_normalize:
    ; Load vector
    movaps XMM0, [RPARAM0]
    movaps XMM1, XMM0
    ; Compute vector length
    mulps XMM1, XMM0
    haddps XMM1, XMM1
    haddps XMM1, XMM1
    sqrtps XMM1, XMM1
    ; Normalze
    divps XMM0, XMM1
    ; Store
    movaps [RPARAM1], XMM0
    ret

; extern float __m3d_sse_vector_length(const void* vec4in0);
__m3d_sse_vector_length:
    movaps XMM0, [RPARAM0]
    mulps XMM0, XMM0
    haddps XMM0, XMM0
    haddps XMM0, XMM0
    sqrtps XMM0, XMM0
    ret

; extern float __m3d_sse_vector_dot(const void* vec4in0, const void* vec4in1);
__m3d_sse_vector_dot:
    ; Load values
    movaps XMM0, [RPARAM0]
    movaps XMM1, [RPARAM1]
    ; Multiply and hadd
    dpps XMM0, XMM1, 0xFF
    ret

; extern void __m3d_sse_vector_cross(const void* vec4in0, const void* vec4in1, const void* vec4out);
__m3d_sse_vector_cross:
    ; Load
    movaps XMM0, [RPARAM0]
    movaps XMM1, [RPARAM1]
    ; Expand (Row 1)
    insertps XMM2, XMM0, 0b01000000
    insertps XMM2, XMM0, 0b10010000
    insertps XMM2, XMM0, 0b00100000
    ; Expand (Row 2)
    insertps XMM3, XMM1, 0b10000000 
    insertps XMM3, XMM1, 0b00010000
    insertps XMM3, XMM1, 0b01100000
    ; First multiply
    mulps XMM2, XMM3
    ; Expand (Row 3)
    insertps XMM3, XMM0, 0b10000000 
    insertps XMM3, XMM0, 0b00010000
    insertps XMM3, XMM0, 0b01100000
    ; Expand (Row 4)
    insertps XMM4, XMM1, 0b01000000
    insertps XMM4, XMM1, 0b10010000
    insertps XMM4, XMM1, 0b00100000
    ; Second multiply
    mulps XMM3, XMM4
    ; Substraction
    subps XMM2, XMM3
    ; Move 4 th component (from first)
    insertps XMM2, XMM0, 0b11110000
    ; Store
    movaps [RPARAM2], XMM2
    ret

; extern void __m3d_sse_vector_mad(const void* vec4in0, const void* vec4in1, const void* vec4in2, void* vec4out);
__m3d_sse_vector_mad:
    ; Load
    movaps XMM0, [RPARAM0]
    movaps XMM1, [RPARAM1]
    movaps XMM2, [RPARAM2]
    ; Compute and store
    mulps XMM0, XMM1
    addps XMM0, XMM2
    movaps [RPARAM3], XMM0
    ret
