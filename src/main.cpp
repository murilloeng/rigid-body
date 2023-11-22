//rigid
#include "inc/rigid.hpp"

void example_1(void)
{
	//data
	Rigid rigid;
	const double dt = 0.01;
	const double tm = 2 - dt;
	//setup
	rigid.m_T = 10;
	rigid.m_J.zeros();
	rigid.m_J(0, 0) = 5;
	rigid.m_J(2, 2) = 1;
	rigid.m_J(1, 1) = 10;
	rigid.m_w_new.zeros();
	rigid.m_ns = unsigned(10 / dt);
	rigid.m_q_new = math::quat(1, 0, 0, 0);
	rigid.m_m = [dt, tm] (double t) {
		if(t <= tm) return math::vec3(20, 0, 0);
		else if(t <= tm + dt) return math::vec3(0, 0.2 / dt, 0);
		else return math::vec3(0, 0, 0);
	};
	//solve
}

int main(void)
{
	example_1();
	//return
	return 0;
}