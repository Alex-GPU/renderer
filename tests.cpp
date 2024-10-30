#include <iostream>
#include "geometry.h"

int main(int argc, char** argv) {
    //test vec3
    Vec3f v0, v1(1,1,1);
    Vec3i v2(2,2);
    std::cout << "v0 by default is " << v0;
    std::cout << "\nv1 is " << v1;
    std::cout << "\nv2 is " << v2;

    Vec2f v3, v4(1,1);
    Vec2i v5(2);
    std::cout << "\nv3 by default is " << v3;
    std::cout << "\nv4 is " << v4;
    std::cout << "\nv5 is " << v5;
}
