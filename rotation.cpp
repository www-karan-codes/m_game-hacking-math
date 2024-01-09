#include "math.hpp"

using gamehacking::math::Rotation;

Rotation::Rotation(void) : pitch_(0), yaw_(0), roll_(0)
{
}

Rotation::Rotation(double pitch, double yaw, double roll) : pitch_(pitch), yaw_(yaw), roll_(roll)
{
}

/*
gamehacking::math::Vector3D Rotation::ToVector(void)
{
    float CP, SP, CY, SY;
    SinCos(&SP, &CP, DEG2RAD(pitch_));
    SinCos(&SY, &CY, DEG2RAD(yaw_));
    return gamehacking::math::Vector3D(CP * CY, CP * SY, SP);
}
*/