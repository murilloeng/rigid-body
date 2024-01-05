//std
#include <cmath>
#include <cstdio>

//rigid
#include "inc/Sphere.hpp"
#include "inc/Pyramid.hpp"
#include "inc/Cylinder.hpp"

void sphere_uniform(void)
{
	Sphere sphere;
	sphere.m_steps = 2000;
	sphere.m_dt = 1.25e-02;
	sprintf(sphere.m_label, "sphere_uniform");
	math::quat(sphere.m_state_old) = {1, 0, 0, 0};
	math::vec3(sphere.m_velocity_old) = {0, 0, 1};
	sphere.setup();
	sphere.solve();
	sphere.finish();
	sphere.draw(10);
}

void cylinder_uniform(void)
{
	Cylinder cylinder;
	cylinder.m_steps = 2000;
	cylinder.m_dt = 1.25e-02;
	sprintf(cylinder.m_label, "cylinder_uniform");
	math::quat(cylinder.m_state_old) = {1, 0, 0, 0};
	math::vec3(cylinder.m_velocity_old) = {0, 0, 1};
	cylinder.setup();
	cylinder.solve();
	cylinder.finish();
	cylinder.draw(10);
}

void pyramid_uniform(void)
{
	Pyramid pyramid;
	pyramid.m_steps = 2000;
	pyramid.m_dt = 1.25e-02;
	sprintf(pyramid.m_label, "pyramid_uniform");
	math::quat(pyramid.m_state_old) = {1, 0, 0, 0};
	math::vec3(pyramid.m_velocity_old) = {0, 0, 1};
	pyramid.setup();
	pyramid.solve();
	pyramid.finish();
	pyramid.draw(10);
}
void pyramid_middle_axis(void)
{
	Pyramid pyramid;
	pyramid.m_steps = 10000;
	pyramid.m_dt = 5.00e-02;
	sprintf(pyramid.m_label, "pyramid_middle_axis");
	math::quat(pyramid.m_state_old) = {1, 0, 0, 0};
	math::vec3(pyramid.m_velocity_old) = {1, 1e-5, 0};
	pyramid.setup();
	pyramid.solve();
	pyramid.finish();
	pyramid.draw(50);
}
void pyramid_top(void)
{
	//data
	Pyramid pyramid;
	const double a = 1.00e+00;
	const double b = 1.00e+00;
	const double h = 1.00e+00;
	const double p = 1.00e+00;
	const double g = 9.81e+00;
	const double l = 3 * h / 4;
	const double m = p * a * b * h / 3;
	const double J3 = m * (a * a + b * b) / 20;
	const double J1 = m * (4 * b * b + 3 * h * h) / 80;
	const double J2 = m * (4 * a * a + 3 * h * h) / 80;
	const double wc = sqrt(m * g * l * (J1 + J2 + 2 * sqrt(J1 * J2)) / (J3 * J3 - (J1 - J2) * (J1 - J2)));
	//pyramid
	pyramid.m_a = a;
	pyramid.m_b = b;
	pyramid.m_h = h;
	pyramid.m_p = p;
	pyramid.m_steps = 100000;
	pyramid.m_dt = 1.00e-03;
	//check
	if(J3 < fabs(J1 - J2))
	{
		printf("No stable configuration exists!\n");
		return;
	}
	//solve
	sprintf(pyramid.m_label, "pyramid_top");
	math::quat(pyramid.m_state_old) = {1, 0, 0, 0};
	math::vec3(pyramid.m_velocity_old) = {1e-5 * wc, 0, 1.05 * wc};
	pyramid.m_me = [m, g, l](double, math::quat q)
	{
		const math::vec3 e3(0, 0 ,1);
		return -m * g * l * q.rotate(e3).cross(e3);
	};
	pyramid.m_dme = [m, g, l](double, math::quat q)
	{
		const math::vec3 e3(0, 0 ,1);
		return -m * g * l * e3.spin() * q.rotate(e3).spin();
	};
	pyramid.setup();
	pyramid.solve();
	pyramid.finish();
	pyramid.draw(100);
}

int main(void)
{
	//test
	pyramid_top();
	//return
	return 0;
}