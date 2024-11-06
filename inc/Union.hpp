#pragma once

//std
#include <vector>

//rigid-body
#include "rigid-body/inc/Interval.hpp"

class Union
{
public:
	//constructors
	Union(void);

	//destructor
	~Union(void);

	//operations
	void trim_empty(void);
	void trim_fusion(void);
	Union intersection(const Union&) const;
	Union intersection(const Interval&) const;

	//data
	std::vector<Interval> m_intervals;
};