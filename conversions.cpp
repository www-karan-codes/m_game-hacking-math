#include "math.hpp"
#include "forward_declaration.hpp"
#include "declarations.hpp"
#include "../ImGui/imgui.h"

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

Vector3D::operator ImVec2()
{
	ImVec2 vector;
	vector.x = x_;
	vector.y = y_;
	return vector;
}

Vector3D::Vector3D(ImVec2& v)
{
	x_ = v.x;
	y_ = v.y;
	z_ = 0;
}

Vector3D Vector3D::operator=(ImVec2& v)
{
	return Vector3D(v.x, v.y, 0);
}