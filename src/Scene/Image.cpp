//def
#define STB_IMAGE_IMPLEMENTATION

//ext
#include "external/cpp/inc/stb_image.h"

//canvas
#include "rigid-body/inc/scene/Image.hpp"

//constructors
Image::Image(void) : m_data(nullptr)
{
	return;
}

//destructor
Image::~Image(void)
{
	if(m_data) stbi_image_free(m_data);
}

//data
unsigned Image::width(void) const
{
	return m_width;
}
unsigned Image::height(void) const
{
	return m_height;
}
std::string Image::path(void) const
{
	return m_path;
}
std::string Image::path(std::string path)
{
	return m_path = path;
}

//load
void Image::load(void)
{
	//load
	int w, h, c;
	if(m_data) stbi_image_free(m_data);
	stbi_set_flip_vertically_on_load(true);
	m_data = stbi_load(m_path.c_str(), &w, &h, &c, STBI_rgb_alpha);
	//check
	if(!m_data)
	{
		fprintf(stderr, "Error: Couldn't load image: %s!\n", m_path.c_str());
		exit(EXIT_FAILURE);
	}
	//setup
	m_width = w;
	m_height = h;
	m_offset = m_total_width;
	//total
	m_total_width += w;
	m_total_height = std::max(m_total_height, unsigned(h));
}

//coordinates
void Image::coordinates(float* coordinates) const
{
	coordinates[2] = 0;
	coordinates[0] = float(m_offset) / m_total_width;
	coordinates[3] = float(m_height) / m_total_height;
	coordinates[1] = float(m_offset + m_width) / m_total_width;
}

//static
unsigned Image::m_total_width = 0;
unsigned Image::m_total_height = 0;