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
	const unsigned nl = 200;
	const unsigned ns = 100;
	const double a = 1.00e-01;
	const double b = 1.00e-01;
	const double h = 1.00e-01;
	const double p = 7.80e+03;
	//pyramid
	pyramid.m_a = a;
	pyramid.m_b = b;
	pyramid.m_h = h;
	pyramid.m_p = p;
	pyramid.setup();
	const double wc = pyramid.critical_velocity();
	//solve
	pyramid.m_steps = nl * ns;
	pyramid.m_dt = 2 * M_PI / wc / ns;
	sprintf(pyramid.m_label, "pyramid_vertical");
	math::quat(pyramid.m_state_old) = {1, 0, 0, 0};
	math::vec3(pyramid.m_velocity_old) = {1e-5 * wc, 0, 0.99 * wc};
	pyramid.setup();
	pyramid.solve();
	pyramid.finish();
	pyramid.draw(10);
}
void pyramid_tilted(unsigned index, double g1, double g2, double qt)
{
	//data
	Pyramid pyramid;
	const unsigned nl = 200;
	const unsigned ns = 100;
	const double h = 1.00e-01;
	const double p = 7.80e+03;
	const double g = 9.81e+00;
	const double a = sqrt(3) / 2 * h * sqrt(g2 - g1 + 1) / sqrt(g1 + g2 - 1);
	const double b = sqrt(3) / 2 * h * sqrt(g1 - g2 + 1) / sqrt(g1 + g2 - 1);
	//check
	if(g1 + g2 < 1 || fabs(g1 - g2) > 1)
	{
		fprintf(stderr, "Tilted top: Incorrect input arguments\n");
		exit(EXIT_FAILURE);
	}
	//pyramid
	pyramid.m_a = a;
	pyramid.m_b = b;
	pyramid.m_h = h;
	pyramid.m_p = p;
	pyramid.setup();
	const double m = pyramid.m_M;
	const double l = pyramid.m_l;
	const double J1 = pyramid.m_J2(0, 0);
	const double J2 = pyramid.m_J2(1, 1);
	const double J3 = pyramid.m_J2(2, 2);
	const double Jp = index == 0 ? J2 : J1;
	const double wr = sqrt(m * g * l / J3);
	const double w0 = sqrt(m * g * l / cos(qt) / (J3 - Jp));
	//solve
	pyramid.m_steps = nl * ns;
	pyramid.m_dt = 2 * M_PI / wr / ns;
	sprintf(pyramid.m_label, "pyramid_tilted");
	fprintf(stdout, "System stability: %s\n", Top::stability_check(index, g1, g2, qt) ? "ok" : "not ok");
	math::quat(pyramid.m_state_old) = {cos(qt / 2), (index == 0) * sin(qt / 2), (index == 1) * sin(qt / 2), 0};
	math::vec3(pyramid.m_velocity_old) = {(index == 0) * w0 * sin(qt), (index == 1) * w0 * sin(qt), w0 * cos(qt)};
	pyramid.setup();
	pyramid.solve();
	pyramid.finish();
	pyramid.draw(10);
}

int main(void)
{
	//test
	pyramid_tilted(0, 0.75, 0.75, M_PI / 20);
	//return
	return 0;
}