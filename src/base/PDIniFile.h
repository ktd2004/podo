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
