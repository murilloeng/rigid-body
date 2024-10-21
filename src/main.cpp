//std
#include <cmath>
#include <cstdio>

//rigid-body
#include "rigid-body/inc/Map.hpp"
#include "rigid-body/inc/Top.hpp"

void test_vertical_symmetric(bool stability)
{
	//data
	Top top;
	const unsigned ns = 10000;
	const double l = 1.00e-01;
	const double m = 1.00e+00;
	const double gs = 7.50e-01;
	const double J3 = 1.00e+00;
	const double tr = 1.00e-05;
	//setup
	top.m_M = m;
	top.m_l = l;
	top.m_J[8] = J3;
	top.m_steps = ns;
	top.m_dt = M_PI / 100 / sqrt(gs);
	top.m_J[0] = top.m_J[4] = gs * J3;
	const double wr = top.reference_velocity();
	top.m_velocity_old[0] = 2 * sqrt(gs) * wr * tr;
	top.m_velocity_old[2] = 2 * sqrt(gs) * wr * (stability ? 1.01 : 0.99);
	sprintf(top.m_label, "tests/vertical-symmetric-%s", stability ? "stable" : "unstable");
	//solve
	top.setup();
	top.solve();
	top.finish();
}

int main(void)
{
	//test
	test_vertical_symmetric(true);
	test_vertical_symmetric(false);
	//return
	return 0;
}