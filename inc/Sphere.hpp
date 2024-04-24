#pragma once

//rigid
#include "rigid-body/inc/Top.hpp"

class Sphere : public Top
{
public:
	//constructor
	Sphere(void);

	//destructor
	~Sphere(void);

	//solve
	void setup(void) override;

	//results
	void draw_model(canvas::Scene*) const override;

	//data
	double m_p;
	double m_r;
};