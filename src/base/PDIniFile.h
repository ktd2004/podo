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
#ifndef _PDINITFILE_H_
#define _PDINITFILE_H_

#include "PDString.h"
#include <string>
#include <map>

namespace PD {

class IniFilePrivate;

/**
 * \brief ini file
 * \ingroup base
 */
class IniFile
{
public:
    typedef std::map<std::string, std::string> Group;

private:
	IniFilePrivate* d;

public:    
	IniFile();
    IniFile(const std::string& fn);
    ~IniFile();

	bool isOpen();
    
    void writeEntry( const std::string& group, const std::string& key, 
		const std::string& value );

    void writeEntryInt( const std::string& group, const std::string& key, 
		const int& value );
    
    std::string readEntry(const std::string& group, const std::string& key,
		const std::string def="");
	int readEntryInt(const std::string& group, const std::string& key,
		const int def=0);

	String::StringList readKeyList(const std::string& group);
	String::StringList readGroupList();
    
    int write();
    int write(const std::string& fn);
    int read(const std::string& fn);

	void close();
};

} //namespace PD {

#endif
