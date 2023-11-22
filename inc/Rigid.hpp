//std
#include <functional>

//math
#include "inc/linear/vec3.hpp"
#include "inc/linear/quat.hpp"
#include "inc/linear/mat3.hpp"

class Rigid
{
public:
	//constructors
	Rigid(void);

	//destructor
	~Rigid(void);

	//analysis
	void setup(void);
	void solve(void);

	//data
	unsigned m_ns;
	math::mat3 m_J;
	math::vec3 m_p_new;
	math::quat m_q_old, m_q_new;
	std::function<math::vec3(double)> m_m;
	math::vec3 m_w_old, m_a_old, m_s_old;
	math::vec3 m_w_new, m_a_new, m_s_new;
	double m_T, m_p, m_b, m_g, m_am, m_af, m_dt;
};