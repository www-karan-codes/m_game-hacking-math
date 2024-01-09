#pragma once

#include <iostream>
#include <cmath>

#include "forward_declaration.hpp"
//#include "declarations.hpp"

#define M_PI 3.14159265358979323846
#define M_PI_F ((float)(M_PI))
#define PI M_PI
#define DEG2RAD(x) ((float)(x) * (float)(M_PI_F / 180.f))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
#define INV_PI (0.31830988618f)
#define HALF_PI (1.57079632679f)

namespace gamehacking::math
{
    void SinCos(float* ScalarSin, float* ScalarCos, float Value);

    struct Rotation;

    struct Vector3D
    {
        enum class Side {kUnknown, kLeft, kRight, kSame};
        Vector3D(void);
        Vector3D(const double x, double y, double z);
        double x_, y_, z_;
        double Magnitude(void) const;
        Vector3D Unit(void);
        Vector3D Normal(void);
        Vector3D operator/(const double&) const;
        Vector3D operator*(const double&) const;
        Vector3D operator+(const Vector3D&) const;
        Vector3D operator-(const Vector3D&) const;
        double DotProduct(const Vector3D&) const;
        Vector3D CrossProduct(const Vector3D&) const;
        double AngleBetweenXY(Vector3D) const;
        static bool IsInFieldOfView(const Vector3D&, const Vector3D&, const Vector3D&);
        Side Orientation(const Vector3D&) const;
        inline friend std::ostream& operator<< (std::ostream& out, const Vector3D& v)
        {
            return out << "x = " << v.x_ << ", y = " << v.y_ << ", z = " << v.z_ << std::endl;
        }

        Vector3D(NAMESPACE::VECTOR&);
        operator NAMESPACE::VECTOR();
        Vector3D operator=(NAMESPACE::VECTOR&);
        
        Vector3D(NAMESPACE::VECTOR2D&);
        Vector3D operator=(NAMESPACE::VECTOR2D&);

        operator ImVec2();
        Vector3D(ImVec2&);
        Vector3D operator=(ImVec2&);

        Rotation ToRotator(void);
    };

    struct Rotation
    {
        Rotation(void);
        Rotation(const double pitch_, double yaw_, double roll_);
        double pitch_, yaw_, roll_;
        Vector3D ToVector(void);

        operator NAMESPACE::ROTATOR();
        Rotation(NAMESPACE::ROTATOR&);
        Rotation operator=(NAMESPACE::ROTATOR&);
    };

    struct ViewMatrix {
        ViewMatrix();
        ViewMatrix(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23);

        float* operator[](int i);

        float m_flMatVal[3][4];
    };
}