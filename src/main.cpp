//std
#include <cmath>
#include <cstdio>

//rigid
#include "rigid-body/inc/Pyramid.hpp"

void top_vertical(unsigned index, double h, double g1, double g2, double sf)
{
	//data
	Pyramid top;
	const unsigned nl = 100;
	const unsigned ns = 100;
	const double e = 1.00e-05;
	const double p = 7.80e+03;
	const double a = sqrt(3) / 2 * h * sqrt(g2 - g1 + 1) / sqrt(g1 + g2 - 1);
	const double b = sqrt(3) / 2 * h * sqrt(g1 - g2 + 1) / sqrt(g1 + g2 - 1);
	//check
	if(g1 + g2 < 1 || fabs(g1 - g2) > 1)
	{
		fprintf(stderr, "Tilted top: Incorrect input arguments\n");
		exit(EXIT_FAILURE);
	}
	//velocity
	top.m_a = a;
	top.m_b = b;
	top.m_h = h;
	top.m_p = p;
	top.setup();
	const double wc = top.critical_velocity();
	printf("%.3e %.3e %.3e\n", top.critical_velocity(), top.critical_velocity(0), top.critical_velocity(1));
	sprintf(top.m_label, "top_vertical_%d", sf > 1 ? 1 : 2);
	//setup
	top.m_steps = nl * ns;
	top.m_dt = 2 * M_PI / wc / ns;
	math::quat(top.m_state_old) = {1, 0, 0, 0};
	math::vec3(top.m_velocity_old) = {e * (index == 0) * wc, e * (index == 1) * wc, sf * wc};
	//solve
	top.setup();
	top.solve();
	top.finish();
	// top.draw(10);
}
void top_tilted(unsigned index, double g1, double g2, double qt)
{
	//data
	Pyramid top;
	const unsigned nl = 10;
	const unsigned ns = 100;
	const double h = 1.00e-01;
	const double p = 7.80e+03;
	const double a = sqrt(3) / 2 * h * sqrt(g2 - g1 + 1) / sqrt(g1 + g2 - 1);
	const double b = sqrt(3) / 2 * h * sqrt(g1 - g2 + 1) / sqrt(g1 + g2 - 1);
	//check
	if(g1 + g2 < 1 || fabs(g1 - g2) > 1)
	{
		fprintf(stderr, "Tilted top: Incorrect input arguments\n");
		exit(EXIT_FAILURE);
	}
	//velocity
	top.m_a = a;
	top.m_b = b;
	top.m_h = h;
	top.m_p = p;
	top.setup();
	const double gp = index == 0 ? g2 : g1;
	const double wr = top.reference_velocity();
	const double w0 = wr * sqrt(1 / cos(qt) / (1 - gp));
	//setup
	top.m_steps = nl * ns;
	top.m_dt = 2 * M_PI / w0 / ns;
	sprintf(top.m_label, "top_tilted");
	fprintf(stdout, "System stability: %s\n", Top::stability_check(index, g1, g2, qt) ? "ok" : "not ok");
	math::quat(top.m_state_old) = {cos(qt / 2), (index == 0) * sin(qt / 2), (index == 1) * sin(qt / 2), 0};
	math::vec3(top.m_velocity_old) = {-(index == 1) * w0 * sin(qt), (index == 0) * w0 * sin(qt), w0 * cos(qt)};
	//solve
	top.setup();
	top.solve();
	top.finish();
	top.draw(10);
}

int main(void)
{
	//test
	const double g1 = 1.20;
	const double g2 = 1.60;
	top_vertical(1, 0.10, g1, g2, 1.01);
	top_vertical(1, 0.10, g1, g2, 0.89);
	//return
	return 0;
}