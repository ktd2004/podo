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
#include "PDFile.h"
#include "PDFile_p.hpp"
#include <stdlib.h>

#ifndef WIN32
#include <unistd.h>
#include <sys/time.h>
#else
#include <io.h>
#endif

#include <fcntl.h>

#ifdef __APPLE__
#define lseek64 lseek
#endif


namespace PD {

/**
 * \brief 생성자
 *
 * \param filename 파일명
 */
File::File(const char* filename)
{
	d = new FilePrivate(filename);
}

/**
 * \brief 소멸자
 */
File::~File()
{
	close();
	delete d;
}

/**
 * \brief 파일명을 얻어옴
 *
 * \return 파일명
 */
std::string File::name() { return d->filename; }

/**
 * \brief 파일이 이미 열려있는지 확인
 *
 * \return true/false
 */
bool File::isOpen()
{
	return (d->fd != -1);
}

/**
 * \brief 파일을 오픈함
 *
 * \param mode File::OpenMode
 *
 * \return 0:ok -1:error
 */
int File::open(int mode)
{
	return open(d->filename.c_str(), mode);
}

/**
 * \brief 파일을 오픈함
 *
 * \param filename 파일명
 * \param mode File::OpenMode
 *
 * \return 0:ok -1:error
 */
int File::open(const char* filename, int mode)
{
	if (d->fd != -1) return d->fd;

	int m = 0;
	if (mode & WriteOnly) m = O_WRONLY;
	if (mode & ReadOnly) m = O_RDONLY;
	if (mode & ReadWrite) m = O_RDWR;

	if (mode & Append) m |= O_APPEND;
	if (mode & Truncate) m |= O_TRUNC;
	if (mode & Create) m |= O_CREAT;

#ifdef WIN32
	if (mode & Binary) m |= O_BINARY;
#endif

#ifndef WIN32
	d->fd = ::open(filename, m, 0644);
#else
	d->fd = ::_open(filename, m, 0644);
#endif

	d->filename = filename;
	
	return d->fd;
}

/**
 * \brief 파일을 닫음
 */
void File::close()
{
	if (d->fd == -1) return;

#ifndef WIN32
	::close(d->fd);
#else
	::_close(d->fd);
#endif
	d->fd = -1;
}

/**
 * \brief 파일을 라인단위로 읽음
 *
 * \param line 라인단위로 읽어서 담을 공간
 * \return true/false
 */
bool File::readLine(std::string& line)
{
	line.clear();

	char buf = 0;
	int retn = -1;
	while(1)
	{
		retn = read((unsigned char*)&buf, 1);
		if(retn <= 0) 
		{
			if (!line.empty()) break;
			return false;
		}
		line += buf;
		if(buf == '\n') break;
	}

	return true;
}

/**
 * \brief 파일내의 내용을 읽기
 *
 * \param buf 내용을 담을 버퍼
 * \param bufSize 내용을 담을 버퍼의 크기
 * \return -1:error, >0:읽은바이트 크기
 */
int File::read(unsigned char* buf, size_t bufSize)
{
#ifndef WIN32
	return ::read(d->fd, buf, bufSize);
#else
	return ::_read(d->fd, buf, (unsigned int)bufSize);
#endif
}

/**
 * \brief 파일내의 내용을 쓰기
 *
 * \param buf 내용을 담은 버퍼
 * \param bufSize 내용을 담은 버퍼의 크기
 * \return -1:error, >0:쓴 바이트 크기
 */
int File::write(unsigned char* buf, size_t bufSize)
{
#ifndef WIN32
	return ::write(d->fd, buf, bufSize);
#else
	return ::_write(d->fd, buf, (unsigned int)bufSize);
#endif
}

/**
 * \brief 파일내의 위치를 이동
 *
 * \param pos 위치
 * \return -1:error, >0:이동한 위치
 */
int File::seek(int pos)
{
#ifndef WIN32
	return lseek(d->fd, pos, SEEK_SET);
#else
	return _lseek(d->fd, pos, SEEK_SET);
#endif
}

/**
 * \brief 파일내의 위치를 이동
 *
 * \param pos 위치
 * \return -1:error, >0:이동한 위치
 */
uint64_t File::seek64(uint64_t pos)
{
#ifndef WIN32
	return lseek64(d->fd, pos, SEEK_SET);
#else
	return _lseeki64(d->fd, pos, SEEK_SET);
#endif
}

/**
 * \brief 파일이 존재하는지 확인
 *
 * \param filename 파일명
 * 
 * \return true/false
 */
bool File::exists(const char* filename)
{
#ifndef WIN32
	return !access(filename,  F_OK);
#else
	return !_access(filename,  0);
#endif
}

/**
 * \brief 파일이 존재하는지 확인
 *
 * \return true/false
 */
bool File::exists()
{
	return exists(d->filename.c_str());
}

/**
 * \brief 파일의 크기를 구함
 *
 * \param filename 파일명

 * \return -1:error, >0: 파일의 크기
 */
int File::size(const char* filename)
{
#ifndef WIN32
	int fd = ::open(filename, O_RDONLY);
#else
	int fd = ::_open(filename, O_RDONLY);
#endif
	if(fd<0) return 0;

	struct stat s;
	if(fstat(fd, &s) < 0) 
	{
#ifndef WIN32
		::close(fd);
#else
		::_close(fd);
#endif
		return 0;
	}

#ifndef WIN32
	::close(fd);
#else
	::_close(fd);
#endif
	return s.st_size;
}

/**
 * \brief 파일을 삭제
 *
 * \param filename 파일명
 *
 * \return true/false
 */
bool File::unlink(const char* filename)
{
#ifndef WIN32
	return (unlink(filename) != -1);
#else
	return (_unlink(filename) != -1);
#endif
}

/**
 * \brief 시스템 버퍼의 내용을 flush
 *
 * \param filename 파일명
 *
 * \return true/false
 */
bool File::fsync(const char* filename)
{
#ifndef WIN32
	int fd = ::open(filename, O_WRONLY);
	if ( fd==-1 ) return false;
	int ret = ::fsync( fd );
	if ( ret==-1 )
	{
		//printf("File::fsync failed\n");
		::close(fd);
		return false;
	}
	::close(fd);
	return true;
#else
	return false;
#endif
}

/**
 * \brief 파일의 마지막 접근/수정 시간을 수정함
 *
 * \param filename 파일명
 * \param dateTime 시간
 *
 * \return 0:ok, -1:error
 */
int File::utime(const char* filename, const DateTime& datetime)
{
#ifndef WIN32
	struct utimbuf ubuf;
	ubuf.actime=(time_t)datetime.sec();
	ubuf.modtime=(time_t)datetime.sec();

	return ::utime(filename, &ubuf); 
#else
	return -1;
#endif
}

} //namespace PD {
