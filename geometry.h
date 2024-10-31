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
    Vec3<float> operator* (const float&) const;
    float norm() const;
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
    Vec2<float> operator* (const float&) const;
    float norm() const;
    void normalize();

    friend std::ostream& operator<< (std::ostream& os, const Vec2<t>& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }
};

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;

class FourFourMatrix {
public:
    float elements[16]={0.f};

    FourFourMatrix();
    FourFourMatrix(float[16]);
    float operator[] (int) const;
    FourFourMatrix operator* (const FourFourMatrix&) const;
    Vec3f pointMul (const Vec3f&) const;
    friend std::ostream& operator<< (std::ostream& os, const FourFourMatrix& m) {
        for(int i=0; i<4; i++) {
            os << "\n[";
            for(int j=0; j<4; j++) {
                os << m.elements[i*4+j] << " ";
            }
            os << "\b]";
        }
        return os << "\n";
    }
};

class TwoTwoMatrix {
public:
    float elements[4]={0.f};

    TwoTwoMatrix();
    TwoTwoMatrix(float[4]);
    float operator[] (int) const;
    Vec2f pointMul (const Vec2f&) const;
    friend std::ostream& operator<< (std::ostream& os, const TwoTwoMatrix& m) {
        return os << "\n[" << m[0] << " " << m[1]
                << "]\n[" << m[2] << " " << m[3] << "]";
    }
};

#endif
