//#pragma once
//
////ext
//#include "external/cpp/inc/freetype/freetype.h"
//
//class Font;
//
//class Character
//{
//public:
//	//constructors
//	Character(void);
//
//	//destructor
//	~Character(void);
//
//	//data
//	unsigned width(void) const;
//	unsigned height(void) const;
//	unsigned offset(void) const;
//	unsigned advance(void) const;
//	unsigned bearing(unsigned) const;
//	const unsigned char* data(void) const;
//
//	//draw
//	void coordinates(float*) const;
//
//	//setup
//	void setup(FT_Face, char);
//
//protected:
//	//data
//	char m_code;
//	unsigned m_width;
//	unsigned m_height;
//	unsigned m_offset;
//	unsigned m_advance;
//	unsigned char* m_data;
//	unsigned m_bearings[2];
//
//	//friends
//	friend class Font;
//};