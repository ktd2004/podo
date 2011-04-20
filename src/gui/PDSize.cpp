#include "PDSize.h"

namespace PD {

Size::Size()
{
	m_width = m_height = 0;
}

Size::Size(int width, int height)
{
	m_width = width;
	m_height = height;
}

Size::Size(const Size& pt)
{
	m_width = pt.width();
	m_height = pt.height();
}

int Size::width() const { return m_width; }
int Size::height() const { return m_height; }

void Size::setWidth(const int width) { m_width = width; }
void Size::setHeight(const int height) { m_height = height; }

Size& Size::operator=(const Size& pt)
{
	m_width = pt.width();
	m_height = pt.height();

	return *this;
}

int Size::operator==(const Size& pt)
{
	if (width() != pt.width()) return 0;
	if (height() != pt.height()) return 0;

	return 1;
}
int Size::operator!=(const Size& pt)
{
	return !(*this == pt);
}




} //namespace PD {
