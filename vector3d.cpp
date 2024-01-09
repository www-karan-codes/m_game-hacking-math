#include "math.hpp"
#include <algorithm>

using gamehacking::math::Vector3D;

Vector3D::Vector3D(void) : x_(0), y_(0), z_(0)
{
}

Vector3D::Vector3D(double x, double y, double z) : x_(x), y_(y), z_(z)
{
}

double Vector3D::Magnitude(void) const
{
    return sqrt(x_*x_ + y_*y_ + z_*z_);
}

Vector3D Vector3D::Unit(void)
{
    auto magnitude = this->Magnitude();
    return *this / magnitude;
}

Vector3D Vector3D::operator/(const double& div) const
{
    return Vector3D(x_/div, y_/div, z_/div);
}

Vector3D Vector3D::operator*(const double& mul) const
{
    return *this/(1/mul);
}

Vector3D Vector3D::operator+(const Vector3D& v) const
{
    return Vector3D(x_ + v.x_, y_ + v.y_, z_ + v.z_);
}

Vector3D Vector3D::operator-(const Vector3D& v) const
{
    return *this + (v * -1);
}

double Vector3D::DotProduct(const Vector3D& v) const
{
    return (x_ * v.x_) + (y_ * v.y_) + (z_ * v.z_);
}

Vector3D Vector3D::CrossProduct(const Vector3D& v) const
{
    return Vector3D((y_ * v.z_) - (z_ * v.y_), (z_ * v.x_) - (x_ * v.z_), (x_ * v.y_) - (y_ * v.x_));
}

Vector3D::Side Vector3D::Orientation(const Vector3D& v) const
{
    auto u = *this;
    static auto up = Vector3D(0,0,1);
    Vector3D right = u.CrossProduct(up);

    auto dot_product = right.DotProduct(v);

    if (dot_product == 0)
    {
        return Side::kSame;
    } else if (dot_product < 0)
    {
        return Side::kRight;
    } else if (dot_product > 0)
    {
        return Side::kLeft;
    } else
    {
        return Side::kUnknown;
    }
}

double Vector3D::AngleBetweenXY(Vector3D v) const
{
    auto u = *this;
    u.z_ = 0;
    v.z_ = 0;

    auto dot = u.DotProduct(v);
    auto denom = u.Magnitude() * v.Magnitude();
    auto div = dot / denom;
    div = std::clamp(div, -1.0, 1.0);
    return acos(div);
}

bool Vector3D::IsInFieldOfView(const Vector3D& location, const Vector3D& direction, const Vector3D& location_to_check)
{
    auto rotation_vector = direction;
    auto difference_vector = location_to_check - location;
    rotation_vector.z_ = 0;
    difference_vector.z_ = 0;

    auto dot_product = rotation_vector.DotProduct(difference_vector);
    if (dot_product <= 0)      // dot is > 0 if vectors face same direction, 0 if vectors perpendicular, negative if facing oppposite directions
        return false;  // we want to ensure the vectors face in the same direction
    return true;
}