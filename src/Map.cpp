//std
#include <cmath>
#include <cstdio>

//ext
#include "external/cpp/inc/GLFW/glfw3.h"

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

//data
bool Map::full(bool full)
{
	return m_full = full;
}
bool Map::full(void) const
{
	return m_full;
}

uint32_t Map::mode(void) const
{
	return m_mode;
}
uint32_t Map::mode(uint32_t mode)
{
	return m_mode = mode;
}

uint32_t Map::angle(void) const
{
	return m_angle;
}
uint32_t Map::angle(uint32_t angle)
{
	return m_angle = angle;
}

uint32_t Map::mesh(uint32_t index) const
{
	return m_mesh[index];
}
uint32_t Map::mesh(uint32_t index, uint32_t mesh)
{
	return m_mesh[index] = mesh;
}

double Map::state(uint32_t index) const
{
	return m_state[index];
}
double Map::state(uint32_t index, double state)
{
	return m_state[index] = state;
}

double Map::range(uint32_t index, bool boundary) const
{
	return m_range[3 * boundary + index];
}
double Map::range(uint32_t index, bool boundary, double range)
{
	return m_range[3 * boundary + index] = range;
}

//compute
void Map::compute(void)
{
	//data
	char path[200];
	//path
	if(m_full)
	{
		sprintf(path, "data/maps/%d-full.txt", m_mode);
	}
	else
	{
		if(m_mode == 0) sprintf(path, "data/maps/%d-%.2lf.txt", m_mode, m_state[2]);
		if(m_mode == 1 || m_mode == 2) sprintf(path, "data/maps/%d-%d.txt", m_mode, m_angle);
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
	//conditions
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
	if(m_mode == 1 && g2 > 1) return UINT32_MAX;
	if(m_mode == 2 && g1 > 1) return UINT32_MAX;
	if(g1 + g2 < 1 || fabs(g2 - g1) > 1) return UINT32_MAX;
	//compute
	if(m_full)
	{
		if(m_mode == 0) return vertical_full();
		if(m_mode == 1) return tilted_1_full();
		if(m_mode == 2) return tilted_2_full();
	}
	else
	{
		if(m_mode == 0) return compute_vertical();
		if(m_mode == 1) return compute_tilted_1();
		if(m_mode == 2) return compute_tilted_2();
	}
	//return
	return 0U;
}

//vertical
uint32_t Map::vertical_full(void) const
{
	//data
	const Union u1 = vertical_condition_1();
	const Union u2 = vertical_condition_2();
	const Union u3 = vertical_condition_3();
	Union ur = u1.intersection(u2.intersection(u3));
	//return
	ur.trim_empty();
	ur.trim_fusion();
	return ur.m_intervals.size() == 0 ? 0 : 
		ur.m_intervals.size() == 1 && ur.m_intervals[0].m_max == HUGE_VAL ? 1 : 
		ur.m_intervals.size() == 1 && ur.m_intervals[0].m_max != HUGE_VAL ? 2 : 3;
}
Union Map::vertical_condition_1(void) const
{
	//data
	Union ur;
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	//data
	const double b = (g1 + g2) / g1 / g2;
	const double a = (2 * g1 * g2 - g1 - g2 + 1) / g1 / g2;
	//union
	if(a < 0)
	{
		ur.m_intervals.push_back(Interval(0, b < 0 ? sqrt(b / a) : 0));
	}
	else
	{
		ur.m_intervals.push_back(Interval(b > 0 ? sqrt(b / a) : 0, HUGE_VAL));
	}
	//return
	return ur;
}
Union Map::vertical_condition_2(void) const
{
	//data
	Union ur;
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	//data
	const double e = 1 / g1 / g2;
	const double d = (g1 + g2 - 2) / g1 / g2;
	const double c = (g1 * g2 - g1 - g2 + 1) / g1 / g2;
	//return
	if(d * d - 4 * c * e < 0)
	{
		if(c > 0) ur.m_intervals.push_back(Interval(0, HUGE_VAL));
	}
	else
	{
		const double s1 = -d / 2 / c - sqrt(d * d - 4 * c * e) / 2 / c;
		const double s2 = -d / 2 / c + sqrt(d * d - 4 * c * e) / 2 / c;
		if(c > 0)
		{
			ur.m_intervals.push_back(Interval(0, s1 > 0 ? sqrt(s1) : 0));
			ur.m_intervals.push_back(Interval(s2 > 0 ? sqrt(s2) : 0, HUGE_VAL));
		}
		else
		{
			ur.m_intervals.push_back(s1 < 0 ? Interval(0, 0) : Interval(s2 > 0 ? sqrt(s2) : 0, sqrt(s1)));
		}
	}
	//return
	return ur;
}
Union Map::vertical_condition_3(void) const
{
	//data
	Union ur;
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	//data
	const double e = 1 / g1 / g2;
	const double b = (g1 + g2) / g1 / g2;
	const double d = (g1 + g2 - 2) / g1 / g2;
	const double c = (g1 * g2 - g1 - g2 + 1) / g1 / g2;
	const double a = (2 * g1 * g2 - g1 - g2 + 1) / g1 / g2;
	//data
	const double am = a * a - 4 * c;
	const double cm = b * b - 4 * e;
	const double bm = -2 * a * b - 4 * d;
	//union
	if(bm * bm - 4 * am * cm < 0)
	{
		if(am > 0) ur.m_intervals.push_back(Interval(0, HUGE_VAL));
	}
	else
	{
		const double s1 = -bm / 2 / am - sqrt(bm * bm - 4 * am * cm) / 2 / am;
		const double s2 = -bm / 2 / am + sqrt(bm * bm - 4 * am * cm) / 2 / am;
		if(am > 0)
		{
			ur.m_intervals.push_back(Interval(0, s1 > 0 ? sqrt(s1) : 0));
			ur.m_intervals.push_back(Interval(s2 > 0 ? sqrt(s2) : 0, HUGE_VAL));
		}
		else
		{
			ur.m_intervals.push_back(s1 < 0 ? Interval(0, 0) : Interval(s2 > 0 ? sqrt(s2) : 0, sqrt(s1)));
		}
	}
	//return
	return ur;
}

//tilted 1
uint32_t Map::tilted_1_full(void) const
{
	//data
	const double g2 = m_state[1];
	const double w2 = 1 / sqrt(1 - g2);
	const Union u1 = tilted_1_condition_1();
	const Union u2 = tilted_1_condition_2();
	const Union u3 = tilted_1_condition_3();
	Union ur = u1.intersection(u2.intersection(u3)).intersection(Interval(w2, HUGE_VAL));
	//return
	ur.trim_empty();
	ur.trim_fusion();
	return ur.m_intervals.size() == 0 ? 0 : 
		ur.m_intervals.size() == 1 && ur.m_intervals[0].m_max == HUGE_VAL ? 1 : 
		ur.m_intervals.size() == 1 && ur.m_intervals[0].m_max != HUGE_VAL ? 2 : 3;
}
Union Map::tilted_1_condition_1(void) const
{
	//data
	Union ur;
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	//data
	const double a = 2 - g2 * (1 + g1 - g2) / g1;
	const double b = (1 - 2 * g1 - g2 * (1 + g1 - g2)) / g1 / g2 / (1 - g2);
	//union
	if(a < 0)
	{
		ur.m_intervals.push_back(Interval(0, b < 0 ? 0 : pow(-b / a, 0.25)));
	}
	else
	{
		ur.m_intervals.push_back(Interval(b > 0 ? 0 : pow(-b / a, 0.25), HUGE_VAL));
	}
	//return
	return ur;
}
Union Map::tilted_1_condition_2(void) const
{
	//data
	Union ur;
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	//data
	const double c = (g1 - g2) * (1 - g2) / g1;
	const double d = (g1 - g2) * (2 * g2 - 3) / g1 / g2 / (1 - g2);
	const double e = 3 * (g1 - g2) / g1 / g2 / (1 - g2) / (1 - g2);
	//union
	if(d * d - 4 * c * e < 0)
	{
		if(c > 0)
		{
			ur.m_intervals.push_back(Interval(0, HUGE_VAL));
		}
	}
	else
	{
		const double s1 = -d / 2 / c - sqrt(d * d - 4 * c * e) / 2 / c;
		const double s2 = -d / 2 / c + sqrt(d * d - 4 * c * e) / 2 / c;
		const double w1 = s1 > 0 ? pow(s1, 0.25) : 0;
		const double w2 = s2 > 0 ? pow(s2, 0.25) : 0;
		if(c > 0)
		{
			ur.m_intervals.push_back(Interval(0, w1));
			ur.m_intervals.push_back(Interval(w2, HUGE_VAL));
		}
		else
		{
			ur.m_intervals.push_back(Interval(w2, w1));
		}
	}
	//return
	return ur;
}
Union Map::tilted_1_condition_3(void) const
{
	//data
	Union ur;
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	//data
	const double c = (g1 - g2) * (1 - g2) / g1;
	const double a = 2 - g2 * (1 + g1 - g2) / g1;
	const double d = (g1 - g2) * (2 * g2 - 3) / g1 / g2 / (1 - g2);
	const double e = 3 * (g1 - g2) / g1 / g2 / (1 - g2) / (1 - g2);
	const double b = (1 - 2 * g1 - g2 * (1 + g1 - g2)) / g1 / g2 / (1 - g2);
	//data
	const double am = a * a - 4 * c;
	const double cm = b * b - 4 * e;
	const double bm = 2 * a * b - 4 * d;
	//union
	if(bm * bm - 4 * am * cm < 0)
	{
		if(am > 0)
		{
			ur.m_intervals.push_back(Interval(0, HUGE_VAL));
		}
	}
	else
	{
		const double s1 = -bm / 2 / am - sqrt(bm * bm - 4 * am * cm) / 2 / am;
		const double s2 = -bm / 2 / am + sqrt(bm * bm - 4 * am * cm) / 2 / am;
		const double w1 = s1 > 0 ? pow(s1, 0.25) : 0;
		const double w2 = s2 > 0 ? pow(s2, 0.25) : 0;
		if(am > 0)
		{
			ur.m_intervals.push_back(Interval(0, w1));
			ur.m_intervals.push_back(Interval(w2, HUGE_VAL));
		}
		else
		{
			ur.m_intervals.push_back(Interval(w2, w1));
		}
	}
	//return
	return ur;
}

//tilted 2
uint32_t Map::tilted_2_full(void) const
{
	//data
	const double g1 = m_state[0];
	const double w1 = 1 / sqrt(1 - g1);
	const Union u1 = tilted_2_condition_1();
	const Union u2 = tilted_2_condition_2();
	const Union u3 = tilted_2_condition_3();
	Union ur = u1.intersection(u2.intersection(u3)).intersection(Interval(w1, HUGE_VAL));
	//return
	ur.trim_empty();
	ur.trim_fusion();
	return ur.m_intervals.size() == 0 ? 0 : 
		ur.m_intervals.size() == 1 && ur.m_intervals[0].m_max == HUGE_VAL ? 1 : 
		ur.m_intervals.size() == 1 && ur.m_intervals[0].m_max != HUGE_VAL ? 2 : 3;
}
Union Map::tilted_2_condition_1(void) const
{
	//data
	Union ur;
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	//data
	const double a = 2 - g1 * (1 + g2 - g1) / g2;
	const double b = (1 - 2 * g2 - g1 * (1 + g2 - g1)) / g2 / g1 / (1 - g1);
	//union
	if(a < 0)
	{
		ur.m_intervals.push_back(Interval(0, b < 0 ? 0 : pow(-b / a, 0.25)));
	}
	else
	{
		ur.m_intervals.push_back(Interval(b > 0 ? 0 : pow(-b / a, 0.25), HUGE_VAL));
	}
	//return
	return ur;
}
Union Map::tilted_2_condition_2(void) const
{
	//data
	Union ur;
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	//data
	const double c = (g2 - g1) * (1 - g1) / g2;
	const double d = (g2 - g1) * (2 * g1 - 3) / g2 / g1 / (1 - g1);
	const double e = 3 * (g2 - g1) / g2 / g1 / (1 - g1) / (1 - g1);
	//union
	if(d * d - 4 * c * e < 0)
	{
		if(c > 0)
		{
			ur.m_intervals.push_back(Interval(0, HUGE_VAL));
		}
	}
	else
	{
		const double s1 = -d / 2 / c - sqrt(d * d - 4 * c * e) / 2 / c;
		const double s2 = -d / 2 / c + sqrt(d * d - 4 * c * e) / 2 / c;
		const double w1 = s1 > 0 ? pow(s1, 0.25) : 0;
		const double w2 = s2 > 0 ? pow(s2, 0.25) : 0;
		if(c > 0)
		{
			ur.m_intervals.push_back(Interval(0, w1));
			ur.m_intervals.push_back(Interval(w2, HUGE_VAL));
		}
		else
		{
			ur.m_intervals.push_back(Interval(w2, w1));
		}
	}
	//return
	return ur;
}
Union Map::tilted_2_condition_3(void) const
{
	//data
	Union ur;
	const double g1 = m_state[0];
	const double g2 = m_state[1];
	//data
	const double c = (g2 - g1) * (1 - g1) / g2;
	const double a = 2 - g1 * (1 + g2 - g1) / g2;
	const double d = (g2 - g1) * (2 * g1 - 3) / g2 / g1 / (1 - g1);
	const double e = 3 * (g2 - g1) / g2 / g1 / (1 - g1) / (1 - g1);
	const double b = (1 - 2 * g2 - g1 * (1 + g2 - g1)) / g2 / g1 / (1 - g1);
	//data
	const double am = a * a - 4 * c;
	const double cm = b * b - 4 * e;
	const double bm = 2 * a * b - 4 * d;
	//union
	if(bm * bm - 4 * am * cm < 0)
	{
		if(am > 0)
		{
			ur.m_intervals.push_back(Interval(0, HUGE_VAL));
		}
	}
	else
	{
		const double s1 = -bm / 2 / am - sqrt(bm * bm - 4 * am * cm) / 2 / am;
		const double s2 = -bm / 2 / am + sqrt(bm * bm - 4 * am * cm) / 2 / am;
		const double w1 = s1 > 0 ? pow(s1, 0.25) : 0;
		const double w2 = s2 > 0 ? pow(s2, 0.25) : 0;
		if(am > 0)
		{
			ur.m_intervals.push_back(Interval(0, w1));
			ur.m_intervals.push_back(Interval(w2, HUGE_VAL));
		}
		else
		{
			ur.m_intervals.push_back(Interval(w2, w1));
		}
	}
	//return
	return ur;
}