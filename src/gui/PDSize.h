#ifndef _PDSIZE_H_
#define _PDSIZE_H_

namespace PD {

/**
 * \brief 
 * \ingroup gui
 */
class Size
{
private:
	int m_width;
	int m_height;

public:
	Size();
	Size(int w, int h);
	Size(const Size& pt);

	int width() const;
	int height() const;

	void setWidth(const int width);
	void setHeight(const int height);

	Size& operator=(const Size& pt);
	int operator==(const Size& pt);
	int operator!=(const Size& pt);
};

} //namespace PD {

#endif
