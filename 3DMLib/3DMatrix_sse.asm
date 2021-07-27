%include "3DMath.inc"

; Define functions as globals
global __m3d_sse_matrix_add_cw
global __m3d_sse_matrix_mul_sc
global __m3d_sse_matrix_transpose
global __m3d_sse_matrix_mul
global __m3d_sse_matrix_vector_mul

; Application programm
section .text

; extern void __m3d_sse_matrix_add_cw(const void* mat4x4in0, const void* mat4x4in1, void* mat4x4out);
__m3d_sse_matrix_add_cw:
    ; Matrix A to XMM0-3
    movaps XMM0, [RPARAM0 +  0]
    movaps XMM1, [RPARAM0 + 16]
    movaps XMM2, [RPARAM0 + 32]
    movaps XMM3, [RPARAM0 + 48]
    ; Matrix B to XMM4-7
    movaps XMM4, [RPARAM1 +  0]
    movaps XMM5, [RPARAM1 + 16]
    movaps XMM6, [RPARAM1 + 32]
    movaps XMM7, [RPARAM1 + 48]
    ; Add components
    addps XMM0, XMM4
    addps XMM1, XMM5
    addps XMM2, XMM6
    addps XMM3, XMM7
    ; Store Matrix
    movaps [RPARAM2 +  0], XMM0
    movaps [RPARAM2 + 16], XMM1
    movaps [RPARAM2 + 32], XMM2
    movaps [RPARAM2 + 48], XMM3
    ret

; extern void __m3d_sse_matrix_mul_sc(float value, const void* mat4x4in0, void* mat4x4out);
__m3d_sse_matrix_mul_sc:
    ; Expand float value
    shufps XMM0, XMM0, 0b00000000
    ; Load matrix to XMM1-4
    movaps XMM1, [RPARAM1 +  0]
    movaps XMM2, [RPARAM1 + 16]
    movaps XMM3, [RPARAM1 + 32]
    movaps XMM4, [RPARAM1 + 48]
    ; Multiply
    mulps XMM1, XMM0
    mulps XMM2, XMM0
    mulps XMM3, XMM0
    mulps XMM4, XMM0
    ; Store
    movaps [RPARAM2 +  0], XMM1
    movaps [RPARAM2 + 16], XMM2
    movaps [RPARAM2 + 32], XMM3
    movaps [RPARAM2 + 48], XMM4
    ret

; extern void __m3d_sse_matrix_transpose(const void* mat4x4in0, void* mat4x4out);
__m3d_sse_matrix_transpose:
    ; Matrix A to XMM0-3
    movaps XMM0, [RPARAM0 +  0]
    movaps XMM1, [RPARAM0 + 16]
    movaps XMM2, [RPARAM0 + 32]
    movaps XMM3, [RPARAM0 + 48]
    ; Matrix B to XMM4-7
    movaps XMM4, [RPARAM1 +  0]
    movaps XMM5, [RPARAM1 + 16]
    movaps XMM6, [RPARAM1 + 32]
    movaps XMM7, [RPARAM1 + 48]

    ; Transpose matrix B to XMM8-11 (8)
    insertps XMM8, XMM4, 0b00000000
    insertps XMM8, XMM5, 0b00010000
    insertps XMM8, XMM6, 0b00100000
    insertps XMM8, XMM7, 0b00110000
    ; Transpose matrix B to XMM8-11 (9)
    insertps XMM9, XMM4, 0b01000000
    insertps XMM9, XMM5, 0b01010000
    insertps XMM9, XMM6, 0b01100000
    insertps XMM9, XMM7, 0b01110000
    ; Transpose matrix B to XMM8-11 (10)
    insertps XMM10, XMM4, 0b10000000
    insertps XMM10, XMM5, 0b10010000
    insertps XMM10, XMM6, 0b10100000
    insertps XMM10, XMM7, 0b10110000
    ; Transpose matrix B to XMM8-11 (11)
    insertps XMM11, XMM4, 0b11000000
    insertps XMM11, XMM5, 0b11010000
    insertps XMM11, XMM6, 0b11100000
    insertps XMM11, XMM7, 0b11110000

    ; Store matrix
    movaps [RPARAM2 +  0], XMM8
    movaps [RPARAM2 + 16], XMM9
    movaps [RPARAM2 + 32], XMM10
    movaps [RPARAM2 + 48], XMM11
    ret

; extern void __m3d_sse_matrix_mul(const void* mat4x4in0, const void* mat4x4in1, void* mat4x4out);
__m3d_sse_matrix_mul:
    ; Matrix A to XMM0-3
    movaps XMM0, [RPARAM0 +  0]
    movaps XMM1, [RPARAM0 + 16]
    movaps XMM2, [RPARAM0 + 32]
    movaps XMM3, [RPARAM0 + 48]
    ; Matrix B to XMM4-7
    movaps XMM4, [RPARAM1 +  0]
    movaps XMM5, [RPARAM1 + 16]
    movaps XMM6, [RPARAM1 + 32]
    movaps XMM7, [RPARAM1 + 48]

    ; Transpose matrix B to XMM8-11 (8)
    insertps XMM8, XMM4, 0b00000000
    insertps XMM8, XMM5, 0b00010000
    insertps XMM8, XMM6, 0b00100000
    insertps XMM8, XMM7, 0b00110000
    ; Transpose matrix B to XMM8-11 (9)
    insertps XMM9, XMM4, 0b01000000
    insertps XMM9, XMM5, 0b01010000
    insertps XMM9, XMM6, 0b01100000
    insertps XMM9, XMM7, 0b01110000
    ; Transpose matrix B to XMM8-11 (10)
    insertps XMM10, XMM4, 0b10000000
    insertps XMM10, XMM5, 0b10010000
    insertps XMM10, XMM6, 0b10100000
    insertps XMM10, XMM7, 0b10110000
    ; Transpose matrix B to XMM8-11 (11)
    insertps XMM11, XMM4, 0b11000000
    insertps XMM11, XMM5, 0b11010000
    insertps XMM11, XMM6, 0b11100000
    insertps XMM11, XMM7, 0b11110000

    ; Row 0
    ; Multiply (0, 0)
    movaps XMM12, XMM0
    mulps XMM12, XMM8
    haddps XMM12, XMM12
    haddps XMM12, XMM12
    ; Multiply (0, 1)
    movaps XMM13, XMM0
    mulps XMM13, XMM9
    haddps XMM13, XMM13
    haddps XMM13, XMM13
    ; Multiply (0, 2)
    movaps XMM14, XMM0
    mulps XMM14, XMM10
    haddps XMM14, XMM14
    haddps XMM14, XMM14
    ; Multiply (0, 3)
    movaps XMM15, XMM0
    mulps XMM15, XMM11
    haddps XMM15, XMM15
    haddps XMM15, XMM15
    ; Store
    insertps XMM4, XMM12, 0b00000000
    insertps XMM4, XMM13, 0b00010000
    insertps XMM4, XMM14, 0b00100000
    insertps XMM4, XMM15, 0b00110000

    ; Row 1
    ; Multiply (1, 0)
    movaps XMM12, XMM1
    mulps XMM12, XMM8
    haddps XMM12, XMM12
    haddps XMM12, XMM12
    ; Multiply (1, 1)
    movaps XMM13, XMM1
    mulps XMM13, XMM9
    haddps XMM13, XMM13
    haddps XMM13, XMM13
    ; Multiply (1, 2)
    movaps XMM14, XMM1
    mulps XMM14, XMM10
    haddps XMM14, XMM14
    haddps XMM14, XMM14
    ; Multiply (1, 3)
    movaps XMM15, XMM1
    mulps XMM15, XMM11
    haddps XMM15, XMM15
    haddps XMM15, XMM15
    ; Store
    insertps XMM5, XMM12, 0b00000000
    insertps XMM5, XMM13, 0b00010000
    insertps XMM5, XMM14, 0b00100000
    insertps XMM5, XMM15, 0b00110000
    
    ; Row 2
    ; Multiply (2, 0)
    movaps XMM12, XMM2
    mulps XMM12, XMM8
    haddps XMM12, XMM12
    haddps XMM12, XMM12
    ; Multiply (1, 1)
    movaps XMM13, XMM2
    mulps XMM13, XMM9
    haddps XMM13, XMM13
    haddps XMM13, XMM13
    ; Multiply (2, 2)
    movaps XMM14, XMM2
    mulps XMM14, XMM10
    haddps XMM14, XMM14
    haddps XMM14, XMM14
    ; Multiply (2, 3)
    movaps XMM15, XMM2
    mulps XMM15, XMM11
    haddps XMM15, XMM15
    haddps XMM15, XMM15
    ; Store
    insertps XMM6, XMM12, 0b00000000
    insertps XMM6, XMM13, 0b00010000
    insertps XMM6, XMM14, 0b00100000
    insertps XMM6, XMM15, 0b00110000

    ; Row 3
    ; Multiply (3, 0)
    movaps XMM12, XMM3
    mulps XMM12, XMM8
    haddps XMM12, XMM12
    haddps XMM12, XMM12
    ; Multiply (3, 1)
    movaps XMM13, XMM3
    mulps XMM13, XMM9
    haddps XMM13, XMM13
    haddps XMM13, XMM13
    ; Multiply (3, 2)
    movaps XMM14, XMM3
    mulps XMM14, XMM10
    haddps XMM14, XMM14
    haddps XMM14, XMM14
    ; Multiply (3, 3)
    movaps XMM15, XMM3
    mulps XMM15, XMM11
    haddps XMM15, XMM15
    haddps XMM15, XMM15
    ; Store
    insertps XMM7, XMM12, 0b00000000
    insertps XMM7, XMM13, 0b00010000
    insertps XMM7, XMM14, 0b00100000
    insertps XMM7, XMM15, 0b00110000

    ; Store matrix
    movaps [RPARAM2 +  0], XMM4
    movaps [RPARAM2 + 16], XMM5
    movaps [RPARAM2 + 32], XMM6
    movaps [RPARAM2 + 48], XMM7
    ret

; extern void __m3d_sse_matrix_vector_mul(const void* mat4x4in0, const void* vec4in0, void* vec4out);
__m3d_sse_matrix_vector_mul:
    ; Load matrix XMM0-3
    movaps XMM0, [RPARAM0 +  0]
    movaps XMM1, [RPARAM0 + 16]
    movaps XMM2, [RPARAM0 + 32]
    movaps XMM3, [RPARAM0 + 48]

    ; Load vector XMM4
    movaps XMM4, [RPARAM1]

    ; Multiply with matrix
    mulps XMM0, XMM4
    mulps XMM1, XMM4
    mulps XMM2, XMM4
    mulps XMM3, XMM4

    ; Sum rows
    haddps XMM0, XMM0
    haddps XMM0, XMM0
    haddps XMM1, XMM1
    haddps XMM1, XMM1
    haddps XMM2, XMM2
    haddps XMM2, XMM2
    haddps XMM3, XMM3
    haddps XMM3, XMM3

    ; Pack to vector
    punpckldq XMM0, XMM1
    punpckldq XMM2, XMM3
    punpcklqdq XMM0, XMM2

    ; Store vector
    movaps [RPARAM2], XMM0
    ret
