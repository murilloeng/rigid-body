#pragma once

class Interval
{
public:
	//constructor
	Interval(void);
	Interval(double, double);

	//destructor
	~Interval(void);

	//operations
	bool is_empty(void) const;
	Interval fusion(const Interval&) const;
	Interval intersection(const Interval&) const;

	//data
	double m_min;
	double m_max;
};