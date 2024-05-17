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
	return;
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
	setup_program(m_program_id_plot, "shd/plot.vert", "shd/plot.frag");
	setup_program(m_program_id_text, "shd/text.vert", "shd/text.frag");
	setup_program(m_program_id_mark, "shd/mark.vert", "shd/mark.frag");
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
		fprintf(stderr, "Error compiling shader!\nError log: %s\n", log);
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
	setup_shader(program_id, GL_VERTEX_SHADER, "");
	setup_shader(program_id, GL_FRAGMENT_SHADER, "");
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
void Plotter::plot(void) const
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
	//callbacks
	// glutIdleFunc(callback_idle);
	// glutMouseFunc(callback_mouse);
	// glutMotionFunc(callback_motion);
	glutDisplayFunc(callback_display);
	// glutReshapeFunc(callback_reshape);
	// glutSpecialFunc(callback_special);
	// glutMouseWheelFunc(callback_wheel);
	// glutKeyboardFunc(callback_keyboard);
	//loop
	glutMainLoop();
}

//callbacks
void Plotter::callback_display(void)
{
	//clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glut
	glutSwapBuffers();
}