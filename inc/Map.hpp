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

	//data
	bool full(bool);
	bool full(void) const;

	uint32_t mode(uint32_t);
	uint32_t mode(void) const;

	uint32_t angle(uint32_t);
	uint32_t angle(void) const;

	uint32_t mesh(uint32_t) const;
	uint32_t mesh(uint32_t, uint32_t);

	double state(uint32_t) const;
	double state(uint32_t, double);

	double range(uint32_t, bool) const;
	double range(uint32_t, bool, double);

	//compute
	void compute(void);
	void state(uint32_t, uint32_t);
	uint32_t compute_stability(void);
	uint32_t compute_vertical(void) const;
	uint32_t compute_tilted_1(void) const;
	uint32_t compute_tilted_2(void) const;

private:
	//data
	bool m_full;
	uint32_t m_mode;
	uint32_t m_mesh[3];

	uint32_t m_angle;
	double m_state[3];
	double m_range[6];
	static const uint32_t m_counter_max = 10;
};