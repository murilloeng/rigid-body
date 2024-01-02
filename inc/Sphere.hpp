#pragma once

//rigid
#include "inc/Rigid.hpp"

class Sphere : public Rigid
{
public:
	//constructor
	Sphere(void);

	//destructor
	~Sphere(void);

	//solve
	void setup(void) override;

	//data
	double m_p;
	double m_r;
};