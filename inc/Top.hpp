#pragma once

//rigid
#include "rigid-body/inc/Rigid.hpp"

class Top : public Rigid
{
public:
	//constructors
	Top(void);

	//destructor
	~Top(void);

	//solver
	void setup(void) override;
	void record(void) override;
	void finish(void) override;

	//stability
	double critical_velocity(void) const;
	double reference_velocity(void) const;
	bool stability_check(unsigned, double) const;
	static bool stability_check(unsigned, double, double, double);

	//data
	double m_l;
	double* m_position_data;
};