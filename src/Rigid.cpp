//std
#include <cmath>
#include <thread>
#include <cstdio>
#include <cstring>

//canvas
#include "Canvas/inc/Objects/Object.hpp"

//rigid
#include "rigid-body/inc/Rigid.hpp"

//constructor
Rigid::Rigid(void) : 
	m_iteration_max(10), m_state_data(nullptr), m_energy_data(nullptr), m_velocity_data(nullptr), m_acceleration_data(nullptr)
{
	return;
}

//destructor
Rigid::~Rigid(void)
{
	delete[] m_state_data;
	delete[] m_energy_data;
	delete[] m_velocity_data;
	delete[] m_acceleration_data;
}

//solver
void Rigid::solve(void)
{
	//data
	const double b = 0.25;
	const double g = 0.50;
	math::vec3 v, r, dv, me;
	math::mat3 M, C, K, S, Ke;
	math::quat q_old(m_state_old), q_new(m_state_new);
	math::vec3 w_old(m_velocity_old), w_new(m_velocity_new);
	math::vec3 a_old(m_acceleration_old), a_new(m_acceleration_new);
	//initial
	me.zeros();
	Ke.zeros();
	if(m_me) me = m_me(0.0, q_old);
	math::quat(m_state_data + 0) = q_old;
	math::vec3(m_velocity_data + 0) = w_old;
	m_energy_data[0] = w_old.inner(m_J2 * w_old) / 2;
	m_J2.solve(a_old, me - w_old.cross(m_J2 * w_old));
	a_new = math::vec3(m_acceleration_data + 0) = a_old;
	//integration
	for(m_step = 0; m_step < m_steps; m_step++)
	{
		//predictor
		a_new = a_old;
		w_new = w_old + m_dt * a_old;
		v = m_dt * w_old + m_dt * m_dt / 2 * a_old;
		//corrector
		for(m_iteration = 0; m_iteration < m_iteration_max; m_iteration++)
		{
			//residue
			q_new = q_old * v.quaternion();
			if(m_me) me = m_me((m_step + 1) * m_dt, q_new);
			if(m_me) Ke = m_Ke((m_step + 1) * m_dt, q_new);
			r = m_J2 * a_new + w_new.cross(m_J2 * w_new) - me;
			//check
			if(r.norm() < 1e-5)
			{
				record();
				break;
			}
			//system
			M = m_J2;
			C = w_new.spin() * m_J2 + m_J2 * w_new.spin() - (m_J2 * w_new).spin();
			K = m_J2 * a_new.spin() + w_new.spin() * m_J2 * w_new.spin() - (m_J2 * w_new).spin() * w_new.spin() - Ke;
			S = K + M / b / m_dt / m_dt + g * C / b / m_dt;
			//update
			S.solve(dv, -r);
			v += dv;
			w_new += g / b / m_dt * dv;
			a_new += double(1) / b / m_dt / m_dt * dv;
		}
	}
}
void Rigid::setup(void)
{
	//delete
	delete[] m_state_data;
	delete[] m_energy_data;
	delete[] m_velocity_data;
	delete[] m_acceleration_data;
	//allocate
	m_state_data = new double[4 * (m_steps + 1)];
	m_energy_data = new double[1 * (m_steps + 1)];
	m_velocity_data = new double[3 * (m_steps + 1)];
	m_acceleration_data = new double[3 * (m_steps + 1)];
}
void Rigid::record(void)
{
	const math::vec3 w_new(m_velocity_new);
	memcpy(m_state_old, m_state_new, 4 * sizeof(double));
	memcpy(m_velocity_old, m_velocity_new, 3 * sizeof(double));
	memcpy(m_acceleration_old, m_acceleration_new, 3 * sizeof(double));
	memcpy(m_state_data + 4 * (m_step + 1), m_state_new, 4 * sizeof(double));
	memcpy(m_velocity_data + 3 * (m_step + 1), m_velocity_new, 3 * sizeof(double));
	memcpy(m_acceleration_data + 3 * (m_step + 1), m_acceleration_new, 3 * sizeof(double));
	m_energy_data[m_step + 1] = w_new.inner(m_J2 * w_new) / 2;
}
void Rigid::finish(void)
{
	//data
	FILE* files[4];
	char paths[4][200];
	const unsigned size[] = {4, 1, 3, 3};
	const char* type[] = {"state", "energy", "velocity", "acceleration"};
	const double* data[] = {m_state_data, m_energy_data, m_velocity_data, m_acceleration_data};
	//write
	for(unsigned i = 0; i < 4; i++)
	{
		//path
		sprintf(paths[i], "data/%s_%s.dat", m_label, type[i]);
		//write
		files[i] = fopen(paths[i], "w");
		for(unsigned j = 0; j < m_steps; j++)
		{
			fprintf(files[i], "%+.6e ", m_dt * j);
			for(unsigned k = 0; k < size[i]; k++)
			{
				fprintf(files[i], "%+.6e ", data[i][size[i] * j + k]);
			}
			fprintf(files[i], "\n");
		}
		fclose(files[i]);
	}
}

//analysis
math::mat3 Rigid::inertia(void) const
{
	return m_J2;
}
math::mat3 Rigid::damping(void) const
{
	const math::vec3 w(m_velocity_new);
	return w.spin() * m_J2 + m_J2 * w.spin() - (m_J2 * w).spin();
}
math::mat3 Rigid::stiffness(void) const
{
	const math::quat q(m_state_new);
	const math::vec3 w(m_velocity_new);
	const math::vec3 a(m_acceleration_new);
	return m_J2 * a.spin() + w.spin() * m_J2 * w.spin() - (m_J2 * w).spin() * w.spin() - m_Ke(0, q);
}

//results
void Rigid::draw(unsigned duration) const
{
	////data
	//unsigned* step = new unsigned(0);
	//canvas::windows::Glut* app = new canvas::windows::Glut(0, nullptr, "../Canvas/shd/");
	////objects
	//draw_model(app->scene());
	//app->scene()->update(true);
	////idle
	//std::function<void(void)> callback_idle = [this, app, step, duration](void)
	//{
	//	canvas::quat q;
	//	q[0] = (float) m_state_data[4 * *step + 0];
	//	q[1] = (float) m_state_data[4 * *step + 1];
	//	q[2] = (float) m_state_data[4 * *step + 2];
	//	q[3] = (float) m_state_data[4 * *step + 3];
	//	for(canvas::objects::Object* object : app->scene()->objects())
	//	{
	//		object->model_matrix(canvas::mat4::rotation(q));
	//	}
	//	app->scene()->update(false);
	//	*step = (*step + 1) % (m_steps + 1);
	//	std::this_thread::sleep_for(std::chrono::milliseconds(duration * 1000 / m_steps));
	//};
	//app->callback_idle(callback_idle);
	////start
	//app->start();
}