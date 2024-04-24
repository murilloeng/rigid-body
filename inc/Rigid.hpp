#pragma once

//std
#include <functional>

//math
#include "Math/inc/linear/vec3.hpp"
#include "Math/inc/linear/quat.hpp"
#include "Math/inc/linear/mat3.hpp"

//canvas
#include "Canvas/inc/Scene/Scene.hpp"

class Rigid
{
public:
	//constructor
	Rigid(void);

	//destructor
	virtual ~Rigid(void);

	//solver
	void solve(void);
	virtual void setup(void);
	virtual void record(void);
	virtual void finish(void);

	//results
	void draw(unsigned) const;
	virtual void draw_model(canvas::Scene*) const = 0;

	//data
	double m_M;
	double m_dt;
	math::mat3 m_J1;
	math::mat3 m_J2;
	unsigned m_step;
	unsigned m_steps;
	unsigned m_iteration;
	unsigned m_iteration_max;

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

	std::function<math::vec3(double, math::quat)> m_me;
	std::function<math::mat3(double, math::quat)> m_Ke;
};