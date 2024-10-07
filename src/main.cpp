//std
#include <cmath>
#include <cstdio>

//rigid-body
#include "rigid-body/inc/Map.hpp"

int main(void)
{
	//data
	Map map;
	map.m_mode = 1;
	map.m_mesh[0] = 500;
	map.m_mesh[1] = 500;
	map.m_mesh[2] = 500;
	//compute
	map.m_angle = 5;
	map.compute();
	map.m_angle = 15;
	map.compute();
	map.m_angle = 30;
	map.compute();
	map.m_angle = 45;
	map.compute();
	map.m_angle = 60;
	map.compute();
	map.m_angle = 75;
	map.compute();
	// map.m_full = true;
	// map.compute();
	//return
	return 0;
}