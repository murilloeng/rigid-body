//std
#include <cmath>
#include <cstdio>

//rigid
#include "rigid-body/inc/Sphere.hpp"
#include "rigid-body/inc/Pyramid.hpp"
#include "rigid-body/inc/Cylinder.hpp"

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
void pyramid_vertical(void)
{
	//data
	Pyramid pyramid;
	const unsigned nl = 100;
	const unsigned ns = 100;
	const double a = 1.00e-01;
	const double b = 1.00e-01;
	const double h = 1.00e-01;
	const double p = 7.80e+03;
	const double g = 9.81e+00;
	//pyramid
	pyramid.m_a = a;
	pyramid.m_b = b;
	pyramid.m_h = h;
	pyramid.m_p = p;
	pyramid.setup();
	const double wc = pyramid.critical_velocity();
	//solve
	printf("wc: %+.6e\n", wc);
	pyramid.m_steps = nl * ns;
	pyramid.m_dt = 2 * M_PI / wc / ns;
	sprintf(pyramid.m_label, "pyramid_top");
	math::quat(pyramid.m_state_old) = {1, 0, 0, 0};
	math::vec3(pyramid.m_velocity_old) = {1e-5 * wc, 0, 0.99 * wc};
	pyramid.m_me = [pyramid](double, math::quat q)
	{
		const double g = 9.81;
		const double m = pyramid.m_M;
		const double l = pyramid.m_l;
		const math::vec3 e3(0, 0, 1);
		return -m * g * l * q.rotate(e3).cross(e3);
	};
	pyramid.m_Ke = [pyramid](double, math::quat q)
	{
		const double g = 9.81;
		const double m = pyramid.m_M;
		const double l = pyramid.m_l;
		const math::vec3 e3(0, 0, 1);
		return -m * g * l * e3.spin() * q.rotate(e3).spin();
	};
	pyramid.setup();
	pyramid.solve();
	pyramid.finish();
	pyramid.draw(100);
}
void pyramid_top_friction(void)
{
	//data
	Pyramid pyramid;
	const unsigned nl = 200;
	const double a = 1.00e-01;
	const double b = 1.00e-01;
	const double h = 1.00e-01;
	const double p = 7.80e+03;
	const double g = 9.81e+00;
	const double u = 5.00e-01;
	const double l = 3 * h / 4;
	const unsigned ns = 100000;
	const double m = p * a * b * h / 3;
	const double J3 = m * (a * a + b * b) / 20;
	const double J1 = m * (4 * b * b + 3 * h * h) / 80;
	const double J2 = m * (4 * a * a + 3 * h * h) / 80;
	const double wc = sqrt(m * g * l * sqrt(1 + u * u) * (J1 + J2 + 2 * sqrt(J1 * J2)) / (J3 * J3 - (J1 - J2) * (J1 - J2)));
	//pyramid
	pyramid.m_a = a;
	pyramid.m_b = b;
	pyramid.m_h = h;
	pyramid.m_p = p;
	pyramid.m_steps = ns;
	pyramid.m_dt = 2 * M_PI / wc * nl / ns;
	//check
	if(J3 < fabs(J1 - J2))
	{
		printf("No stable configuration exists!\n");
		return;
	}
	//solve
	sprintf(pyramid.m_label, "pyramid_top_friction");
	math::vec3(pyramid.m_velocity_old) = {1e-5 * wc, 0, 1.01 * wc};
	math::quat(pyramid.m_state_old) = {cos(atan(u) / 2), sin(atan(u) / 2), 0, 0};
	pyramid.m_me = [m, g, l, u](double, math::quat q)
	{
		const math::vec3 e2(0, 1, 0);
		const math::vec3 e3(0, 0, 1);
		return -m * g * l * q.rotate(e3).cross(e3 - u * e2);
	};
	pyramid.m_Ke = [m, g, l, u](double, math::quat q)
	{
		const math::vec3 e2(0, 1, 0);
		const math::vec3 e3(0, 0, 1);
		return -m * g * l * (e3 - u * e2).spin() * q.rotate(e3).spin();
	};
	pyramid.setup();
	pyramid.solve();
	pyramid.finish();
	pyramid.draw(100);
}

int main(void)
{
	//test
	//return
	return 0;
}