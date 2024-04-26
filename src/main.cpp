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
void pyramid_tilted(void)
{
	//data
	// Pyramid pyramid;
	// const unsigned nl = 200;
	// const unsigned ns = 100;
	// const double h = 1.00e-01;
	// const double p = 7.80e+03;
	// const double g1 = 6.00e-01;
	// const double g2 = 6.00e-01;
	// const double a = sqrt(3) / 2 * h * sqrt(1 + g2 - g1) / sqrt(g1 + g2 - 1);
	// const double b = sqrt(3) / 2 * h * sqrt(1 + g1 - g2) / sqrt(g1 + g2 - 1);
	// //pyramid
	// pyramid.m_a = a;
	// pyramid.m_b = b;
	// pyramid.m_h = h;
	// pyramid.m_p = p;
	// pyramid.setup();
	// printf("J1: %+.2e\n", pyramid.m_J2(0, 0));
	// printf("J2: %+.2e\n", pyramid.m_J2(1, 1));
	// printf("J3: %+.2e\n", pyramid.m_J2(2, 2));
	// printf("g1: %+.2e\n", pyramid.m_J2(0, 0) / pyramid.m_J2(2, 2));
	// printf("g2: %+.2e\n", pyramid.m_J2(1, 1) / pyramid.m_J2(2, 2));

	const double g1 = 0.60;
	const double g2 = 0.60;
	const unsigned ns = 150;
	for(unsigned i = 0; i <= ns; i++)
	{
		const double bt = 1.5 * i / ns;
		printf("%+.2e %d\n", bt, Top::stability_check(1, g1, g2, bt));
	}
}

int main(void)
{
	//test
	pyramid_tilted();
	//return
	return 0;
}