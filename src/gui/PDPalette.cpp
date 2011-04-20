#include "PDPalette.h"

namespace PD {

Palette::Palette()
{
	for (int i=0; i<Palette::MaxState; i++)
	{
		m_palette[Palette::Background][i] = lightgray;
		m_palette[Palette::Highlight][i] = white;
		m_palette[Palette::Text][i] = black;
		m_palette[Palette::HighlightText][i] = black;
		m_palette[Palette::FocusColor][i] = Color(173,206,240);
		m_palette[Palette::LightColor][i] = white;
		m_palette[Palette::DarkColor][i] = Color(64, 64, 64);
	}

}

Palette::Palette(Palette& c)
{
	for (int i=0; i<Palette::MaxState; i++)
	{
		m_palette[Palette::Background][i] = 
			c.color(Palette::Background, (Palette::State)i);
		m_palette[Palette::Highlight][i] = 
			c.color(Palette::Highlight, (Palette::State)i);
		m_palette[Palette::Text][i] = 
			c.color(Palette::Text, (Palette::State)i);
		m_palette[Palette::HighlightText][i] = 
			c.color(Palette::HighlightText, (Palette::State)i);
		m_palette[Palette::FocusColor][i] = 
			c.color(Palette::FocusColor, (Palette::State)i);
		m_palette[Palette::LightColor][i] = 
			c.color(Palette::LightColor, (Palette::State)i);
		m_palette[Palette::DarkColor][i] = 
			c.color(Palette::DarkColor, (Palette::State)i);
	}

}

Palette::~Palette()
{
}

void Palette::setColor(ColorRole role, Color c, State s/*=Enable*/)
{
	m_palette[role][s] = c;
}

Color Palette::color(ColorRole role, State s/*=Enable*/)
{
	return m_palette[role][s];
}

Palette& Palette::operator=(Palette& c)
{
	for (int i=0; i<MaxState; i++)
	{
		m_palette[Background][i] = c.color(Background, (State)i);
		m_palette[Highlight][i] = c.color(Highlight, (State)i);
		m_palette[Text][i] = c.color(Text, (State)i);
		m_palette[HighlightText][i] = c.color(HighlightText, (State)i);
		m_palette[FocusColor][i] = c.color(FocusColor, (State)i);
		m_palette[LightColor][i] = c.color(LightColor, (State)i);
		m_palette[DarkColor][i] = c.color(DarkColor, (State)i);
	}

	return *this;
}

int Palette::operator==(Palette& c)
{
	for (int i=0; i<MaxState; i++)
	{
		if (m_palette[Background][i] != c.color(Background, (State)i) ) return 0;
		if (m_palette[Highlight][i] != c.color(Highlight, (State)i) ) return 0;
		if (m_palette[Text][i] != c.color(Text, (State)i) ) return 0;
		if (m_palette[HighlightText][i] != c.color(HighlightText, (State)i) ) return 0;
		if (m_palette[FocusColor][i] != c.color(FocusColor, (State)i) ) return 0;
		if (m_palette[LightColor][i] != c.color(LightColor, (State)i) ) return 0;
		if (m_palette[DarkColor][i] != c.color(DarkColor, (State)i) ) return 0;
	}
	return 1;
}

int Palette::operator!=(Palette& c)
{
	return !(*this == c);
}


}

