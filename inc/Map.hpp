#pragma once

//std
#include <cstdint>

class Map
{
public:
	//constructors
	Map(void);

	//destructor
	~Map(void);

	//compute
	void compute(void);
	void state(uint32_t, uint32_t);
	uint32_t compute_stability(void);
	uint32_t compute_vertical(void) const;
	uint32_t compute_tilted_1(void) const;
	uint32_t compute_tilted_2(void) const;

	//data
	bool m_full;
	uint32_t m_mode;
	uint32_t m_mesh[3];
	
	double m_state[3];
	double m_range[6];
};