#ifndef _PDOBJECT_H_
#define _PDOBJECT_H_

#include "PDSigSlot.h"

#ifdef WIN32
#pragma warning(disable:4312) 
#endif


namespace PD {

/**
 * \brief 
 * \ingroup base
 */
class Object : public sigslot::has_slots<>
{
public:
	Object();
	virtual ~Object();
};

} //namespace PD {

#endif
