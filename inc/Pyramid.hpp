#pragma once

//rigid
#include "inc/Rigid.hpp"

class Pyramid : public Rigid
{
public:
	//constructor
	Pyramid(void);

	//destructor
	~Pyramid(void);

	//solve
	void setup(void) override;

	//data
	double m_p;
	double m_a;
	double m_b;
	double m_h;
};