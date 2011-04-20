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
