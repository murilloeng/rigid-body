#pragma once

//rigid
#include "rigid-body/inc/Rigid.hpp"

class Sphere : public Rigid
{
public:
	//constructor
	Sphere(void);

	//destructor
	~Sphere(void);

	//solve
	void setup(void) override;

	//results
	virtual void draw_model(canvas::Scene*) const override;

	//data
	double m_p;
	double m_r;
};