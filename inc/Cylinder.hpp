#pragma once

//rigid
#include "rigid-body/inc/Top.hpp"

class Cylinder : public Top
{
public:
	//constructor
	Cylinder(void);

	//destructor
	~Cylinder(void);

	//solve
	void setup(void) override;

	//results
	void draw_model(canvas::Scene*) const override;

	//data
	double m_p;
	double m_r;
	double m_h;
};