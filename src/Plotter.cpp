//std
#include <cstdio>

//ext
#include <GL/glew.h>
#include <GL/freeglut.h>

//rigid
#include "rigid-body/inc/Plotter.hpp"


//constructor
Plotter::Plotter(void) : m_font(new Font), m_frame(0), m_marks(9), m_frames(200)
{
	m_master = this;
}

//destructor
Plotter::~Plotter(void)
{
	delete m_font;
	if(glIsBuffer(m_vao_id_plot)) glDeleteBuffers(1, &m_vao_id_plot);
	if(glIsBuffer(m_vbo_id_plot)) glDeleteBuffers(1, &m_vbo_id_plot);
	if(glIsBuffer(m_ibo_id_plot)) glDeleteBuffers(1, &m_ibo_id_plot);
	if(glIsBuffer(m_vao_id_mark)) glDeleteBuffers(1, &m_vao_id_mark);
	if(glIsBuffer(m_vbo_id_mark)) glDeleteBuffers(1, &m_vbo_id_mark);
	if(glIsBuffer(m_ibo_id_mark)) glDeleteBuffers(1, &m_ibo_id_mark);
	if(glIsBuffer(m_vao_id_text)) glDeleteBuffers(1, &m_vao_id_text);
	if(glIsBuffer(m_vbo_id_text)) glDeleteBuffers(1, &m_vbo_id_text);
	if(glIsBuffer(m_ibo_id_text)) glDeleteBuffers(1, &m_ibo_id_text);
	if(glIsProgram(m_program_id_plot)) glDeleteProgram(m_program_id_plot);
	if(glIsProgram(m_program_id_mark)) glDeleteProgram(m_program_id_mark);
	if(glIsProgram(m_program_id_text)) glDeleteProgram(m_program_id_text);
}

void Plotter::setup(void)
{
	//color
	glClearColor(1, 1, 1, 1);
	//setup
	setup_buffers();
	setup_freetype();
	setup_program(m_program_id_plot, "shd/plot.vert", "shd/plot.frag");
	setup_program(m_program_id_mark, "shd/mark.vert", "shd/mark.frag");
	setup_program(m_program_id_text, "shd/text.vert", "shd/text.frag");
	//data
	setup_data();
	setup_uniforms();
}
//draw
void Plotter::setup_data(void)
{
	setup_data_plot();
	setup_data_mark();
	setup_data_text();
}
void Plotter::setup_buffers(void)
{
	//create
	glGenBuffers(1, &m_vbo_id_plot);
	glGenBuffers(1, &m_vbo_id_text);
	glGenBuffers(1, &m_vbo_id_mark);
	glGenBuffers(1, &m_ibo_id_plot);
	glGenBuffers(1, &m_ibo_id_text);
	glGenBuffers(1, &m_ibo_id_mark);
	glGenVertexArrays(1, &m_vao_id_plot);
	glGenVertexArrays(1, &m_vao_id_text);
	glGenVertexArrays(1, &m_vao_id_mark);
	//buffers plot
	glBindVertexArray(m_vao_id_plot);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id_plot);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id_plot);
	//attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (unsigned*) (0 * sizeof(float)));
	//vao mark
	glBindVertexArray(m_vao_id_mark);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id_mark);
	//attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (unsigned*) (0 * sizeof(float)));
	//vao text
	glBindVertexArray(m_vao_id_text);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id_text);
	//attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (unsigned*) (0 * sizeof(float)));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (unsigned*) (2 * sizeof(float)));
}
void Plotter::setup_freetype(void)
{
	//font
	unsigned w = 0;
	unsigned h = 0;
	m_font->setup(w, h);
	glGenTextures(1, &m_texture_id);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//texture
	Font::m_width = w;
	Font::m_height = h;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);
	//texture data
	m_font->setup_texture();
}
void Plotter::setup_uniforms(void)
{
	glUseProgram(m_program_id_plot);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "time"), 0);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "offset"), m_offset);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "x1_min"), m_x1_min);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "x1_max"), m_x1_max);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "x2_min"), m_x2_min);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "x2_max"), m_x2_max);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "x3_min"), m_x3_min);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "x3_max"), m_x3_max);
}
void Plotter::setup_data_plot(void)
{
	//data
	const float ps = 1 - m_offset;
	const unsigned ibo_data[] = {0, 1, 2, 0, 2, 3};
	const float vbo_data[] = {-ps, -ps, +ps, -ps, +ps, +ps, -ps, +ps};
	//transfer data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id_plot);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id_plot);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vbo_data), vbo_data, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ibo_data), ibo_data, GL_DYNAMIC_DRAW);
}
void Plotter::setup_data_mark(void)
{
	//data
	const float ms = m_offset / 2;
	const float ps = 1 - m_offset;
	unsigned ibo_data[8 * (1 + m_marks)];
	float vbo_data[8 * (1 + 2 * m_marks)];
	//outer lines
	for(unsigned i = 0; i < 4; i++)
	{
		ibo_data[2 * i + 0] = (i + 0) % 4;
		ibo_data[2 * i + 1] = (i + 1) % 4;
		vbo_data[2 * i + 0] = i == 0 || i == 3 ? -ps : +ps;
		vbo_data[2 * i + 1] = i == 0 || i == 1 ? -ps : +ps;
	}
	//inner lines
	for(unsigned i = 0; i < m_marks; i++)
	{
		ibo_data[2 * (i + 0 * m_marks + 4) + 0] = i + 0 * m_marks + 4;
		ibo_data[2 * (i + 0 * m_marks + 4) + 1] = i + 1 * m_marks + 4;
		ibo_data[2 * (i + 1 * m_marks + 4) + 0] = i + 2 * m_marks + 4;
		ibo_data[2 * (i + 1 * m_marks + 4) + 1] = i + 3 * m_marks + 4;
		ibo_data[2 * (i + 2 * m_marks + 4) + 0] = i + 4 * m_marks + 4;
		ibo_data[2 * (i + 2 * m_marks + 4) + 1] = i + 5 * m_marks + 4;
		ibo_data[2 * (i + 3 * m_marks + 4) + 0] = i + 6 * m_marks + 4;
		ibo_data[2 * (i + 3 * m_marks + 4) + 1] = i + 7 * m_marks + 4;
	}
	for(unsigned i = 0; i < m_marks; i++)
	{
		vbo_data[2 * (i + 0 * m_marks + 4) + 1] = -ps;
		vbo_data[2 * (i + 2 * m_marks + 4) + 0] = +ps;
		vbo_data[2 * (i + 4 * m_marks + 4) + 1] = +ps;
		vbo_data[2 * (i + 6 * m_marks + 4) + 0] = -ps;
		vbo_data[2 * (i + 1 * m_marks + 4) + 1] = -ps + ms;
		vbo_data[2 * (i + 3 * m_marks + 4) + 0] = +ps - ms;
		vbo_data[2 * (i + 5 * m_marks + 4) + 1] = +ps - ms;
		vbo_data[2 * (i + 7 * m_marks + 4) + 0] = -ps + ms;
		vbo_data[2 * (i + 0 * m_marks + 4) + 0] = 2 * ps * float(i + 1) / (m_marks + 1) - ps;
		vbo_data[2 * (i + 1 * m_marks + 4) + 0] = 2 * ps * float(i + 1) / (m_marks + 1) - ps;
		vbo_data[2 * (i + 2 * m_marks + 4) + 1] = 2 * ps * float(i + 1) / (m_marks + 1) - ps;
		vbo_data[2 * (i + 3 * m_marks + 4) + 1] = 2 * ps * float(i + 1) / (m_marks + 1) - ps;
		vbo_data[2 * (i + 4 * m_marks + 4) + 0] = ps - 2 * ps * float(i + 1) / (m_marks + 1);
		vbo_data[2 * (i + 5 * m_marks + 4) + 0] = ps - 2 * ps * float(i + 1) / (m_marks + 1);
		vbo_data[2 * (i + 6 * m_marks + 4) + 1] = ps - 2 * ps * float(i + 1) / (m_marks + 1);
		vbo_data[2 * (i + 7 * m_marks + 4) + 1] = ps - 2 * ps * float(i + 1) / (m_marks + 1);
	}
	//transfer data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id_mark);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id_mark);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vbo_data), vbo_data, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ibo_data), ibo_data, GL_DYNAMIC_DRAW);
}
void Plotter::setup_data_text(void)
{
	//data
	float vbo_data[32 * (m_marks + 2)];
	unsigned ibo_data[48 * (m_marks + 2)];
	//ibo data
	for(unsigned i = 0; i < 8 * (m_marks + 2); i++)
	{
		ibo_data[6 * i + 0] = 4 * i + 0;
		ibo_data[6 * i + 1] = 4 * i + 1;
		ibo_data[6 * i + 2] = 4 * i + 2;
		ibo_data[6 * i + 3] = 4 * i + 0;
		ibo_data[6 * i + 4] = 4 * i + 2;
		ibo_data[6 * i + 5] = 4 * i + 3;
	}
	//vbo data
	// for (unsigned i = 0; i < count; i++)
	// {
	// 	/* code */
	// }
	
	//text
	// const unsigned wf = Font::width();
	// const unsigned hf = Font::height();
	// const int w = m_font->m_chars['A'].width();
	// const int h = m_font->m_chars['A'].height();
	// const int x = m_font->m_chars['A'].offset();
	// ibo_data[3 * 0 + 0] = 0;
	// ibo_data[3 * 0 + 1] = 1;
	// ibo_data[3 * 0 + 2] = 2;
	// ibo_data[3 * 1 + 0] = 0;
	// ibo_data[3 * 1 + 1] = 2;
	// ibo_data[3 * 1 + 2] = 3;
	// vbo_data[4 * 0 + 0] = 0.4;
	// vbo_data[4 * 0 + 1] = 0.4;
	// vbo_data[4 * 0 + 2] = float(x) / wf;
	// vbo_data[4 * 0 + 3] = float(h) / hf;
	// vbo_data[4 * 1 + 0] = 0.6;
	// vbo_data[4 * 1 + 1] = 0.4;
	// vbo_data[4 * 1 + 2] = float(x + w) / wf;
	// vbo_data[4 * 1 + 3] = float(h) / hf;
	// vbo_data[4 * 2 + 0] = 0.6;
	// vbo_data[4 * 2 + 1] = 0.6;
	// vbo_data[4 * 2 + 2] = float(x + w) / wf;
	// vbo_data[4 * 2 + 3] = float(0) / hf;
	// vbo_data[4 * 3 + 0] = 0.4;
	// vbo_data[4 * 3 + 1] = 0.6;
	// vbo_data[4 * 3 + 2] = float(x) / wf;
	// vbo_data[4 * 3 + 3] = float(0) / hf;
	//transfer data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id_text);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id_text);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vbo_data), vbo_data, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ibo_data), ibo_data, GL_DYNAMIC_DRAW);
}
void Plotter::setup_shader(GLuint program_id, GLenum shader_type, const char* shader_path)
{
	//shader
	GLuint shader_id = glCreateShader(shader_type);
	//source
	std::string shader_source;
	load_file(shader_source, shader_path);
	const GLchar* p = shader_source.c_str();
	glShaderSource(shader_id, 1, &p, nullptr);
	//compile
	GLint status;
	GLchar log[1024];
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
	if(status == 0)
	{
		glGetShaderInfoLog(shader_id, sizeof(log), nullptr, log);
		fprintf(stderr, "Error compiling shader %d!\nError log: %s\n", shader_type, log);
		exit(EXIT_FAILURE);
	}
	//attach
	glAttachShader(program_id, shader_id);
}
void Plotter::setup_program(GLuint& program_id, const char* vertex_shader_path, const char* fragment_shader_path)
{
	//program
	program_id = glCreateProgram();
	//check
	if(program_id == 0)
	{
		fprintf(stderr, "Error creating shader program!\n");
		exit(EXIT_FAILURE);
	}
	//shaders
	setup_shader(program_id, GL_VERTEX_SHADER, vertex_shader_path);
	setup_shader(program_id, GL_FRAGMENT_SHADER, fragment_shader_path);
	//link
	GLint status;
	GLchar log[1024];
	glLinkProgram(program_id);
	glGetProgramiv(program_id, GL_LINK_STATUS, &status);
	if(status == 0)
	{
		glGetProgramInfoLog(program_id, sizeof(log), nullptr, log);
		fprintf(stderr, "Error linking shader program: %s\n", log);
		exit(EXIT_FAILURE);
	}
	//validate
	glValidateProgram(program_id);
	glGetProgramiv(program_id, GL_VALIDATE_STATUS, &status);
	if(status == 0)
	{
		glGetProgramInfoLog(program_id, sizeof(log), nullptr, log);
		fprintf(stderr, "Error validating shader program: %s\n", log);
		exit(EXIT_FAILURE);
	}
}

//load
bool Plotter::load_file(std::string& source, const char* path)
{
	//open
	FILE* file = fopen(path, "r");
	//check
	if(!file) return false;
	//read
	source.clear();
	while(!feof(file)) source += fgetc(file);
	source.back() = '\0';
	//close
	fclose(file);
	//return
	return true;
}

//plot
void Plotter::plot(void)
{
	int argc = 0;
	glutInit(&argc, nullptr);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(0, 0);
	glutInitContextVersion(4, 6);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	//window
	glutCreateWindow("Rigid Body");
	//glew
	if(glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Error: can't setup glew!\n");
		exit(EXIT_FAILURE);
	}
	setup();
	//callbacks
	glutIdleFunc(callback_idle);
	// glutMouseFunc(callback_mouse);
	// glutMotionFunc(callback_motion);
	glutDisplayFunc(callback_display);
	glutReshapeFunc(callback_reshape);
	// glutSpecialFunc(callback_special);
	// glutMouseWheelFunc(callback_wheel);
	glutKeyboardFunc(callback_keyboard);
	//loop
	glutMainLoop();
}

//callbacks
void Plotter::callback_idle(void)
{
	glUseProgram(m_master->m_program_id_plot);
	m_master->m_frame = (m_master->m_frame + 1) % m_master->m_frames;
	glUniform1f(glGetUniformLocation(m_master->m_program_id_plot, "time"), float(m_master->m_frame) / m_master->m_frames);
	glutPostRedisplay();
}
void Plotter::callback_display(void)
{
	//clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//draw plot
	glUseProgram(m_master->m_program_id_plot);
	glBindVertexArray(m_master->m_vao_id_plot);
	glBindBuffer(GL_ARRAY_BUFFER, m_master->m_vbo_id_plot);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_master->m_ibo_id_plot);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	//draw mark
	glUseProgram(m_master->m_program_id_mark);
	glBindVertexArray(m_master->m_vao_id_mark);
	glBindBuffer(GL_ARRAY_BUFFER, m_master->m_vbo_id_mark);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_master->m_ibo_id_mark);
	glDrawElements(GL_LINES, 8 * (1 + m_master->m_marks), GL_UNSIGNED_INT, nullptr);
	//draw text
	glUseProgram(m_master->m_program_id_text);
	glBindVertexArray(m_master->m_vao_id_text);
	glBindTexture(GL_TEXTURE_2D, m_master->m_texture_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_master->m_vbo_id_text);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_master->m_ibo_id_text);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	//glut
	glutSwapBuffers();
}
void Plotter::callback_reshape(int width, int height)
{
	//plot
	glUseProgram(m_master->m_program_id_plot);
	glUniform1ui(glGetUniformLocation(m_master->m_program_id_plot, "width"), width);
	glUniform1ui(glGetUniformLocation(m_master->m_program_id_plot, "height"), height);
	//mark
	glUseProgram(m_master->m_program_id_mark);
	glUniform1ui(glGetUniformLocation(m_master->m_program_id_mark, "width"), width);
	glUniform1ui(glGetUniformLocation(m_master->m_program_id_mark, "height"), height);
	//viewport
	glViewport(0, 0, width, height);
	//redraw
	glutPostRedisplay();
}
void Plotter::callback_keyboard(unsigned char key, int, int)
{
	if(key == 27)
	{
		glutDestroyWindow(glutGetWindow());
	}
}

//static data
Plotter* Plotter::m_master = nullptr;
const float Plotter::m_offset = 0.10f;