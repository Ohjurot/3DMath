#pragma once

#define M3D_FLT_EPSILON 0.000001f
#define M3D_FLT4_ALLIGN (sizeof(M3D::FLT) * 4)

#define M3D_PI 3.1415927f


namespace M3D {
    // Plain float type
    typedef float FLT;

    // Angle conversions
    inline FLT DegreeToRadian(FLT deg) {
        return deg * M3D_PI / 180;
    }
    inline FLT RadianToDegree(FLT rad) {
        return rad * 180 / M3D_PI;
    }

    // Feature struct
    struct CPU_FEATURES {
        bool RandomSupport = false;
        bool VektorSupport = false;
        bool MatrixSupport = false;
    };
}
