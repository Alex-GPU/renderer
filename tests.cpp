// test, thus no comment

#include <iostream>
#include <algorithm>
#include "geometry.h"
#include "draw.h"
#include "io.h"

Vec3f v3f[] = {Vec3f(), Vec3f(1.1f,1.1f,1.1f), Vec3f(2.2f, 1.5f), Vec3f(3.5f, 4.f, 5.f)};
Vec2f v2f[] = {Vec2f(), Vec2f(1.1f,1.1f), Vec2f(0.5f), Vec2f(3.f, 4.f)};

template<typename vecType0, typename vecType1, typename returnType>
inline void compute(const vecType0& v0, const vecType1& v1,
                    returnType (vecType0::*opr)(const vecType1&) const, const char* oprSym) {
    std::cout << "\n" << v0 << " " << oprSym << " " << v1 << " = " << (v0.*opr)(v1);
}

void testConstructor() {
    std::cout << "v30 by default is " << v3f[0]
            << "\nv31 is " << v3f[1]
            << "\nv32 is " << v3f[2]
            << "\nv20 by default is " << v2f[0]
            << "\nv21 is " << v2f[1]
            << "\nv22 is " << v2f[2];
}

void testComputation() {
    for(int i=0; i<sizeof(v3f)/sizeof(v3f[0]) - 1; i++) {
        compute(v3f[i], v3f[i+1], &Vec3f::operator+, "+");
        compute(v3f[i], v3f[i+1], &Vec3f::operator-, "-");
        compute(v3f[i], v3f[i+1], &Vec3f::operator*, "*");
        compute(v3f[i], v3f[i+1], &Vec3f::operator^, "^");
        compute(v3f[i], 0.5f, &Vec3f::operator*, "*");
        std::cout << "\n";

        compute(v2f[i], v2f[i+1], &Vec2f::operator+, "+");
        compute(v2f[i], v2f[i+1], &Vec2f::operator-, "-");
        compute(v2f[i], v2f[i+1], &Vec2f::operator*, "*");
        compute(v2f[i], v2f[i+1], &Vec2f::operator^, "^");
        compute(v2f[i], 0.5f, &Vec2f::operator*, "*");
        std::cout << "\n";
    }
}

void testNorm() {
    for(int i=0; i<sizeof(v3f)/sizeof(v3f[0]); i++) {
        std::cout << "\n" << v3f[i] << " norm = " << v3f[i].norm();
        v3f[i].normalize();
        std::cout << ", " << v3f[i] << " normalized norm = " << v3f[i].norm();

        std::cout << "\n" << v2f[i] << " norm = " << v2f[i].norm();
        v2f[i].normalize();
        std::cout << ", " << v2f[i] << " normalized norm = " << v2f[i].norm();
    }
}

void testFFMatrix() {
    float elems[16] = {1.2f, 2.3f, 3.4f, 4.5f,
                       5.f, 6.f, 7.f, 8.f,
                       9.f, 10.f, 11.f, 12.f,
                       2.f, 2.f, 2.f, 2.f};
    FourFourMatrix ffmtxs[] = {FourFourMatrix(), FourFourMatrix(elems)};
    //std::cout << ffmtxs[0] << ffmtxs[1] << ffmtxs[0]*ffmtxs[1] << ffmtxs[1]*ffmtxs[1];
    for(int i=0; i<sizeof(v3f)/sizeof(v3f[0]); i++) {
        std::cout << "\n" << ffmtxs[1] << " * " << v3f[i] << " = " << ffmtxs[1].pointMul(v3f[i]);
    }
}

void testTTMatrix() {
    float elems[4] = {0.5f, 2.2f, 3.f, 4.1f};
    TwoTwoMatrix mtxs[] = {TwoTwoMatrix(), TwoTwoMatrix(elems)};
    for(int i=0; i<sizeof(v3f)/sizeof(v3f[0]); i++) {
        std::cout << "\n" << mtxs[1] << " * " << v2f[i] << " = " << mtxs[1].pointMul(v2f[i]);
    }
}

void testWireTriangle() {
    const int width{400}, height{400}, x0(200), y0(200), x1(210), y1(200), x2(205), y2(205);
    int xmin = std::min({x0, x1, x2});
    int ymin = std::min({y0, y1, y2});
    int xmax = std::max({x0, x1, x2});
    int ymax = std::max({y0, y1, y2});
    Vec3i image[width*height] = {0.f};
    Vec3i white(255, 255, 255);
    Vec2i v0(x0, y0), v1(x1, y1), v2(x2, y2);
    wireTriangle(v0, v1, v2, image, width, height);
    for (int i=ymin; i<=ymax; i++) {
        std::cout << "\n";
        for (int j=xmin; j<=xmax; j++) {
            std::cout << image[i*width+j] << " ";
        }
    }
}

int main(int argc, char** argv) {
    //test vector constructor
    //testConstructor();

    //test vector computation
    //testComputation();
    
    //test normalization
    //testNorm();

    //test four by four matrix
    //testFFMatrix();

    //test two by two matrix
    //testTTMatrix();

    //test draw triangle
    //testWireTriangle();
    
    //test io
    const int width{400}, height{400}, x0(100), y0(100), x1(300), y1(100), x2(200), y2(300);
    Vec3i image[width*height];
    //for (int i=0; i<100; i++) {std::cout << image[i] << "\n";}
    Vec3i white(255, 255, 255);
    Vec2i v0(x0, y0), v1(x1, y1), v2(x2, y2);
    wireTriangle(v0, v1, v2, image, width, height);
    saveToFile(image, width, height);

    return 0;    
}
