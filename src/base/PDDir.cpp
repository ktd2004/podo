/* 
   Copyright 2011 PODO. 
   This file is part of PODO. 
   
   PODO is free software: you can redistribute it and/or modify 
   it under the terms of the GNU Lesser General Public License as  
   published by the Free Software Foundation, either version 3 of  
   the License, or (at your option) any later version. 
   
   PODO is distributed in the hope that it will be useful, 
   but WITHOUT ANY WARRANTY; without even the implied warranty of 
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
   GNU Lesser General Public License for more details. 
   
   You should have received a copy of the GNU Lesser General Public  
   License along with PODO. If not, see <http://www.gnu.org/licenses/>. 
 */
#include "PDDir.h"
#include <dirent.h>
#include <string.h>
#include "PDDir_p.hpp"

namespace PD {

/**
 * \brief 생성자
 *
 * \param path
 */
Dir::Dir(const char* path/*=""*/)
{
	d = new DirPrivate(path);
}

/**
 * \brief 소멸자
 *
 */
Dir::~Dir()
{
	delete d;
}

/**
 * \brief 필터 설정
 *
 *
 * \param f Dir::Filter를 OR연산 
 */
void Dir::setFilter(int f)
{
	if(f == NoFilter)
	{
		d->filter &= ((int)f);
	}
	else d->filter |= ((int)f);
}

/**
 * \brief path가 존재하는지 확인
 *
 * \param path
 *
 * \return true/false
 */
bool Dir::exists(const char* path)
{
	bool retn = false;
	struct stat fstat;
	stat(path, &fstat);
	if( S_ISDIR(fstat.st_mode) )
		retn = true;
	return retn;
}

/**
 * \brief path가 존재하는지 확인
 *
 * \return true/false
 */
bool Dir::exists()
{
	return exists(d->path.c_str());
}

/**
 * \brief path내의 목록을 얻어옴
 *
 * \param path 
 * \param f Dir::Filter
 * \param nameFilter 이름 filter
 *
 * \return 목록list
 */
String::StringList Dir::entryList(const char*path, int f/*=NoFilter*/, 
	std::string nameFilter/*=""*/)
{
	return d->readDir(path, f, nameFilter);
}

/**
 * \brief path내의 목록을 얻어옴
 *
 * \param f Dir::Filter
 * \param nameFilter 이름 filter
 *
 * \return 목록list
 */
String::StringList Dir::entryList(int f/*=NoFilter*/, 
	std::string nameFilter/*=""*/)
{
	return entryList(d->path.c_str(), f, nameFilter);
}

/**
 * \brief file의 크기를 얻어옴
 *
 * \param fileName
 *
 * \return file의 크기
 */
off_t Dir::size (const char *fileName)
{
    int fileType = 0;
    off_t totalFileSize = 0;

    fileType = d->getFileType (fileName);
    if (Dir::RegularFile == fileType)
        totalFileSize = d->getFileSize (fileName);
    else if (Dir::DirectoryFile == fileType)
        totalFileSize = d->getDirFileSize (fileName);

    return totalFileSize;
}

} //namespace PD
