#pragma once
#include "GameObject.h"
#include "bmp.h"
class HUDBar : public GameObject
{
private:
	Sprite bar;//바 이미지
	Sprite barBk;//바 태두리 이미지

	//bar의 출력 길이
	int value;
public:
	HUDBar(float px,float py);
	~HUDBar();

	void init();
	void draw();

	//bar 길이값 설정
	void setValue(float v);//길이 설정 0~1사이
};

