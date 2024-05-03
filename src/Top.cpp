//std
#include <cmath>

//rigid
#include "rigid-body/inc/Top.hpp"

//constructors
Top::Top(void) : m_position_data(nullptr)
{
	return;
}

//destructor
Top::~Top(void)
{
	delete[] m_position_data;
}

//solver
void Top::setup(void)
{
	Rigid::setup();
	delete[] m_position_data;
	m_position_data = new double[3 * (m_steps + 1)];
	m_me = [this](double t, math::quat q){
		const double m = m_M;
		const double l = m_l;
		const double g = 9.81;
		const math::vec3 e3(0, 0, 1);
		return -m * g * l * q.rotate(e3).cross(e3);
	};
	m_Ke = [this](double t, math::quat q){
		const double m = m_M;
		const double l = m_l;
		const double g = 9.81;
		const math::vec3 e3(0, 0, 1);
		return -m * g * l * e3.spin() * q.rotate(e3).spin();
	};
	math::vec3(m_position_data + 0) = math::quat(m_state_old).rotate({0, 0, -m_l});
}
void Top::record(void)
{
	Rigid::record();
	math::vec3(m_position_data + 3 * (m_step + 1)) = math::quat(m_state_new).rotate({0, 0, -m_l});
}
void Top::finish(void)
{
	//data
	char path[200];
	Rigid::finish();
	sprintf(path, "data/%s_position.dat", m_label);
	//write
	FILE* file = fopen(path, "w");
	for(unsigned j = 0; j < m_steps; j++)
	{
		fprintf(file, "%+.6e ", m_dt * j);
		for(unsigned k = 0; k < 3; k++)
		{
			fprintf(file, "%+.6e ", m_position_data[3 * j + k]);
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

//stability
double Top::reference_velocity(void) const
{
	//data
	const double m = m_M;
	const double l = m_l;
	const double g = 9.81e+00;
	const double J3 = m_J2[8];
	//return
	return sqrt(m * g * l / J3);
}

double Top::critical_velocity(void) const
{
	//data
	const double J1 = m_J2[0];
	const double J2 = m_J2[4];
	const double J3 = m_J2[8];
	const double g1 = J1 / J3;
	const double g2 = J2 / J3;
	const double wr = reference_velocity();
	//return
	return wr * (sqrt(g1) + sqrt(g2)) / sqrt(1 - pow(g2 - g1, 2));
}
double Top::critical_velocity(unsigned index) const
{
	//data
	const double J1 = m_J2[0];
	const double J2 = m_J2[4];
	const double J3 = m_J2[8];
	const double g1 = J1 / J3;
	const double g2 = J2 / J3;
	const double gp = index == 0 ? g2 : g1;
	const double wr = reference_velocity();
	//return
	return wr / sqrt(1 - gp);
}

bool Top::stability_check(unsigned index, double tilt_angle) const
{
	const double J1 = m_J2[0];
	const double J2 = m_J2[4];
	const double J3 = m_J2[8];
	const double g1 = J1 / J3;
	const double g2 = J2 / J3;
	return stability_check(index, g1, g2, tilt_angle);
}
bool Top::stability_check(unsigned index, double g1, double g2, double bt)
{
	//data
	double a, b, c, d;
	const double h1 = 1 - g1;
	const double h2 = 1 - g2;
	const double w3 = 1 / sqrt(cos(bt) * (index == 0 ? h2 : h1));
	//parameters
	if(index == 0)
	{
		a = (g2 * g2 - h1 * h1) / g1;
		c = 2 * (1 + g2 - g1) / (g1 * g2);
		d = -(1 + 2 * (g2 - g1)) / (g1 * g2 * h2 * h2);
		b = (1 + g2 * g2 - g1 * g1 + g2 - g1) / (g1 * g2 * h2);
	}
	else
	{
		a = (g1 * g1 - h2 * h2) / g2;
		c = 2 * (1 + g1 - g2) / (g1 * g2);
		d = -(1 + 2 * (g1 - g2)) / (g1 * g2 * h1 * h1);
		b = (1 + g1 * g1 - g2 * g2 + g1 - g2) / (g1 * g2 * h1);
	}
	//return
	const double w34 = w3 * w3 * w3 * w3;
	return 
		(a * pow(w3, 4) + b >= 0) && (c * pow(w3, 4) + d >= 0) &&
		(pow(a * pow(w3, 4) + b, 2) - 4 * (c * pow(w3, 4) + d) >= 0);
}