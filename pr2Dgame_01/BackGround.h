#pragma once
#include "SpliteObject.h"
class BackGround : public SpliteObject//SpliteObject를 상속
{
private:
	//배경 스크롤 속도
	float speed;
public:
	//생성자&소멸자
	BackGround(float px, float py);
	~BackGround();

	//init,update 오버라이딩
	void init();
	void update();//이동속도 계산하여 이동시킴
};

