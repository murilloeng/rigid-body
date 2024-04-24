#pragma once

//rigid
#include "rigid-body/inc/Top.hpp"

class Cone : public Top
{
public:
	//constructor
	Cone(void);

	//destructor
	~Cone(void);

	//solve
	void setup(void) override;

	//results
	void draw_model(canvas::Scene*) const override;

	//data
	double m_p;
	double m_r;
	double m_h;
};