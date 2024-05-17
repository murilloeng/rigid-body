//std
#include <string>
#include <functional>

//ext
#include <GL/glew.h>

class Plotter
{
public:
	//constructor
	Plotter(void);

	//destructor
	~Plotter(void);

	//draw
	void setup(void);
	void setup_data(void);
	void setup_buffers(void);
	static void setup_shader(GLuint, GLenum, const char*);
	static void setup_program(GLuint&, const char*, const char*);

	//load
	static bool load_file(std::string&, const char*);

	//plot
	void plot(void);

	//callbacks
	static void callback_idle(void);
	static void callback_display(void);
	static void callback_reshape(int, int);
	static void callback_keyboard(unsigned char, int, int);

	//data
	bool m_grid;
	float m_x1_min;
	float m_x1_max;
	float m_x2_min;
	float m_x2_max;
	float m_x3_min;
	float m_x3_max;
	unsigned m_frame;
	GLuint m_vao_id_plot;
	GLuint m_vbo_id_plot;
	GLuint m_ibo_id_plot;
	GLuint m_vao_id_text;
	GLuint m_vbo_id_text;
	GLuint m_ibo_id_text;
	GLuint m_vao_id_mark;
	GLuint m_vbo_id_mark;
	GLuint m_ibo_id_mark;
	GLuint m_program_id_plot;
	GLuint m_program_id_text;
	GLuint m_program_id_mark;
	static Plotter* m_master;
	std::function<bool(double, double, double)> m_function;
};