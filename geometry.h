#include <iostream>
#ifndef GEOMETRY_H
#define GEOMETRY_H

//declaring 3d vector first as 2d cross product produces 3d
template<typename t>
class Vec3 {
public:
    t x, y, z;

    Vec3(t _x=0, t _y=0, t _z=0);
    t& operator[] (int);
    Vec3 operator+ (const Vec3&) const;
    Vec3 operator- (const Vec3&) const;
    t operator* (const Vec3&) const;
    Vec3 operator^ (const Vec3&) const;
    Vec3 operator* (float) const;
    t norm() const;
    void normalize();

    friend std::ostream& operator<< (std::ostream& os, const Vec3<t>& v) {
        return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    }
};

typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;

template<typename t>
class Vec2 {
public:
    t x, y;

    Vec2(t _x=0, t _y=0);
    t& operator[] (int);
    Vec2 operator+ (const Vec2&) const;
    Vec2 operator- (const Vec2&) const;
    t operator* (const Vec2&) const;
    Vec3<t> operator^ (const Vec2&) const;
    Vec2 operator* (float) const;
    t norm() const;
    void normalize();

    friend std::ostream& operator<< (std::ostream& os, const Vec2<t>& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }
};

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;

class FourFourMatrix {
public:
    float elements[16];

    FourFourMatrix(float[16]);
    float operator[] (int) const;
    FourFourMatrix operator* (const FourFourMatrix&) const;
    Vec3f pointMul (const Vec3f&) const;
};

class TwoTwoMatrix {
public:
    float elements[4];

    TwoTwoMatrix(float[4]);
    Vec2f pointMul (const Vec2f&) const;
};

#endif
