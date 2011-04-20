#ifndef _PDPOINT_H_
#define _PDPOINT_H_

namespace PD {

/**
 * \brief
 * \ingroup gui
 */
class Point
{
private:
	int m_x;
	int m_y;

public:
	Point();
	Point(int x, int y);
	Point(const Point& pt);

	int x() const;
	int y() const;

	void setX(const int x);
	void setY(const int y);

	Point& operator=(const Point& pt);
	int operator==(const Point& pt);
	int operator!=(const Point& pt);
};

} //namespace PD {

#endif
