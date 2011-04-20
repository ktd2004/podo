#include "PDEvent.h"

namespace PD {

Event::Event() 
{ 
	m_widget = 0;
	m_msg = MsgNone;
}

Event::Event(Msg msg)
{ 
	m_msg = msg;
	m_widget = 0;
}

} //namespace PD {
