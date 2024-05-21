//std
#include <filesystem>

//ext
#include "external/cpp/inc/GL/glew.h"

//rigid
#include "rigid-body/inc/scene/Font.hpp"

//constructors
Font::Font(void) : m_face(nullptr)
{
	return;
}

//destructor
Font::~Font(void)
{
	FT_Done_Face(m_face);
}

//data
unsigned Font::width(void)
{
	return m_width;
}
unsigned Font::height(void)
{
	return m_height;
}

unsigned Font::pixels_size(void)
{
	return m_pixels_size;
}
unsigned Font::pixels_size(unsigned pixels_size)
{
	return m_pixels_size = pixels_size;
}

Character& Font::character(unsigned index)
{
	return m_chars[index];
}
const Character& Font::character(unsigned index) const
{
	return m_chars[index];
}

//setup
void Font::setup_texture(void)
{
	for(unsigned i = 0; i < 128; i++)
	{
		const unsigned w = m_chars[i].m_width;
		const unsigned h = m_chars[i].m_height;
		const unsigned x = m_chars[i].m_offset;
		const unsigned char* data = m_chars[i].m_data;
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, w, h, GL_RED, GL_UNSIGNED_BYTE, data);
	}
}
void Font::setup(unsigned& w, unsigned& h)
{
	//library
	if(FT_Init_FreeType(&m_library))
	{
		fprintf(stderr, "Error: Unable to init FreeType Library!\n");
		exit(EXIT_FAILURE);
	}
	//font
	FT_Done_Face(m_face);
	if(FT_New_Face(m_library, "/usr/share/fonts/truetype/msttcorefonts/Courier_New.ttf", 0, &m_face))
	{
		fprintf(stderr, "Error: Failed to load font!\n");
		exit(EXIT_FAILURE);
	}
	//size
	if(FT_Set_Pixel_Sizes(m_face, 0, m_pixels_size))
	{
		fprintf(stderr, "Error: Failed to set font size!\n");
		exit(EXIT_FAILURE);
	}
	//characters
	for(unsigned i = 0; i < 128; i++)
	{
		//load
		if(FT_Load_Char(m_face, i, FT_LOAD_RENDER))
		{
			fprintf(stderr, "Error: Failed to load glyph %d from font!\n", i);
			exit(EXIT_FAILURE);
		}
		//setup
		m_chars[i].m_offset = w;
		m_chars[i].setup(m_face, i);
		//update
		w += m_chars[i].m_width;
		h = std::max(h, m_chars[i].m_height);
	}
}

//static
unsigned Font::m_width;
unsigned Font::m_height;
unsigned Font::m_pixels_size = 256;