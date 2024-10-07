//std
#include <cmath>
#include <cstdio>

//rigid body
#include "rigid-body/inc/Map.hpp"

//constructor
Map::Map(void) : m_full(false), m_mode(0), m_mesh{500, 500, 500}, m_range{0.0, 0.0, 1.5, 2.0, 2.0, 3.0}
{
	return;
}

//destructor
Map::~Map(void)
{
	return;
}

//compute
void Map::compute(void)
{
	//path
	char path[200];
	if(m_full) sprintf(path, "data/map-%d-full.txt", m_mode);
	else
	{
		if(m_mode == 0) sprintf(path, "data/map-%d-%.2lf.txt", m_mode, m_state[2]);
		if(m_mode == 1 || m_mode == 2) sprintf(path, "data/map-%d-%.2lf.txt", m_mode, m_angle);
	}
	//file
	FILE* file = fopen(path, "w");
	//loop
	for(uint32_t i = 0; i <= m_mesh[0]; i++)
	{
		for(uint32_t j = 0; j <= m_mesh[1]; j++)
		{
			state(i, j);
			fprintf(file, "%+.6e %+.6e %d\n", m_state[0], m_state[1], compute_stability());
		}
		fprintf(file, "\n");
	}
	//close
	fclose(file);
}
void Map::state(uint32_t i, uint32_t j)
{
	m_state[0] = m_range[0] + double(i) / m_mesh[0] * (m_range[3] - m_range[0]);
	m_state[1] = m_range[1] + double(j) / m_mesh[1] * (m_range[4] - m_range[1]);
	if(m_mode == 1) m_state[2] = 1 / sqrt((1 - m_state[1]) * cos(M_PI * m_angle / 180));
	if(m_mode == 2) m_state[2] = 1 / sqrt((1 - m_state[0]) * cos(M_PI * m_angle / 180));
}
uint32_t Map::compute_vertical(void) const
{
	//data
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	const double wp = m_state[2];
	//data
	const double e1 = 1 / g1 / g2;
	const double b1 = (g1 + g2) / g1 / g2;
	const double d1 = (g1 + g2 - 2) / g1 / g2;
	const double c1 = (g1 * g2 - g1 - g2 + 1) / g1 / g2;
	const double a1 = (2 * g1 * g2 - g1 - g2 + 1) / g1 / g2;
	//consditions
	const double B1 = a1 * wp * wp - b1;
	const double C1 = c1 * wp * wp * wp * wp + d1 * wp * wp + e1;
	//return
	return B1 >= 0 && C1 >= 0 && B1 * B1 - 4 * C1 >= 0;
}
uint32_t Map::compute_tilted_1(void) const
{
	//data
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	const double wp = m_state[2];
	//data
	const double c2 = (g1 - g2) * (1 - g2) / g1;
	const double a2 = 2 - g2 * (1 + g1 - g2) / g1;
	const double d2 = (g1 - g2) * (2 * g2 - 3) / g1 / g2 / (1 - g2);
	const double e2 = 3 * (g1 - g2) / g1 / g2 / (1 - g2) / (1 - g2);
	const double b2 = (1 - 2 * g1 - g2 * (1 + g1 - g2)) / g1 / g2 / (1 - g2);
	//consditions
	const double B2 = a2 * wp * wp + b2 / wp / wp;
	const double C2 = c2 * wp * wp * wp * wp + d2 + e2 / wp / wp / wp / wp;
	//return
	return B2 >= 0 && C2 >= 0 && B2 * B2 - 4 * C2 >= 0;
}
uint32_t Map::compute_tilted_2(void) const
{
	//data
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	const double wp = m_state[2];
	//data
	const double c3 = (g2 - g1) * (1 - g1) / g2;
	const double a3 = 2 - g1 * (1 + g2 - g1) / g2;
	const double d3 = (g2 - g1) * (2 * g1 - 3) / g2 / g1 / (1 - g1);
	const double e3 = 3 * (g2 - g1) / g2 / g1 / (1 - g1) / (1 - g1);
	const double b3 = (1 - 2 * g2 - g1 * (1 + g2 - g1)) / g2 / g1 / (1 - g1);
	//conditions
	const double B3 = a3 * wp * wp + b3 / wp / wp;
	const double C3 = c3 * wp * wp * wp * wp + d3 + e3 / wp / wp / wp / wp;
	//return
	return B3 >= 0 && C3 >= 0 && B3 * B3 - 4 * C3 >= 0;
}
uint32_t Map::compute_stability(void)
{
	//check
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	if(g1 + g2 < 1 || fabs(g2 - g1) > 1) return UINT32_MAX;
	//compute
	if(!m_full)
	{
		if(m_mode == 0) return compute_vertical();
		if(m_mode == 1) return compute_tilted_1();
		if(m_mode == 2) return compute_tilted_2();
	}
	else
	{
		uint32_t v1 = 0, v2 = 0, counter = 0;
		for(uint32_t i = 0; i <= m_mesh[2]; i++)
		{
			m_state[2] = m_range[2] + double(i) / m_mesh[2] * (m_range[5] - m_range[2]);
			if(m_mode == 0) v2 = compute_vertical();
			if(m_mode == 1) v2 = compute_tilted_1();
			if(m_mode == 2) v2 = compute_tilted_2();
			if(v1 != v2) v1 = v2, counter++;
		}
		return counter;
	}
	//return
	return 0U;
}