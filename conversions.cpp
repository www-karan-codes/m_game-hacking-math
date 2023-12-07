#include "math.hpp"
#include "forward_declaration.hpp"
#include "declarations.hpp"

using gamehacking::math::Vector3D;

Vector3D::operator NAMESPACE::VECTOR()
{
	NAMESPACE::VECTOR vector;
	vector.X = x_;
	vector.Y = y_;
	vector.Z = z_;
	return vector;
}

Vector3D::Vector3D(NAMESPACE::VECTOR& v)
{
	x_ = v.X;
	y_ = v.Y;
	z_ = v.Z;
}

Vector3D Vector3D::operator=(NAMESPACE::VECTOR& v)
{
	return Vector3D(v.X, v.Y, v.Z);
}