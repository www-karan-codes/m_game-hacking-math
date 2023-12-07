#include <iostream>
#include <cmath>

namespace gamehacking::math
{
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
        bool IsInFieldOfView(const Vector3D&) const;
        Side Orientation(const Vector3D&) const;
        friend std::ostream& operator<< (std::ostream &out, const Vector3D&);
    };
}