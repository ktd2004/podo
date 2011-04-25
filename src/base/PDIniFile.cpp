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
#include "PDIniFile.h"
#include "PDFile.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#define snprintf _snprintf
#endif
#include "PDIniFile_p.hpp"

namespace PD {

/**
 * \brief 생성자
 */
IniFile::IniFile()
{
	d = new IniFilePrivate;
}

/**
 * \brief 생성자
 *
 * \param fn 파일명
 */
IniFile::IniFile(const std::string& fn)
{
	d = new IniFilePrivate(fn);
    read(fn);
}

/**
 * \brief 소멸자
 */
IniFile::~IniFile()
{
	close();
	delete d;
}

/**
 * \brief 파일이 열려있는지 확인
 *
 * \return true/false
 */
bool IniFile::isOpen() { return d->isOpen; }

/**
 * \brief 파일을 닫음
 */
void IniFile::close()
{
	// delete all of map
    std::map<std::string, Group*>::iterator it = d->groups.begin();
	while(it != d->groups.end())
	{
		Group* grp = (*it).second;
		if (grp != NULL)
		{
			//printf("IniFile::~IniFile() delete group : [%s]\n",
			//	(*it).first.c_str());
			delete grp;
		}
		it++;
	}

	d->groups.clear();

	d->currentGroup = NULL;
	d->isOpen = false;
}

/**
 * \brief 항목을 기록함
 *
 * \param group
 * \param key
 * \param value
 */
void IniFile::writeEntry(const std::string& group, const std::string& key, 
	const std::string& value)
{
	if(!d->groups[group])
	{
		//printf("IniFile::writeEntry no group:%s\n", group.c_str());
		Group* grp = new Group;
		d->groups[group] = grp;
		d->currentGroup = grp;
	}
	else
	{
		d->currentGroup = d->groups[group];
	}

	(*d->currentGroup)[key] = value;
	//printf("IniFile::writeEntry key:%s value:%s\n", 
	//	key.c_str(), value.c_str());
}

/**
 * \brief 숫자 항목을 기록함
 *
 * \param group
 * \param key
 * \param value
 */
void IniFile::writeEntryInt( const std::string& group, const std::string& key, 
	const int& value )
{
	std::string str;	
	char buf[128];	
	snprintf(buf, sizeof(buf), "%d", value);
	str = buf;

	writeEntry(group, key, str);
}


/**
 * \brief 항목을 읽어옴
 *
 * \param group
 * \param key
 * \param def 기본값
 *
 * \return value
 */
std::string IniFile::readEntry(const std::string& group, 
	const std::string& key, const std::string def/*=""*/)
{
	std::string value = def;

	std::map<std::string, Group*>::iterator it = d->groups.find(group);
	if (it != d->groups.end())
	{
		Group::iterator git = (*it).second->find(key);
		if (git != (*it).second->end())
		{
			value = (*git).second;
		}
	}
	//printf("key : %s value:%s\n", key.c_str(), value.c_str());
	return value;
}

/**
 * \brief 숫자 항목을 읽어옴
 *
 * \param group
 * \param key
 * \param def 기본값
 *
 * \return value
 */
int IniFile::readEntryInt(const std::string& group, const std::string& key,
	const int def/*=0*/)
{
	std::string value = readEntry(group, key);

	int retn = def;

	if(!value.empty()) retn = atoi(value.c_str());

	return retn;
}

/**
 * \brief 모든 키 항목을 읽어옴
 *
 * \param group
 *
 * \return 키 리스트
 */
String::StringList IniFile::readKeyList(const std::string& group)
{
	String::StringList list;
	std::map<std::string, Group*>::iterator it = d->groups.find(group);
	if (it != d->groups.end())
	{
		Group* grp = (*it).second;
		Group::iterator git = grp->begin();
		while(git != grp->end())
		{
			list.push_back( (*git).first );	
			git++;
		}
	}

	return list;
}

/**
 * \brief 모든 그룹 항목을 읽어옴
 *
 * \return 그룹 리스트
 */
String::StringList IniFile::readGroupList()
{
	String::StringList list;
	std::map<std::string, Group*>::iterator it = d->groups.begin();
	while(it != d->groups.end())
	{
		std::string grpName = (*it).first;
		list.push_back(grpName);
		it++;
	}



	return list;
}

/**
 * \brief 변경된 모든 항목을 파일에 쓰기
 *
 * \return 0:ok -1:error
 */
int IniFile::write()
{
	return write(d->filename);
}

/**
 * \brief 변경된 모든 항목을 파일에 쓰기
 *
 * \param fn 파일명
 *
 * \return 0:ok -1:error
 */
int IniFile::write(const std::string &fn)
{
	File file;

	unlink(fn.c_str());
	if(file.open(fn.c_str(), PD::File::WriteOnly | PD::File::Create) == -1)
	{
		//printf("IniFile::write '%s' file open failed.\n", fn.c_str());
		return -1;
	}	

	std::map<std::string, Group*>::iterator g_it = d->groups.begin();

	size_t writeContentsSize = 100 * 1024; // 100KB
	unsigned char* writeContents = new unsigned char[writeContentsSize];
	size_t writeContentsPos = 0;

	enum { BUFSIZE = 1024 };
	char buf[BUFSIZE];
	//int retn = -1;
	while(g_it != d->groups.end())
	{
		const std::string& section = (*g_it).first;
		memset(buf, 0, sizeof(buf));
		snprintf(buf, sizeof(buf), "[%s]\n", section.c_str());

		//printf("IniFile::write writeContentsPos:%d buf:%s(%d)...1\n",
		//	writeContentsPos, buf, strlen(buf));

		if (writeContentsPos + strlen(buf) > writeContentsSize)
		{
			file.write(writeContents, writeContentsPos);
			writeContentsPos = 0;
		}
		memcpy(&writeContents[writeContentsPos], buf, strlen(buf));
		writeContentsPos += strlen(buf);
		
		Group grp = *(*g_it).second;

    	std::map<std::string, std::string>::iterator it = grp.begin();

		while(it != grp.end())
		{
			memset(buf, 0, sizeof(buf));
			//printf("key = [%s]   value = [%s] \n", (*it).first.c_str(),
			//	(*it).second.c_str());
			//fprintf(fp, "%s = %s\n", (*it).first.c_str(), 
			//	(*it).second.c_str());
			snprintf(buf, sizeof(buf), "%s = %s\n", (*it).first.c_str(),
				(*it).second.c_str());
			//printf("IniFile::write writeContentsPos:%d buf:%s(%d)...2\n",
			//	writeContentsPos, buf, strlen(buf));
			if (writeContentsPos + strlen(buf) > writeContentsSize)
			{
				file.write(writeContents, writeContentsPos);
				writeContentsPos = 0;
			}
			memcpy(&writeContents[writeContentsPos], buf, strlen(buf));
			writeContentsPos += strlen(buf);
			it++;
		}
		g_it++;
	}

	if (writeContentsPos)
	{
		if (file.write(writeContents, writeContentsPos) != 
			(int)writeContentsPos)
		{
			delete [] writeContents;
			return -1;
		}
	}

	delete [] writeContents;

	return 0;
}

/**
 * \brief 파일에서 ini파일을 읽어오기
 *
 * \param fn 파일명
 *
 * \return 0:ok -1:error
 */
int IniFile::read(const std::string& fn)
{
	if (isOpen()) close();

	File f(fn.c_str());
	if(f.open(PD::File::ReadOnly)<0)
	{
		//printf("IniFile::read '%s' file open failed.\n", fn.c_str());
		return -1;
	}
	std::string str;
	d->lineNo = 1;
	while(1)
	{
		if (!f.readLine(str)) break;
		if(d->parse(str) == -1) return -1;
		d->lineNo++;
	}

	d->isOpen = true;

	return 0;
}

} // namespace PD {
