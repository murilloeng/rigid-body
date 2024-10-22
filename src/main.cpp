//std
#include <cmath>
#include <cstdio>

//rigid-body
#include "rigid-body/inc/Map.hpp"
#include "rigid-body/inc/Top.hpp"

static void compute_maps(uint32_t mode, bool full)
{
	//data
	Map map;
	map.m_mode = mode;
	map.m_full = full;
	//compute
	if(!full)
	{
		if(mode == 0)
		{
			for(uint32_t i = 0; i < 6; i++)
			{
				map.m_state[2] = 1.50 + 0.25 * i;
				map.compute();
			}
		}
		else
		{
			for(uint32_t i = 0; i < 6; i++)
			{
				map.m_angle = i == 0 ? 1 : 15 * i;
				map.compute();
			}
		}
	}
	else
	{
		map.compute();
	}
}

static void test_vertical_symmetric(bool stability)
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
	const uint32_t ng = 2000;
	const uint32_t nw = 2000;
	for(uint32_t i = 0; i <= nw; i++)
	{
		for(uint32_t j = 0; j <= ng; j++)
		{
			const double g = double(j) / ng;
			const double w = 1.50 + 0.5 * double(i) / nw;
			const bool s = Top::stability_vertical(g, 1 + g, w);
			if(s) printf("%.2e %.2e %d\n", w, g, s);
		}
	}
	//return
	return 0;
}