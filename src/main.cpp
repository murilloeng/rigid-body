//std
#include <cstdio>

//math
#include "inc/linear/vec3.hpp"
#include "inc/linear/mat3.hpp"
#include "inc/linear/quat.hpp"

void test_1(void)
{
	//data
	double t = 0;
	const double T = 10;
	const double M = 20;
	const double g = 1.00;
	const double b = 0.50;
	const double h = 0.001;
	math::mat3 J, K, C, S;
	math::quat q_old, q_new;
	math::vec3 p_new, w_old, w_new, a_old, a_new, dp, r;
	FILE* file = fopen("data/test-1.dat", "w");
	//setup
	J.zeros();
	J(0, 0) = 5;
	J(1, 1) = 5;
	J(2, 2) = 1;
	p_new.zeros();
	a_new.zeros();
	a_old.zeros();
	J(0, 0) = J(1, 1) = 5;
	const math::vec3 e3(0, 0, 1);
	w_old = w_new = math::vec3(0, 0, 50);
	q_old = q_new = math::vec3(0.3, 0, 0).quaternion();
	const math::vec3 s3 = q_new.conjugate(e3);
	//print
	fprintf(file, "%+.6e ", t);
	fprintf(file, "%+.6e %+.6e %+.6e ", p_new[0], p_new[1], p_new[2]);
	fprintf(file, "%+.6e %+.6e %+.6e ", w_new[0], w_new[1], w_new[2]);
	fprintf(file, "%+.6e %+.6e %+.6e ", a_new[0], a_new[1], a_new[2]);
	fprintf(file, "%+.6e %+.6e %+.6e %+.6e\n", q_new[0], q_new[1], q_new[2], q_new[3]);
	//time loop
	while(t < T)
	{
		//predictor
		a_new = a_old;
		w_new = w_old + h * a_old;
		p_new = h * w_old + h * h / 2 * a_old;
		q_new = q_old * p_new.quaternion();
		//corrector
		for(unsigned i = 0; i < 10; i++)
		{
			//residue
			r = J * a_new + w_new.cross(J * w_new) + M * s3.cross(q_new.conjugate(e3));
			//check
			if(r.norm() < 1e-5 * M)
			{
				t += h;
				q_old = q_new;
				w_old = w_new;
				a_old = a_new;
				fprintf(file, "%+.6e ", t);
				fprintf(file, "%+.6e %+.6e %+.6e ", p_new[0], p_new[1], p_new[2]);
				fprintf(file, "%+.6e %+.6e %+.6e ", w_new[0], w_new[1], w_new[2]);
				fprintf(file, "%+.6e %+.6e %+.6e ", a_new[0], a_new[1], a_new[2]);
				fprintf(file, "%+.6e %+.6e %+.6e %+.6e\n", q_new[0], q_new[1], q_new[2], q_new[3]);
				break;
			}
			//tangent
			C = w_new.spin() * J - (J * w_new).spin();
			K = M * s3.spin() * q_new.conjugate().rotation() * e3.spin();
			S = g / b / h * C + J / b / h / h + K * p_new.rotation_gradient();
			//update
			dp = -S.inverse() * r;
			p_new += dp;
			w_new += g * dp / b / h;
			a_new += dp / b / h / h;
		}
	}
	fclose(file);
}

int main(void)
{
	test_1();
	return 0;
}