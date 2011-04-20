#ifndef _PDFILE_H_
#define _PDFILE_H_

#include "PDDateTime.h"
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef WIN32
#include <stdint.h> // for uint64_t
#include <utime.h>
#else
#define uint64_t __int64
#endif

namespace PD {

class FilePrivate;

/**
 * \brief file
 * \ingroup base
 */
class File
{
public:
	// same fcntl.h
	enum OpenMode { 
		ReadOnly	= 00000000, 
		WriteOnly	= 00000001, 
		ReadWrite	= 00000002, 

		Create		= 00000100,
		Truncate	= 00001000,
		Append		= 00002000,

		Binary		= 0x008000 // win32 only
		};
private:
	FilePrivate* d;

public:
	File(const char* filename="");
	~File();

	std::string name();

	bool isOpen();
	int open(int mode);
	int open(const char* filename, int mode);
	void close();

	int seek(int pos);
	uint64_t seek64(uint64_t pos);


	int read(unsigned char* buf, size_t bufSize);
	int write(unsigned char* buf, size_t bufSize);

	bool readLine(std::string& line);

	static bool exists(const char* filename);
	bool exists();

	static int size(const char* filename);
	static bool unlink(const char* filename);
	static bool fsync(const char* filename);

	static int utime(const char* filename, const DateTime& datetime);
};

} //namespace PD {

#endif
