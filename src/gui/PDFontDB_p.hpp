#ifndef _PDFONTDB_P_H_
#define _PDFONTDB_P_H_

namespace PD {

class FontDBPrivate
{
public:
	FontDB::FontMap map;
	FontDB::CacheFontMapList cacheFontMapList;
	std::string cacheFontMapFile;

public:
	FontDBPrivate()
	{
	}

	~FontDBPrivate()
	{
	}

	Font* open(const char* name, size_t size)
	{
		Font* f = new Font(name, size);
		if (f == 0)
		{
			printf("FontDBPrivate::open failed to open '%s' size:%d\n", 
					name, size);
			return 0;
		}

		std::string key = String::format("%s_%d", name, size);
		map[key] = f;

		//printf("FontDBPrivate::open name:%s size:%d %X\n", name, size, f);
		return f;
	}


};

} //namespace PD {
#endif
