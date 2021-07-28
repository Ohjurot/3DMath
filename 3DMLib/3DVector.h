#pragma once

#include "3DMath.h"
#include "3DVector_sse.h"

#include <sstream>
#include <iomanip>

namespace M3D {
    // 4 Component vector
    struct alignas(M3D_FLT4_ALLIGN) Vec4 {
        union {
            FLT elements[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
            struct {
                // Comonent 0
                union {
                    FLT x;
                    const FLT c_x;
                    FLT r;
                    const FLT c_r;
                };
                // Comonent 1
                union {
                    FLT y;
                    const FLT c_y;
                    FLT g;
                    const FLT c_g;
                };
                // Comonent 2
                union {
                    FLT z;
                    const FLT c_z;
                    FLT b;
                    const FLT c_b;
                };
                // Comonent 3
                union {
                    FLT w;
                    const FLT c_w;
                    FLT a;
                    const FLT c_a;
                };
            };
        };

        // Normalize
        inline void normalize() {
            __m3d_sse_vector_normalize(this, this);
        }
        inline Vec4 nnormalize() const {
            Vec4 vec;
            __m3d_sse_vector_normalize(this, &vec);
            return vec;
        }
        // Vector length
        inline float length() const {
            return __m3d_sse_vector_length(this);
        }
        // Dot product
        inline float dot(const Vec4& other) const {
            return __m3d_sse_vector_dot(this, &other);
        }
        // Cross product
        inline void cross(const Vec4& other) {
            __m3d_sse_vector_cross(this, &other, this);
        }
        inline Vec4 ncross(const Vec4& other) const {
            Vec4 out;
            __m3d_sse_vector_cross(this, &other, &out);
            return out;
        }

        // States
        inline bool isPoint() const {
            return w == 1.0f;
        }
        inline bool isVector() const {
            return w == 0.0f;
        }

        // Assign operator
        inline Vec4& operator=(const Vec4& other) {
            memcpy(this, &other, sizeof(Vec4));
            return *this;
        }

        // Vec4 * Vec4
        inline Vec4 operator+(const Vec4& other) {
            Vec4 out;
            __m3d_sse_vector_add_cw(this, &other, &out);
            return out;
        }
        inline Vec4& operator+=(const Vec4& other) {
            __m3d_sse_vector_add_cw(this, &other, this);
            return *this;
        }
        // Vec4 + FLT
        inline Vec4 operator+(FLT value) {
            Vec4 out;
            __m3d_sse_vector_add_sc(value, this, &out);
            return out;
        }
        inline Vec4& operator+=(FLT value) {
            __m3d_sse_vector_add_sc(value, this, this);
            return *this;
        }
        // Vec4 - Vec4
        inline Vec4 operator-(const Vec4& other) {
            Vec4 out;
            __m3d_sse_vector_sub_cw(this, &other, &out);
            return out;
        }
        inline Vec4& operator-=(const Vec4& other) {
            __m3d_sse_vector_sub_cw(this, &other, this);
            return *this;
        }
        // Vec4 - FLT
        inline Vec4 operator-(FLT value) {
            Vec4 out;
            __m3d_sse_vector_sub_sc(value, this, &out);
            return out;
        }
        inline Vec4& operator-=(FLT value) {
            __m3d_sse_vector_sub_sc(value, this, this);
            return *this;
        }
        // Vec4 * Vec4
        inline Vec4 operator*(const Vec4& other) {
            Vec4 out;
            __m3d_sse_vector_mul_cw(this, &other, &out);
            return out;
        }
        inline Vec4& operator*=(const Vec4& other) {
            __m3d_sse_vector_mul_cw(this, &other, this);
            return *this;
        }
        // Vec4 * FLT
        inline Vec4 operator*(FLT value) {
            Vec4 out;
            __m3d_sse_vector_mul_sc(value, this, &out);
            return out;
        }
        inline Vec4& operator*=(FLT value) {
            __m3d_sse_vector_mul_sc(value, this, this);
            return *this;
        }
        // Vec4 / Vec4
        inline Vec4 operator/(const Vec4& other) {
            Vec4 out;
            __m3d_sse_vector_div_cw(this, &other, &out);
            return out;
        }
        inline Vec4& operator/=(const Vec4& other) {
            __m3d_sse_vector_div_cw(this, &other, this);
            return *this;
        }
        // Vec4 / FLT
        inline Vec4 operator/(FLT value) {
            Vec4 out;
            __m3d_sse_vector_div_sc(value, this, &out);
            return out;
        }
        inline Vec4& operator/=(FLT value) {
            __m3d_sse_vector_div_sc(value, this, this);
            return *this;
        }

    };

    // Left side float
    inline Vec4& operator+(FLT f, const Vec4& vec) {
        Vec4 out;
        __m3d_sse_vector_add_sc(f, &vec, &out);
        return out;
    }
    inline Vec4& operator-(FLT f, const Vec4& vec) {
        Vec4 out;
        __m3d_sse_vector_sub_sc(f, &vec, &out);
        return out;
    }
    inline Vec4& operator*(FLT f, const Vec4& vec) {
        Vec4 out;
        __m3d_sse_vector_mul_sc(f, &vec, &out);
        return out;
    }
    inline Vec4& operator/(FLT f, const Vec4& vec) {
        Vec4 out;
        __m3d_sse_vector_div_sc(f, &vec, &out);
        return out;
    }

    // Serialize
    std::ostream& operator<<(std::ostream& outStream, const Vec4& vec) {
        // Stream out
        outStream << "(X=" << vec.c_x << ", Y=" << vec.c_y << ", Z=" << vec.c_z << ", W=" << vec.c_w << ")";
        // Return 
        return outStream;
    }

    // Creators
    inline Vec4 MakePoint(FLT x, FLT y, FLT z) {
        return {
            x, y, z, 1.0f,
        };
    }
    inline Vec4 MakeVector(FLT x, FLT y, FLT z) {
        return {
            x, y, z, 0.0f,
        };
    }

    // Vector mad
    inline Vec4 VectorMultiplyAndAdd(const Vec4& mul0, const Vec4& mul1, const Vec4& add) {
        Vec4 out;
        __m3d_sse_vector_mad(&mul0, &mul1, &add, &out);
        return out;
    }

    // Angel between vectors
    inline FLT VectorAngleCosTheta(const Vec4& vec0, const Vec4& vec1) {
        return vec0.dot(vec1) / (vec0.length() * vec1.length());
    }
    inline FLT VectorAngelTheta(const Vec4& vec0, const Vec4& vec1) {
        return acos(VectorAngleCosTheta(vec0, vec1));
    }
}
