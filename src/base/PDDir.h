#ifndef _PDDIR_H_
#define _PDDIR_H_

#include <stdio.h>
#include <string>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "PDString.h"

namespace PD {

class DirPrivate;

/**
 * \brief dir
 * \ingroup base
 */
class Dir
{
public:
	
	enum Filter { 
		NoFilter	= 0x0000, 		// no filter
		Dirs		= 0x0001, 		// list all directories
		Files		= 0x0002, 		// list files only
		SymLinks	= 0x0004, 		// dont't support symbolic links.
		NoSymLinks	= 0x0008, 		// dont't support symbolic links.
		Hidden		= 0x0010, 		// files stating with a .
		System		= 0x0020, 		// list system files(fifo, socket and device files)
		CharDevice 	= 0x0040,		// char device
		BlockDevice	= 0x0080,		// block device3
		};
	enum FileType {
		UnknownFile = 0,
		RegularFile	= 1,
		DirectoryFile =	2
		};

private:
	DirPrivate* d;

public:
	Dir(const char* path="");
	~Dir();

	void setFilter(int f);
	static bool exists(const char* path);
	bool exists();
	String::StringList entryList(int f=NoFilter,
		std::string nameFilter="");

	String::StringList entryList(const char* path, int f=NoFilter,
		std::string nameFilter="");
	uintmax_t size(const char* path);
};

} //namespace PD {

#endif
