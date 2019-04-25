#pragma once
#include "SpliteObject.h"
class Title : public SpliteObject
{
private:

public:
	Title(float px, float py);
	~Title();

	void init();
	void update();
};

