//std
#include <cmath>

//rigid
#include "rigid-body/inc/Cylinder.hpp"

//canvas
#include "Canvas/inc/Objects/3D/Cylinder.hpp"

//constructor
Cylinder::Cylinder(void) : m_p(1.00e+03), m_r(1.00e+00), m_h(1.00e+00)
{
	return;
}

//destructor
Cylinder::~Cylinder(void)
{
	return;
}

//solve
void Cylinder::setup(void)
{
	m_J1.zeros();
	m_J2.zeros();
	m_l = m_h / 2;
	m_M = M_PI * m_p * m_r * m_r * m_h;
	m_J2(2, 2) = m_M * m_r * m_r / 2;
	m_J2(0, 0) = m_J2(1, 1) = m_M * (m_h * m_h + 3 * m_r * m_r) / 12;
	Rigid::setup();
}

//results
void Cylinder::draw_model(canvas::Scene* scene) const
{
	//data
	canvas::objects::Cylinder* cylinder = new canvas::objects::Cylinder;
	//objects
	cylinder->radius(m_r);
	cylinder->height(m_h);
	cylinder->color_fill("blue");
	//scene
	scene->add_object(cylinder);
}