//std
#include <ctime>
#include <string>
#include <functional>

//ext
#include <GL/glew.h>
#include <freetype/freetype.h>

//rigid
#include "rigid-body/inc/scene/Font.hpp"
#include "rigid-body/inc/scene/Image.hpp"

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
	void setup_latex(void);
	void setup_buffers(void);
	void setup_freetype(void);
	void setup_uniforms(void);
	void setup_data_plot(void);
	void setup_data_mark(void);
	void setup_data_text(void);
	void setup_data_image(void);

	void setup_latex(const char*, const char*, unsigned);
	void setup_data_image(float*&, unsigned, float, float, float, unsigned, unsigned);
	void setup_data_text(float*&, const char*, float, float, float, unsigned, unsigned);

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
	clock_t m_time;
	float m_x1_min;
	float m_x1_max;
	float m_x2_min;
	float m_x2_max;
	float m_x3_min;
	float m_x3_max;
	Image* m_images;
	unsigned m_mode;
	unsigned m_frame;
	unsigned m_marks;
	unsigned m_width;
	unsigned m_height;
	unsigned m_frames;
	char m_label_1[20];
	char m_label_2[20];
	char m_label_3[20];
	GLuint m_vao_id_plot;
	GLuint m_vbo_id_plot;
	GLuint m_ibo_id_plot;
	GLuint m_vao_id_mark;
	GLuint m_vbo_id_mark;
	GLuint m_ibo_id_mark;
	GLuint m_vao_id_text;
	GLuint m_vbo_id_text;
	GLuint m_ibo_id_text;
	GLuint m_vao_id_image;
	GLuint m_vbo_id_image;
	GLuint m_ibo_id_image;
	GLuint m_program_id_plot;
	GLuint m_program_id_mark;
	GLuint m_program_id_text;
	GLuint m_program_id_image;
	static Plotter* m_master;
	GLuint m_texture_id_text;
	GLuint m_texture_id_image;
	const static float m_offset;
	std::function<bool(double, double, double)> m_function;
};