#ifndef _PDColor_H_
#define _PDColor_H_

#ifdef WIN32
#undef Color
#endif

namespace PD {

class Color
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	Color();
	Color(unsigned char red, unsigned char green, unsigned char blue,
		unsigned alpha=0);
	
	int operator!=(const Color& c);
	int operator==(const Color& c);
	Color& operator=(const Color& c);
	operator int();
};

extern Color white;
extern Color black;
extern Color red;
extern Color green;
extern Color blue;
extern Color yellow;
extern Color cyan;
extern Color magenta;

extern Color gray;
extern Color lightgray;
extern Color darkgray;

} //namespace PD

#endif
