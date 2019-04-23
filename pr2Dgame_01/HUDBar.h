#pragma once
#include "GameObject.h"
#include "bmp.h"
class HUDBar : public GameObject
{
private:
	Sprite bar;//바 이미지
	Sprite barBk;//바 태두리 이미지
public:
	HUDBar(float px,float py);
	~HUDBar();

	void init();
	void draw();
};

