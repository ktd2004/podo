#ifndef _PDLABEL_P_H_
#define _PDLABEL_P_H_

namespace PD {

class LabelPrivate
{
public:
	std::string text;
	int	alignment;
	bool border;
	unsigned int margin;

	LabelPrivate() : alignment(AlignLeft | AlignTop)
	{
		border = false;
		margin = 2;
	}

	~LabelPrivate()
	{
	}
};
} //namespace PD {
#endif
