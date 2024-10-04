//std
#include <cmath>
#include <cstdio>

//rigid-body
#include "rigid-body/inc/Map.hpp"

int main(void)
{
	//data
	Map map;
	map.m_mode = 0;
	map.m_mesh[0] = 500;
	map.m_mesh[1] = 500;
	//compute
	map.m_state[2] = 1.50;
	map.compute();
	map.m_state[2] = 1.75;
	map.compute();
	map.m_state[2] = 2.00;
	map.compute();
	map.m_state[2] = 2.25;
	map.compute();
	map.m_state[2] = 2.50;
	map.compute();
	//return
	return 0;
}