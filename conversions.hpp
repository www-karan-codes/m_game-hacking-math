#pragma once

namespace gamehacking::math
{
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
		x_ = v.X;
		y_ = v.Y;
		z_ = v.Z;
		return *this;
	}

	Rotation::operator NAMESPACE::ROTATOR()
	{
		NAMESPACE::ROTATOR rotator;
		rotator.Pitch = pitch_;
		rotator.Yaw = yaw_;
		rotator.Roll = roll_;
		return rotator;
	}

	Rotation::Rotation(NAMESPACE::ROTATOR& r)
	{
		pitch_ = r.Pitch;
		yaw_ = r.Yaw;
		roll_ = r.Roll;
	}

	Rotation Rotation::operator=(NAMESPACE::ROTATOR& r)
	{
		pitch_ = r.Pitch;
		yaw_ = r.Yaw;
		roll_ = r.Roll;
		return *this;
	}
}