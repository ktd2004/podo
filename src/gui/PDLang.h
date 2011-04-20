#ifndef _PDLANG_H_
#define _PDLANG_H_

#include "PDGlobal.h"
#include <string>

namespace PD
{

class LangPrivate;

/**
 * \brief
 * \ingroup gui
 */
class Lang
{
private:
	LangPrivate* d;

public:
	Lang();
	~Lang();

	void setLanguage(const char* fileName);
	std::string tr(const std::string& group, const std::string& key);
	CountryCode countryCode();
};

}
#endif
