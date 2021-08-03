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
        1.0f, 7.0f, 14.0f, 0.0f,
        9.0f, 4.0f, 18.0f, 18.0f,
        2.0f, 4.0f, 5.0f, 5.0f,
        1.0f, 7.0f, 1.0f, 11.0f,
    };

    auto inv = m0.ninverse();

    return 0;
}
