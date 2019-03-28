#pragma once
#include "SpliteObject.h"
class BackGround : public SpliteObject//SpliteObject를 상속
{
private:

public:
	//생성자&소멸자
	BackGround(float px, float py);
	~BackGround();

	//init 오버라이딩
	void init();
};

