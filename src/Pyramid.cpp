//rigid
#include "inc/Pyramid.hpp"

//constructor
Pyramid::Pyramid(void) : m_p(1.00e+03), m_a(1.00e+00), m_b(2.00e+00), m_h(1.00e+00)
{
	return;
}

//destructor
Pyramid::~Pyramid(void)
{
	return;
}

//solve
void Pyramid::setup(void)
{
	m_J1.zeros();
	m_J2.zeros();
	m_M = m_p * m_a * m_b * m_h / 3;
	m_J1(0, 1) = +3 * m_M * m_h / 4;
	m_J1(1, 0) = -3 * m_M * m_h / 4;
	m_J2(2, 2) = m_M * (m_a * m_a + m_b * m_b) / 20;
	m_J2(0, 0) = m_M * (m_b * m_b + 12 * m_h * m_h) / 20;
	m_J2(1, 1) = m_M * (m_a * m_a + 12 * m_h * m_h) / 20;
	Rigid::setup();
}