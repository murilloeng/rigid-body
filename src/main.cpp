//std
#include <cmath>
#include <cstdio>

//rigid
#include "inc/Sphere.hpp"
#include "inc/Pyramid.hpp"
#include "inc/Cylinder.hpp"

void sphere_1(void)
{
	Sphere sphere;
	sphere.m_steps = 2000;
	sphere.m_dt = 1.25e-02;
	sprintf(sphere.m_label, "sphere_1");
	math::quat(sphere.m_state_old) = {1, 0, 0, 0};
	math::vec3(sphere.m_velocity_old) = {0, 0, 1};
	sphere.setup();
	sphere.solve();
	sphere.finish();
	sphere.draw(10);
}

void cylinder_1(void)
{
	Cylinder cylinder;
	cylinder.m_steps = 2000;
	cylinder.m_dt = 1.25e-02;
	sprintf(cylinder.m_label, "cylinder_1");
	math::quat(cylinder.m_state_old) = {1, 0, 0, 0};
	math::vec3(cylinder.m_velocity_old) = {0, 0, 1};
	cylinder.setup();
	cylinder.solve();
	cylinder.finish();
	cylinder.draw(10);
}

void pyramid_1(void)
{
	Pyramid pyramid;
	pyramid.m_steps = 2000;
	pyramid.m_dt = 1.25e-02;
	sprintf(pyramid.m_label, "pyramid_1");
	math::quat(pyramid.m_state_old) = {1, 0, 0, 0};
	math::vec3(pyramid.m_velocity_old) = {0, 0, 1};
	pyramid.setup();
	pyramid.solve();
	pyramid.finish();
	pyramid.draw(10);
}
void pyramid_2(void)
{
	Pyramid pyramid;
	pyramid.m_steps = 10000;
	pyramid.m_dt = 5.00e-02;
	sprintf(pyramid.m_label, "pyramid_2");
	math::quat(pyramid.m_state_old) = {1, 0, 0, 0};
	math::vec3(pyramid.m_velocity_old) = {1e-5, 1, 0};
	pyramid.setup();
	pyramid.solve();
	pyramid.finish();
	pyramid.draw(50);
}

int main(void)
{
	//test
	pyramid_2();
	//return
	return 0;
}