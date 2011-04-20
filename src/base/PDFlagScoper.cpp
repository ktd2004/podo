#include "PDFlagScoper.h"
#include "PDFlagScoper_p.hpp"
#include <assert.h>

namespace PD {

/**
 * \brief 생성자
 *
 * bool변수값을 true/false로 설정하고 scope가 벗어나면 다시 초기화시키는\n
 * helper class
 *
 * \param flag
 * \param defaultVal
 */
FlagScoper::FlagScoper(bool* flag, bool defaultVal/*=true*/)
{
	assert(flag);

	d = new FlagScoperPrivate(flag, defaultVal);
}

/**
 * \brief 소멸자
 */
FlagScoper::~FlagScoper()
{
	delete d;
}

} //namespace
