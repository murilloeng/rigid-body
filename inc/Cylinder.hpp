#pragma once

//rigid
#include "inc/Rigid.hpp"

class Cylinder : public Rigid
{
public:
	//constructor
	Cylinder(void);

	//destructor
	~Cylinder(void);

	//solve
	void setup(void) override;

	//data
	double m_p;
	double m_r;
	double m_h;
};