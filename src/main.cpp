//std
#include <cmath>
#include <cstdio>

//rigid
#include "rigid-body/inc/Plotter.hpp"
#include "rigid-body/inc/Pyramid.hpp"

void domains_vertical(void)
{
	/*Plotter plotter;
	plotter.m_mode = 0;
	plotter.m_x1_min = 0;
	plotter.m_x1_max = 2;
	plotter.m_x2_min = 0;
	plotter.m_x2_max = 2;
	plotter.m_x3_min = 0;
	plotter.m_x3_max = 10;
	plotter.plot();*/
}
void top_vertical(unsigned index, double h, double g1, double g2, double wp, const char* label)
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
	sprintf(top.m_label, label);
	const double wr = top.reference_velocity();
	//setup
	top.m_steps = nl * ns;
	top.m_dt = 2 * M_PI / wr / ns;
	math::quat(top.m_state_old) = {1, 0, 0, 0};
	math::vec3(top.m_velocity_old) = {e * (index == 0) * wr, e * (index == 1) * wr, wp * wr};
	//solve
	top.setup();
	top.solve();
	top.finish();
	top.draw(1);
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
	// const double g1 = 0.80;
	// const double g2 = 1.20;
	// const double w1 = 1.90684;
	// const double w2 = 2.23604;
	// top_vertical(1, 0.10, g1, g2, 1.01 * w1, "top_vertical_1");
	// top_vertical(1, 0.10, g1, g2, 0.99 * w1, "top_vertical_2");
	// system("gnuplot -p -e \"index = 2; model = 'top_vertical_1'\" data/top.gp");
	// system("gnuplot -p -e \"index = 2; model = 'top_vertical_2'\" data/top.gp");
	domains_vertical();
	//return
	return 0;
}