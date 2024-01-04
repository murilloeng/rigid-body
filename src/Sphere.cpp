//std
#include <cmath>

//rigid
#include "inc/Sphere.hpp"

//canvas
#include "Canvas/lib/inc/Objects/3D/Sphere.hpp"

//constructor
Sphere::Sphere(void) : m_p(1.00e+03), m_r(1.00e+00)
{
	return;
}

//destructor
Sphere::~Sphere(void)
{
	return;
}

//solve
void Sphere::setup(void)
{
	m_J1.zeros();
	m_J2.zeros();
	m_M = 4 * M_PI * m_p * m_r * m_r * m_r / 3;
	m_J2(0, 0) = m_J2(1, 1) = m_J2(2, 2) = 2 * m_M * m_r * m_r / 5;
	Rigid::setup();
}

//results
void Sphere::draw_model(canvas::Scene* scene) const
{
	//data
	canvas::objects::Sphere* sphere = new canvas::objects::Sphere;
	//objects
	sphere->radius(m_r);
	sphere->color_fill("blue");
	//scene
	scene->add_object(sphere);
}