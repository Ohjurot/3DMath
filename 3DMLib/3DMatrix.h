#pragma once

#include "3DMath.h"
#include "3DVector.h"
#include "3DMatrix_sse.h"

namespace M3D {
    // 4x4 Matrix
    struct alignas(M3D_FLT4_ALLIGN) Mat4x4 {
        union {
            FLT elements[4 * 4] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
            struct {
                FLT row0[4], row1[4], row2[4], row3[4];
            };
        };

        // Transpose matrix
        inline void transpose() {
            __m3d_sse_matrix_transpose(this, this);
        }
        inline Mat4x4 ntranspose() {
            Mat4x4 out;
            __m3d_sse_matrix_transpose(this, &out);
            return out;
        }

        // Matrix addition
        inline Mat4x4 operator+(const Mat4x4& other) {
            Mat4x4 out;
            __m3d_sse_matrix_add_cw(this, &other, &out);
            return out;
        }
        inline Mat4x4& operator+=(const Mat4x4& other) {
            __m3d_sse_matrix_add_cw(this, &other, this);
            return *this;
        }
        
        // Matrix multiplication scalar
        inline Mat4x4 operator*(FLT value) {
            Mat4x4 out;
            __m3d_sse_matrix_mul_sc(value, this, &out);
            return out;
        }
        inline Mat4x4& operator*=(FLT value) {
            __m3d_sse_matrix_mul_sc(value, this, this);
            return *this;
        }

        // Matrix multiply by matrix
        inline Mat4x4& operator*(const Mat4x4& other) {
            Mat4x4 out;
            __m3d_sse_matrix_mul(this, &other, &out);
            return out;
        }

        // Vector multiply with matrix
        inline Vec4& operator*(const Vec4& other) {
            Vec4 out;
            __m3d_sse_matrix_vector_mul(this, &other, &out);
            return out;
        }
    };

    // Matrix multiplication
    inline Mat4x4 operator*(FLT value, const Mat4x4& other) {
        Mat4x4 out;
        __m3d_sse_matrix_mul_sc(value, &other, &out);
        return out;
    }
}
