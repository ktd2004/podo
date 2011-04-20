#ifndef _PDFILE_P_H_
#define _PDFILE_P_H_

namespace PD {

class FilePrivate
{
public:
	int fd;
	std::string filename;

public:
	FilePrivate(const char* name)
	{
		fd = -1;
		filename = name;
	}
};
} //namespace PD {
#endif
