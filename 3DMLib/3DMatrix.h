#pragma once

#include "3DMath.h"
#include "3DVector.h"
#include "3DMatrix_sse.h"

namespace M3D {
    // 4x4 Matrix
    struct alignas(M3D_FLT4_ALLIGN) Mat4x4 {
        union {
            FLT elements[4 * 4] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
            FLT elements2D[4][4];
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

        // Determinate
        inline float det() {
            return
                elements2D[0][3] * elements2D[1][2] * elements2D[2][1] * elements2D[3][0] - elements2D[0][2] * elements2D[1][3] * elements2D[2][1] * elements2D[3][0] -
                elements2D[0][3] * elements2D[1][1] * elements2D[2][2] * elements2D[3][0] + elements2D[0][1] * elements2D[1][3] * elements2D[2][2] * elements2D[3][0] +
                elements2D[0][2] * elements2D[1][1] * elements2D[2][3] * elements2D[3][0] - elements2D[0][1] * elements2D[1][2] * elements2D[2][3] * elements2D[3][0] -
                elements2D[0][3] * elements2D[1][2] * elements2D[2][0] * elements2D[3][1] + elements2D[0][2] * elements2D[1][3] * elements2D[2][0] * elements2D[3][1] +
                elements2D[0][3] * elements2D[1][0] * elements2D[2][2] * elements2D[3][1] - elements2D[0][0] * elements2D[1][3] * elements2D[2][2] * elements2D[3][1] -
                elements2D[0][2] * elements2D[1][0] * elements2D[2][3] * elements2D[3][1] + elements2D[0][0] * elements2D[1][2] * elements2D[2][3] * elements2D[3][1] +
                elements2D[0][3] * elements2D[1][1] * elements2D[2][0] * elements2D[3][2] - elements2D[0][1] * elements2D[1][3] * elements2D[2][0] * elements2D[3][2] -
                elements2D[0][3] * elements2D[1][0] * elements2D[2][1] * elements2D[3][2] + elements2D[0][0] * elements2D[1][3] * elements2D[2][1] * elements2D[3][2] +
                elements2D[0][1] * elements2D[1][0] * elements2D[2][3] * elements2D[3][2] - elements2D[0][0] * elements2D[1][1] * elements2D[2][3] * elements2D[3][2] -
                elements2D[0][2] * elements2D[1][1] * elements2D[2][0] * elements2D[3][3] + elements2D[0][1] * elements2D[1][2] * elements2D[2][0] * elements2D[3][3] +
                elements2D[0][2] * elements2D[1][0] * elements2D[2][1] * elements2D[3][3] - elements2D[0][0] * elements2D[1][2] * elements2D[2][1] * elements2D[3][3] -
                elements2D[0][1] * elements2D[1][0] * elements2D[2][2] * elements2D[3][3] + elements2D[0][0] * elements2D[1][1] * elements2D[2][2] * elements2D[3][3];
        }

        // Compute the inverse
        inline Mat4x4 ninverse() {
            // Step 01
            Mat4x4 out;
            out.elements2D[0][0] = elements[5] * elements[10] * elements[15] - elements[5] * elements[11] * elements[14] - elements[9] * elements[6] * elements[15] + elements[9] * elements[7] * elements[14] + elements[13] * elements[6] * elements[11] - elements[13] * elements[7] * elements[10];
            out.elements2D[1][0] = -elements[4] * elements[10] * elements[15] + elements[4] * elements[11] * elements[14] + elements[8] * elements[6] * elements[15] - elements[8] * elements[7] * elements[14] - elements[12] * elements[6] * elements[11] + elements[12] * elements[7] * elements[10];
            out.elements2D[2][0] = elements[4] * elements[9] * elements[15] - elements[4] * elements[11] * elements[13] - elements[8] * elements[5] * elements[15] + elements[8] * elements[7] * elements[13] + elements[12] * elements[5] * elements[11] - elements[12] * elements[7] * elements[9];
            out.elements2D[3][0] = -elements[4] * elements[9] * elements[14] + elements[4] * elements[10] * elements[13] + elements[8] * elements[5] * elements[14] - elements[8] * elements[6] * elements[13] - elements[12] * elements[5] * elements[10] + elements[12] * elements[6] * elements[9];
            out.elements2D[0][1] = -elements[1] * elements[10] * elements[15] + elements[1] * elements[11] * elements[14] + elements[9] * elements[2] * elements[15] - elements[9] * elements[3] * elements[14] - elements[13] * elements[2] * elements[11] + elements[13] * elements[3] * elements[10];
            out.elements2D[1][1] = elements[0] * elements[10] * elements[15] - elements[0] * elements[11] * elements[14] - elements[8] * elements[2] * elements[15] + elements[8] * elements[3] * elements[14] + elements[12] * elements[2] * elements[11] - elements[12] * elements[3] * elements[10];
            out.elements2D[2][1] = -elements[0] * elements[9] * elements[15] + elements[0] * elements[11] * elements[13] + elements[8] * elements[1] * elements[15] - elements[8] * elements[3] * elements[13] - elements[12] * elements[1] * elements[11] + elements[12] * elements[3] * elements[9];
            out.elements2D[3][1] = elements[0] * elements[9] * elements[14] - elements[0] * elements[10] * elements[13] - elements[8] * elements[1] * elements[14] + elements[8] * elements[2] * elements[13] + elements[12] * elements[1] * elements[10] - elements[12] * elements[2] * elements[9];
            out.elements2D[0][2] = elements[1] * elements[6] * elements[15] - elements[1] * elements[7] * elements[14] - elements[5] * elements[2] * elements[15] + elements[5] * elements[3] * elements[14] + elements[13] * elements[2] * elements[7] - elements[13] * elements[3] * elements[6];
            out.elements2D[1][2] = -elements[0] * elements[6] * elements[15] + elements[0] * elements[7] * elements[14] + elements[4] * elements[2] * elements[15] - elements[4] * elements[3] * elements[14] - elements[12] * elements[2] * elements[7] + elements[12] * elements[3] * elements[6];
            out.elements2D[2][2] = elements[0] * elements[5] * elements[15] - elements[0] * elements[7] * elements[13] - elements[4] * elements[1] * elements[15] + elements[4] * elements[3] * elements[13] + elements[12] * elements[1] * elements[7] - elements[12] * elements[3] * elements[5];
            out.elements2D[3][2] = -elements[0] * elements[5] * elements[14] + elements[0] * elements[6] * elements[13] + elements[4] * elements[1] * elements[14] - elements[4] * elements[2] * elements[13] - elements[12] * elements[1] * elements[6] + elements[12] * elements[2] * elements[5];
            out.elements2D[0][3] = -elements[1] * elements[6] * elements[11] + elements[1] * elements[7] * elements[10] + elements[5] * elements[2] * elements[11] - elements[5] * elements[3] * elements[10] - elements[9] * elements[2] * elements[7] + elements[9] * elements[3] * elements[6];
            out.elements2D[1][3] = elements[0] * elements[6] * elements[11] - elements[0] * elements[7] * elements[10] - elements[4] * elements[2] * elements[11] + elements[4] * elements[3] * elements[10] + elements[8] * elements[2] * elements[7] - elements[8] * elements[3] * elements[6];
            out.elements2D[2][3] = -elements[0] * elements[5] * elements[11] + elements[0] * elements[7] * elements[9] + elements[4] * elements[1] * elements[11] - elements[4] * elements[3] * elements[9] - elements[8] * elements[1] * elements[7] + elements[8] * elements[3] * elements[5];
            out.elements2D[3][3] = elements[0] * elements[5] * elements[10] - elements[0] * elements[6] * elements[9] - elements[4] * elements[1] * elements[10] + elements[4] * elements[2] * elements[9] + elements[8] * elements[1] * elements[6] - elements[8] * elements[2] * elements[5];
        
            // Det
            float d = 1.0f / (elements[0] * out.elements[0] + elements[1] * out.elements[4] + elements[2] * out.elements[8] + elements[3] * out.elements[12]);
            out *= d;

            // Retur matrix
            return out;
        }

        // Assign operator
        inline Mat4x4& operator=(const Mat4x4& other) {
            memcpy(this, &other, sizeof(Mat4x4));
            return *this;
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
        inline Mat4x4 operator*(const Mat4x4& other) {
            Mat4x4 out;
            __m3d_sse_matrix_mul(this, &other, &out);
            return out;
        }
        inline Mat4x4& operator*=(const Mat4x4& other) {
            __m3d_sse_matrix_mul(this, &other, this);
            return *this;
        }

        // Vector multiply with matrix
        inline Vec4 operator*(const Vec4& other) {
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
    
    // Translate 
    inline Mat4x4 TranslationMatrix(FLT tx, FLT ty, FLT tz) {
        return {
            1.0f,   0.0f,   0.0f,   tx,
            0.0f,   1.0f,   0.0f,   ty,
            0.0f,   0.0f,   1.0f,   tz,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
    }

    // Rotate around X axis
    inline Mat4x4 XRotationMatrix(FLT rad) {
        // Angels
        FLT vcos = cos(rad);
        FLT vsin = sin(rad);

        // Compose matrix
        return {
            1.0f,   0.0f,   0.0f,   0.0f,
            0.0f,   vcos,  -vsin,   0.0f,
            0.0f,   vsin,   vcos,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
    }

    // Rotate around Y axis
    inline Mat4x4 YRotationMatrix(FLT rad) {
        // Angels
        FLT vcos = cos(rad);
        FLT vsin = sin(rad);

        // Compose matrix
        return {
            vcos,   0.0f,   vsin,   0.0f,
            0.0f,   1.0f,   0.0f,   0.0f,
           -vsin,   0.0f,   vcos,   0.0f,
           0.0f,    0.0f,   0.0f,   1.0f,
        };
    }

    // Rotate around Z axis
    inline Mat4x4 ZRotationMatrix(FLT rad) {
        // Angels
        FLT vcos = cos(rad);
        FLT vsin = sin(rad);

        // Compose matrix
        return {
            vcos,  -vsin,   0.0f,   0.0f,
            vsin,   vcos,   0.0f,   0.0f,
            0.0f,   0.0f,   1.0f,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
    }

    // Non uniform scaling matrix
    inline Mat4x4 ScalingMatrix(FLT sx, FLT sy, FLT sz) {
        return {
            sx,     0.0f,   0.0f,   0.0f,
            0.0f,   sy,     0.0f,   0.0f,
            0.0f,   0.0f,   sz,     0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
    }

    // XY Shearing Matrix
    inline Mat4x4 XYShearingMatrix(FLT s) {
        return {
            1.0f,   s,      0.0f,   0.0f,
            0.0f,   1.0f,   0.0f,   0.0f,
            0.0f,   0.0f,   1.0f,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
    }

    // XZ Shearing Matrix
    inline Mat4x4 XZShearingMatrix(FLT s) {
        return {
            1.0f,   0.0f,   s,      0.0f,
            0.0f,   1.0f,   0.0f,   0.0f,
            0.0f,   0.0f,   1.0f,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
    }

    // YX Shearing Matrix
    inline Mat4x4 YXShearingMatrix(FLT s) {
        return {
            1.0f,   0.0f,   0.0f,   0.0f,
            s,      1.0f,   0.0f,   0.0f,
            0.0f,   0.0f,   1.0f,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
    }

    // YZ Shearing Matrix
    inline Mat4x4 YZShearingMatrix(FLT s) {
        return {
            1.0f,   0.0f,   0.0f,   0.0f,
            0.0f,   1.0f,   s,      0.0f,
            0.0f,   0.0f,   1.0f,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
    }

    // ZX Shearing Matrix
    inline Mat4x4 ZXShearingMatrix(FLT s) {
        return {
            1.0f,   0.0f,   0.0f,   0.0f,
            0.0f,   1.0f,   0.0f,   0.0f,
            s,      0.0f,   1.0f,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
    }

    // ZY Shearing Matrix
    inline Mat4x4 ZYShearingMatrix(FLT s) {
        return {
            1.0f,   0.0f,   0.0f,   0.0f,
            0.0f,   1.0f,   0.0f,   0.0f,
            0.0f,   s,      1.0f,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
    }

    // Euler rotation matrix
    inline Mat4x4 EulerRotationMatrix(FLT roll, FLT pitch, FLT head) {
        // Compute R/P/H sin/cos
        FLT rsin = sin(roll);
        FLT rcos = cos(roll);
        FLT psin = sin(pitch);
        FLT pcos = cos(pitch);
        FLT hsin = sin(head);
        FLT hcos = cos(head);

        // Comose matrix
        return {
            (rcos * hcos) - (rsin * psin * hsin),      -rsin * pcos,        (rcos * hsin) + (rsin * psin * hcos),       0.0f,
            (rsin * hcos) + (rcos * psin * hsin),       rcos * pcos,        (rsin * hsin) - (rcos * psin * pcos),       0.0f,
            -pcos * hsin,                               psin,               pcos * hcos,                                0.0f,
            0.0f,                                       0.0f,               0.0f,                                       1.0f,
        };
    }

    // Goldman rotation
    inline Mat4x4 GoldmanRotationMatrix(const Vec4& axis, FLT angle) {
        // Compute angles
        FLT vsin = sin(angle);
        FLT vcos = cos(angle);

        // Compose matrix
        return {
            vcos + ((1 - vcos) * axis.c_x * axis.c_x),                  ((1 - vcos) * axis.c_x * axis.c_y) - (axis.c_z * vsin),     ((1 - vcos) * axis.c_x * axis.c_z) + (axis.c_y * vsin),     0.0f,
            ((1 - vcos) * axis.c_x * axis.c_y) + (axis.c_z * vsin),     vcos + ((1 - vcos) * axis.c_y * axis.c_y),                  ((1 - vcos) * axis.c_y * axis.c_z) - (axis.c_x * vsin),     0.0f,
            ((1 - vcos) * axis.c_x * axis.c_z) - (axis.c_y * vsin),     ((1 - vcos) * axis.c_y * axis.c_z) + (axis.c_x * vsin),     vcos + ((1 - vcos) * axis.c_z * axis.c_z),                  0.0f,
            0.0f,                                                       0.0f,                                                       0.0f,                                                       1.0f,
        };
    }

    // Mirroring matrix (LH <--> RH)
    inline Mat4x4 ZMirrorMatrix() {
        return {
            1.0f,   0.0f,   0.0f,   0.0f,
            0.0f,   1.0f,   0.0f,   0.0f,
            0.0f,   0.0f,  -1.0f,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
    }

    // Plain Orthographic Projection matrix (z-Plane = 0.0f)
    inline Mat4x4 PlaneOrthographicProjectionMatrix() {
        return {
            1.0f,   0.0f,   0.0f,   0.0f,
            0.0f,   1.0f,   0.0f,   0.0f,
            0.0f,   0.0f,   0.0f,   0.0f,
            0.0f,   0.0f,   0.0f,   1.0f,
        };
    }

    // Orthographic Projection
    inline Mat4x4 OrthographicProjectionMatrix_D3D(float left, float right, float top, float bottom, float nearZ, float farZ) {
        return {
            2.0f / (right - left),      0.0f,                       0.0f,                      -((right + left) / (right - left)),
            0.0f,                       2.0f / (top - bottom),      0.0f,                      -((top + bottom) / (top - bottom)),
            0.0f,                       0.0f,                       1.0f / (farZ - nearZ),     -((nearZ) / (farZ - nearZ)),
            0.0f,                       0.0f,                       0.0f,                       1.0f,
        };
    }
    inline Mat4x4 OrthographicProjectionMatrix_D3D(float width, float height, float nearZ, float farZ) {
        return {
            2.0f / width,               0.0f,                       0.0f,                       0.0f,
            0.0f,                       2.0f / height,              0.0f,                       0.0f,
            0.0f,                       0.0f,                       1.0f / (farZ - nearZ),     -((nearZ) / (farZ - nearZ)),
            0.0f,                       0.0f,                       0.0f,                       1.0f,
        };
    }

    // Perspective projection (hFov in Rad; aspectRation = width / height)
    inline Mat4x4 PerspectiveProjectonMatrix_D3D(float hFov, float aspectRation, float nearZ, float farZ) {
        // Compute |l/r| 
        float hS = nearZ * tanf(0.5f * hFov);
        // Compute |t/b|
        float vS = hS / aspectRation;
        // Composit matrix
        return {
            (2.0f * nearZ) / (2.0f * hS),   0.0f,                           0.0f,                       0.0f,
            0.0f,                           (2.0f * nearZ) / (2.0f * vS),   0.0f,                       0.0f,
            0.0f,                           0.0f,                           farZ / (farZ - nearZ),     -((farZ * nearZ) / (farZ - nearZ)),
            0.0f,                           0.0f,                           1.0f,                       0.0f,
        };
    }
}
