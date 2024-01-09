#include "../Math/math.hpp"

namespace gamehacking::math
{
	float* ViewMatrix::operator[](int i) {
		return m_flMatVal[i];
	}

    ViewMatrix::ViewMatrix() {}
    ViewMatrix::ViewMatrix(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23) {
        m_flMatVal[0][0] = m00;
        m_flMatVal[0][1] = m01;
        m_flMatVal[0][2] = m02;
        m_flMatVal[0][3] = m03;
        m_flMatVal[1][0] = m10;
        m_flMatVal[1][1] = m11;
        m_flMatVal[1][2] = m12;
        m_flMatVal[1][3] = m13;
        m_flMatVal[2][0] = m20;
        m_flMatVal[2][1] = m21;
        m_flMatVal[2][2] = m22;
        m_flMatVal[2][3] = m23;
    }
}