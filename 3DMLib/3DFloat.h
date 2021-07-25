#pragma once

#include "3DMath.h"

#include <cmath>

namespace M3D {
    // Floatingpoint class
    struct Float {
        // Inner value
        FLT _value = 0.0f;

        // Construct
        Float() = default;
        Float(const Float& other) = default;
        inline Float(FLT v) {
            _value = v;
        }

        // Auto convert
        inline operator FLT() const{
            return _value;
        }

        // Assign
        inline Float& operator=(FLT v) {
            _value = v;
            return *this;
        }
        Float& operator=(const Float& other) = default;

        // Compare (eqal)
        inline bool operator==(FLT other) {
            return fabs(*this - other) <= M3D_FLT_EPSILON;
        }
        inline bool operator==(const Float& other) {
            return fabs(*this - other) <= M3D_FLT_EPSILON;
        }

    };
}
