#pragma once

//rigid
#include "rigid-body/inc/Top.hpp"

class Pyramid : public Top
{
public:
	//constructor
	Pyramid(void);

	//destructor
	~Pyramid(void);

	//solve
	void setup(void) override;

	//results
	void draw_model(canvas::Scene*) const override;

	//data
	double m_p;
	double m_a;
	double m_b;
	double m_h;
};