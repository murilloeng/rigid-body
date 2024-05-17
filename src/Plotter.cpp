//std
#include <cstdio>

//ext
#include <GL/glew.h>
#include <GL/freeglut.h>

//rigid
#include "rigid-body/inc/Plotter.hpp"

//constructor
Plotter::Plotter(void)
{
	m_master = this;
}

//destructor
Plotter::~Plotter(void)
{
	if(glIsBuffer(m_vao_id_plot)) glDeleteBuffers(1, &m_vao_id_plot);
	if(glIsBuffer(m_vbo_id_plot)) glDeleteBuffers(1, &m_vbo_id_plot);
	if(glIsBuffer(m_ibo_id_plot)) glDeleteBuffers(1, &m_ibo_id_plot);
	if(glIsBuffer(m_vao_id_text)) glDeleteBuffers(1, &m_vao_id_text);
	if(glIsBuffer(m_vbo_id_text)) glDeleteBuffers(1, &m_vbo_id_text);
	if(glIsBuffer(m_ibo_id_text)) glDeleteBuffers(1, &m_ibo_id_text);
	if(glIsBuffer(m_vao_id_mark)) glDeleteBuffers(1, &m_vao_id_mark);
	if(glIsBuffer(m_vbo_id_mark)) glDeleteBuffers(1, &m_vbo_id_mark);
	if(glIsBuffer(m_ibo_id_mark)) glDeleteBuffers(1, &m_ibo_id_mark);
	if(glIsProgram(m_program_id_plot)) glDeleteProgram(m_program_id_plot);
	if(glIsProgram(m_program_id_text)) glDeleteProgram(m_program_id_text);
	if(glIsProgram(m_program_id_mark)) glDeleteProgram(m_program_id_mark);
}

//draw
void Plotter::setup(void)
{
	//color
	glClearColor(1, 1, 1, 1);
	//setup
	setup_buffers();
	setup_program(m_program_id_plot, "shd/plot.vert", "shd/plot.frag");
	// setup_program(m_program_id_text, "shd/text.vert", "shd/text.frag");
	// setup_program(m_program_id_mark, "shd/mark.vert", "shd/mark.frag");
	//data
	setup_data();
}
void Plotter::setup_data(void)
{
	m_frame = 0;
	glUseProgram(m_program_id_plot);
	glUniform1ui(glGetUniformLocation(m_program_id_plot, "frame"), 0);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "x1_min"), m_x1_min);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "x1_max"), m_x1_max);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "x2_min"), m_x2_min);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "x2_max"), m_x2_max);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "x3_min"), m_x3_min);
	glUniform1f(glGetUniformLocation(m_program_id_plot, "x3_max"), m_x3_max);
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
	const unsigned ibo_plot_data[] = {0, 1, 2, 0, 2, 3};
	const float vbo_plot_data[] = {-1, -1, +1, -1, +1, +1, -1, +1};
	//buffers plot
	glBindVertexArray(m_vao_id_plot);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id_plot);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id_plot);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vbo_plot_data, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned), ibo_plot_data, GL_DYNAMIC_DRAW);
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
	//vao mark
	glBindVertexArray(m_vao_id_mark);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id_mark);
	//attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (unsigned*) (0 * sizeof(float)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (unsigned*) (2 * sizeof(float)));
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
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutInitContextVersion(4, 6);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	//window
	glutCreateWindow("Canvas");
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
	m_master->m_frame++;
	glUniform1ui(glGetUniformLocation(m_master->m_program_id_plot, "frame"), m_master->m_frame);
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
	//glut
	glutSwapBuffers();
}
void Plotter::callback_reshape(int width, int height)
{
	//plot
	glUseProgram(m_master->m_program_id_plot);
	glUniform1ui(glGetUniformLocation(m_master->m_program_id_plot, "width"), width);
	glUniform1ui(glGetUniformLocation(m_master->m_program_id_plot, "height"), height);
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