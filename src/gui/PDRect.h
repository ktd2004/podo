#ifndef _PDRECT_H_
#define _PDRECT_H_

#include "PDPoint.h"
#include "PDSize.h"

namespace PD {

/**
 * \brief
 * \ingroup gui
 */
class Rect
{
private:
	int m_x1;
	int m_x2;
	int m_y1;
	int m_y2;

public:
	Rect();
	Rect(int x, int y, int w=0, int h=0);
	Rect(int x, int y, const Size& size);
	Rect(const Point& pt, int w=0, int h=0);
	Rect(const Point& pt, const Size& size);

	int x() const;
	int y() const;
	int width() const;
	int height() const;

	int left() const;
	int right() const;
	int top() const;
	int bottom() const;

	void setX(int x);
	void setY(int y);
	void setWidth(int w);
	void setHeight(int h);

	void setPosition(int x, int y);
	void setPosition(const Point& pt);
	void setSize(int w, int h);
	void setSize(const Size& size);

	void adjust(int dx, int dy, int dx2, int dy2);

	Rect normalized();

	bool intersect(const Rect& rect);

	bool contains(const Point& pt);
	bool contains(const int x, const int y);

	void print();

	Rect& operator=(const Rect& rect);
	int operator!=(const Rect& rect);
};

} //namespace PD {

#endif
