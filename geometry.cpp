#include <cmath>
#include "geometry.h"

template class Vec3<float>;
template class Vec3<int>;
template class Vec2<float>;
template class Vec2<int>;

template <typename t>
Vec3<t>::Vec3(t _x, t _y, t _z): x((t)_x), y((t)_y), z((t)_z) {}

template <typename t>
t& Vec3<t>::operator[] (int i) {return *(&x + i);}

template <typename t>
Vec3<t> Vec3<t>::operator+ (const Vec3& v) const {
    return Vec3<t>(x+v.x, y+v.y, z+v.z);
}

template <typename t>
Vec3<t> Vec3<t>::operator- (const Vec3& v) const {
    return Vec3<t>(x-v.x, y-v.y, z-v.z);
}

template <typename t>
t Vec3<t>::operator* (const Vec3& v) const {
    return x*v.x + y*v.y + z*v.z;
}

template <typename t>
Vec3<t> Vec3<t>::operator^ (const Vec3& v) const {
    return Vec3<t>(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

template <typename t>
Vec3<t> Vec3<t>::operator* (float f) const {
    return Vec3<t>(x*f, y*f, z*f);
}

template <typename t>
t Vec3<t>::norm() const {
    return std::sqrt(x*x + y*y + z*z);
}

template <typename t>
void Vec3<t>::normalize() {
    t n = norm();
    x /= n;
    y /= n;
    z /= n;
}

template <typename t>
Vec2<t>::Vec2(t _x, t _y): x((t)_x), y((t)_y) {}

template <typename t>
t& Vec2<t>::operator[] (int i) {return *(&x+i);}

template <typename t>
Vec2<t> Vec2<t>::operator+ (const Vec2& v) const {
    return Vec2<t>(x+v.x, y+v.y);
}

template <typename t>
Vec2<t> Vec2<t>::operator- (const Vec2& v) const {
    return Vec2<t>(x-v.x, y-v.y);
}

template <typename t>
t Vec2<t>::operator* (const Vec2& v) const {
    return x*v.x + y*v.y;
}

template <typename t>
Vec3<t> Vec2<t>::operator^ (const Vec2& v) const {
    return Vec3<t>(0, 0, x*v.y - y*v.x);
}

template <typename t>
Vec2<t> Vec2<t>::operator* (float f) const {
    return Vec2<t>(x*f, y*f);
}

template <typename t>
t Vec2<t>::norm() const {
    return std::sqrt(x*x + y*y);
}

template <typename t>
void Vec2<t>::normalize() {
    t n = norm();
    x /= n;
    y /= n;
}

FourFourMatrix::FourFourMatrix(float elems[16]) {
    for (int i=0; i<16; i++) {
        elements[i] = elems[i];
    }
}

float FourFourMatrix::operator[] (int i) const {
    return elements[i];
}

FourFourMatrix FourFourMatrix::operator* (const FourFourMatrix& m) const {
    float result[16];
    int row, column;
    for (int i=0; i<16; i++) {
        row = i / 4;
        column = i % 4;
        result[i] = elements[row*4]*m[column] + elements[row*4+1]*m[column+4] +
                    elements[row*4+2]*m[column+8] + elements[row*4+3]*m[column+12];
    }

    return FourFourMatrix(result);
}

Vec3f FourFourMatrix::pointMul(const Vec3f& v) const {
    // the last row of the matrix has no useful info
    // the point is implicitly converted to a 4*1 vector
    return Vec3f(elements[0]*v.x + elements[1]*v.y + elements[2]*v.z + elements[3],
                 elements[4]*v.x + elements[5]*v.y + elements[6]*v.z + elements[7],
                 elements[8]*v.x + elements[9]*v.y + elements[10]*v.z + elements[11]);
}

TwoTwoMatrix::TwoTwoMatrix(float elems[4]) {
    elements[0] = elems[0];
    elements[1] = elems[1];
    elements[2] = elems[2];
    elements[3] = elems[3];
}

Vec2f TwoTwoMatrix::pointMul(const Vec2f& v) const {
    return Vec2f(elements[0]*v.x + elements[1]*v.y, elements[2]*v.x + elements[3]*v.y);
}
