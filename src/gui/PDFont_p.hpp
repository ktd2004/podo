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
#ifndef _PDFONT_P_H_
#define _PDFONT_P_H_

namespace PD {

class FontPrivate
{
public:
	TTF_Font* font;
	std::string name;
	int size;
	PD::Mutex mutex;

public:
	FontPrivate()
	{
		font = 0;
		size = theApp->fontSize();
	}

	FontPrivate(const char* fn, int _size)
	{
		font = NULL;
		size = _size;
	}

	~FontPrivate()
	{
		close();
	}

	bool isOpen()
	{
		return (font != NULL);
	}

	int open()
	{
		close();

		std::string path = PD::theApp->fontDir() + "/" + name;
		font = TTF_OpenFont(path.c_str(), size);
		if (font == NULL)
		{
			printf("FontPrivate::open failed to open '%s' font\n", 
				path.c_str());
			return -1;
		}
		//printf("Font::open fn:%s size:%d\n", path.c_str(), size);

		return 0;
	}

	void close()
	{
		if (font) 
		{	
			TTF_CloseFont(font);
			font = 0;
		}
	}
};

} //namespace PD {
#endif
