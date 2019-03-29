#include "stdafx.h"
#include "Animation.h"


Animation::Animation(std::string name, int tag, bool state, float px, float py)
	:GameObject(name, tag, state, px, py)
{
}


Animation::~Animation()
{
}

void Animation::draw()
{
	drawBmp(px, py, &frames[0]);
}
