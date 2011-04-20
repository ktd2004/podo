#ifndef _PDPROCESS_H_
#define _PDPROCESS_H_

#include "PDObject.h"
#include "PDString.h"

namespace PD {

class ProcessPrivate;

/**
 * \brief 
 * \ingroup base
 */
class Process : public Object
{
public:
	enum PipeType{
        ReadPipe = 0,
        WritePipe
    };  

private:
	ProcessPrivate* d;

public:
	Process();
	virtual ~Process();	

	std::string command();
	void setCommand(std::string cmd);

	int start();
	int start(std::string name);

	static int exec(std::string cmd);
	int pid();
	void kill();

	sigslot::signal1<std::string>  readStdOut;
	sigslot::signal1<std::string>  readStdErr;

};

} //namespace PD {

#endif
