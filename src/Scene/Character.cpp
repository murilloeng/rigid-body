////ext
//#include "freetype/freetype.h"
//
////rigid
//#include "rigid-body/inc/scene/Font.hpp"
//#include "rigid-body/inc/scene/Character.hpp"
//
////constructores
//Character::Character(void) : m_data(nullptr)
//{
//	return;
//}
//
////destructor
//Character::~Character(void)
//{
//	delete[] m_data;
//}
//
////data
//unsigned Character::width(void) const
//{
//	return m_width;
//}
//unsigned Character::height(void) const
//{
//	return m_height;
//}
//unsigned Character::offset(void) const
//{
//	return m_offset;
//}
//unsigned Character::advance(void) const
//{
//	return m_advance;
//}
//unsigned Character::bearing(unsigned index) const
//{
//	return m_bearings[index];
//}
//const unsigned char* Character::data(void) const
//{
//	return m_data;
//}
//
////draw
//void Character::coordinates(float* coordinates) const
//{
//	//data
//	const unsigned w = Font::width();
//	const unsigned h = Font::height();
//	//coordinates
//	coordinates[2 * 2 + 1] = coordinates[2 * 3 + 1] = 0;
//	coordinates[2 * 0 + 0] = coordinates[2 * 3 + 0] = float(m_offset) / w;
//	coordinates[2 * 0 + 1] = coordinates[2 * 1 + 1] = float(m_height) / h;
//	coordinates[2 * 1 + 0] = coordinates[2 * 2 + 0] = float(m_offset + m_width) / w;
//}
//
////setup
//void Character::setup(FT_Face face, char code)
//{
//	//setup
//	m_code = code;
//	m_width = face->glyph->bitmap.width;
//	m_height = face->glyph->bitmap.rows;
//	m_advance = face->glyph->advance.x / 64;
//	m_bearings[1] = face->glyph->bitmap_top;
//	m_bearings[0] = face->glyph->bitmap_left;
//	//buffer
//	if(m_data) delete[] m_data;
//	m_data = new unsigned char[m_width * m_height];
//	memcpy(m_data, face->glyph->bitmap.buffer, m_width * m_height * sizeof(unsigned char));
//}