//#pragma once
//
////std
//#include <string>
//
////ext
//#include "external/cpp/inc/freetype/freetype.h"
//
////rigid
//#include "rigid-body/inc/scene/Character.hpp"
//
//class Plotter;
//
//class Font
//{
//public:
//	//constructors
//	Font(void);
//
//	//destructor
//	~Font(void);
//
//	//data
//	static unsigned width(void);
//	static unsigned height(void);
//
//	static unsigned pixels_size(void);
//	static unsigned pixels_size(unsigned);
//
//	Character& character(unsigned);
//	const Character& character(unsigned) const;
//
//	//setup
//	void setup_texture(void);
//	void setup(unsigned&, unsigned&);
//
//protected:
//	//data
//	FT_Face m_face;
//	FT_Library m_library;
//	Character m_chars[128];
//	static unsigned m_width;
//	static unsigned m_height;
//	static unsigned m_pixels_size;
//
//	//friends
//	friend class Plotter;
//};