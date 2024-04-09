#pragma once

//rigid
#include "rigid-body/inc/Rigid.hpp"

class Pyramid : public Rigid
{
public:
	//constructor
	Pyramid(void);

	//destructor
	~Pyramid(void);

	//solve
	void setup(void) override;

	//results
	virtual void draw_model(canvas::Scene*) const override;

	//data
	double m_p;
	double m_a;
	double m_b;
	double m_h;
};