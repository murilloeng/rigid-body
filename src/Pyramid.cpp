//rigid
#include "rigid-body/inc/Pyramid.hpp"

//canvas
#include "Canvas/inc/Objects/2D/Triangle.hpp"

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
	m_l = 3 * m_h / 4;
	m_M = m_p * m_a * m_b * m_h / 3;
	m_J2(2, 2) = m_M * (m_a * m_a + m_b * m_b) / 20;
	m_J2(0, 0) = m_M * (4 * m_b * m_b + 3 * m_h * m_h) / 80;
	m_J2(1, 1) = m_M * (4 * m_a * m_a + 3 * m_h * m_h) / 80;
	Top::setup();
}

//results
void Pyramid::draw_model(canvas::Scene* scene) const
{
	//data
	const canvas::vec3 p0 = {0, 0, -3 * float(m_h) / 4};
	canvas::objects::Triangle* t1 = new canvas::objects::Triangle;
	canvas::objects::Triangle* t2 = new canvas::objects::Triangle;
	canvas::objects::Triangle* t3 = new canvas::objects::Triangle;
	canvas::objects::Triangle* t4 = new canvas::objects::Triangle;
	canvas::objects::Triangle* t5 = new canvas::objects::Triangle;
	canvas::objects::Triangle* t6 = new canvas::objects::Triangle;
	const canvas::vec3 p1 = {-float(m_a) / 2, -float(m_b) / 2, float(m_h) / 4};
	const canvas::vec3 p2 = {+float(m_a) / 2, -float(m_b) / 2, float(m_h) / 4};
	const canvas::vec3 p3 = {+float(m_a) / 2, +float(m_b) / 2, float(m_h) / 4};
	const canvas::vec3 p4 = {-float(m_a) / 2, +float(m_b) / 2, float(m_h) / 4};
	//objects
	t1->color_fill("blue");
	t2->color_fill("blue");
	t3->color_fill("blue");
	t4->color_fill("blue");
	t5->color_fill("blue");
	t6->color_fill("blue");
	t1->point(0, p0), t1->point(1, p1), t1->point(2, p2);
	t2->point(0, p0), t2->point(1, p2), t2->point(2, p3);
	t3->point(0, p0), t3->point(1, p3), t3->point(2, p4);
	t4->point(0, p0), t4->point(1, p4), t4->point(2, p1);
	t5->point(0, p1), t5->point(1, p2), t5->point(2, p3);
	t6->point(0, p1), t6->point(1, p3), t6->point(2, p4);
	//scene
	scene->add_object(t1);
	scene->add_object(t2);
	scene->add_object(t3);
	scene->add_object(t4);
	scene->add_object(t5);
	scene->add_object(t6);
}