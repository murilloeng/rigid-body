//std
#include <string>
#include <functional>

//ext
#include <GL/glew.h>
#include <freetype/freetype.h>

//rigid
#include "rigid-body/inc/scene/Font.hpp"

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
	void setup_freetype(void);
	void setup_uniforms(void);
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
	Font* m_font;
	float m_x1_min;
	float m_x1_max;
	float m_x2_min;
	float m_x2_max;
	float m_x3_min;
	float m_x3_max;
	unsigned m_frame;
	unsigned m_marks;
	unsigned m_frames;
	GLuint m_texture_id;
	GLuint m_vao_id_plot;
	GLuint m_vbo_id_plot;
	GLuint m_ibo_id_plot;
	GLuint m_vao_id_mark;
	GLuint m_vbo_id_mark;
	GLuint m_ibo_id_mark;
	GLuint m_vao_id_text;
	GLuint m_vbo_id_text;
	GLuint m_ibo_id_text;
	GLuint m_program_id_plot;
	GLuint m_program_id_mark;
	GLuint m_program_id_text;
	static Plotter* m_master;
	const static float m_offset;
	std::function<bool(double, double, double)> m_function;
};