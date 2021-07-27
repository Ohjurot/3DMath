#include <iostream>

#include <3DFloat.h>
#include <3DVector.h>
#include <3DMatrix.h>
#include <3DRand.h>

#include <ctime>

using namespace M3D;

int main(void) {
    // Info
    std::cout << "Loetwig Fusel 3D-Math lib" << std::endl;

    // Matrix
    Mat4x4 m0 = {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        1.0f, 2.0f, 3.0f, 4.0f,
    };
    Vec4 v0 = {1.0f, 2.0f, 3.0f, 4.0f};

    // Matrix add
    Vec4 v1 = m0 * v0;

    return 0;
}
