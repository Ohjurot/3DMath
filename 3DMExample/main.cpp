#include <iostream>

#include <3DFloat.h>
#include <3DVector.h>

using namespace M3D;

int main(void) {
    // Info
    std::cout << "Loetwig Fusel 3D-Math lib" << std::endl;

    Vec4 vI = M3D_MakeVektor(1.0f, 0.0f, 0.0f);
    vI.normalize();
    return 0;
}
