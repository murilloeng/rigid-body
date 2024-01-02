#pragma once

//math
#include "Math/inc/linear/vec3.hpp"
#include "Math/inc/linear/quat.hpp"
#include "Math/inc/linear/mat3.hpp"

class Rigid
{
public:
	//constructor
	Rigid(void);

	//destructor
	~Rigid(void);

	//solver
	void solve(void);
	void record(void);
	void finish(void);
	virtual void setup(void);

	//data
	double m_M;
	double m_dt;
	math::mat3 m_J1;
	math::mat3 m_J2;
	unsigned m_step;
	unsigned m_steps;
	char m_label[200];

	double* m_state_data;
	double* m_energy_data;
	double* m_velocity_data;
	double* m_acceleration_data;

	double m_state_old[4];
	double m_state_new[4];
	double m_velocity_old[3];
	double m_velocity_new[3];
	double m_acceleration_old[3];
	double m_acceleration_new[3];
};