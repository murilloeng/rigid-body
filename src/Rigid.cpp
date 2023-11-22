//std
#include <cmath>
#include <cstdio>

//rigid
#include "inc/Rigid.hpp"

//constructors
Rigid::Rigid(void)
{
	return;
}

//destructor
Rigid::~Rigid(void)
{
	return;
}

//analysis
void Rigid::setup(void)
{
	//solver
	m_dt = m_T / m_ns;
	m_af = m_p / (1 + m_p);
	m_b = 1 / pow(1 + m_p, 2);
	m_g = (3 - m_p) / (1 + m_p) / 2;
	m_am = (2 * m_p - 1) / (1 + m_p);
	//initial
	m_q_old = m_q_new;
	m_w_old = m_w_new;
	m_a_new = m_a_old = m_s_new = m_s_old = -m_w_new.cross(m_J * m_w_new);
}
void Rigid::solve(void)
{
	//data
	math::mat3 S;
	math::vec3 r, m, dp;
	const double gp = m_g / m_b / m_dt;
	const double bp = (1 - m_am) / (1 - m_af) / m_b / m_dt / m_dt;
	//file
	FILE* file = fopen("rigid.txt", "w");
	//loop
	for(unsigned i = 0; i < m_ns; i++)
	{
		//predictor
		m = m_m((i + 1) * m_dt);
		m_s_new = (m_a_old - m_am * m_s_old) / (1 - m_am);
		m_w_new = m_w_old + m_dt * m_s_old + m_g * m_dt * (m_s_new - m_s_old);
		m_p_new = m_dt * m_w_old + m_dt * m_dt / 2 * m_s_old + m_b * m_dt * m_dt * (m_s_new - m_s_old);
		m_q_new = m_q_old * m_p_new.quaternion();
		//corrector
		for(unsigned j = 0; j < 10; j++)
		{
			//residue
			r = m_q_new.conjugate(m) - m_J * m_a_new - m_w_new.cross(m_J * m_w_new);
			if(r.norm() < 1e-5)
			{
				printf("step: %04d\n", i);
				printf("rotation: %.2e %.2e %.2e %.2e\n", m_q_new[0], m_q_new[1], m_q_new[2], m_q_new[3]);
				printf("velocity: %.2e %.2e %.2e\n", m_w_new[0], m_w_new[1], m_w_new[2]);
				printf("acceleration: %.2e %.2e %.2e\n", m_a_new[0], m_a_new[1], m_a_new[2]);
				break;
			}
			//update
			S = bp * m_J + gp * (m_w_new.spin() * m_J - (m_J * m_w_new).spin());
			dp = S.inverse() * r;
			m_p_new += dp;
			m_w_new += gp * dp;
			m_a_new += bp * dp;
			m_q_new = m_q_old * m_p_new.quaternion();
			m_s_new = ((1 - m_af) * m_a_new + m_af * m_a_old - m_am * m_s_old) / (1 - m_am);
		}
	}
	//close
	fclose(file);
}