#include "PDPoint.h"

namespace PD {

Point::Point()
{
	m_x = m_y = 0;
}

Point::Point(int x, int y)
{
	m_x = x;
	m_y = y;
}

Point::Point(const Point& pt)
{
	m_x = pt.x();
	m_y = pt.y();
}

int Point::x() const { return m_x; }
int Point::y() const { return m_y; }

void Point::setX(const int x) { m_x = x; }
void Point::setY(const int y) { m_y = y; }

Point& Point::operator=(const Point& pt)
{
	m_x = pt.x();
	m_y = pt.y();

	return *this;
}

int Point::operator==(const Point& pt)
{
	if(x() != pt.x()) return 0;
	if(y() != pt.y()) return 0;

	return 1;
}
int Point::operator!=(const Point& pt)
{
	return !(*this == pt);
}




} //namespace PD {
