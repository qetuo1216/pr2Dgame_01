#include "stdafx.h"
#include "SpliteObject.h"
SpliteObject::SpliteObject(std::string name, int tag, int state, float px, float py)
	:GameObject(name,tag,state,px,py)//게임오브젝트 내용을 상속받은 것
{
}


SpliteObject::~SpliteObject()
{
	//로드한 이미지 메모리를 해제함
}

void SpliteObject::draw()
{
	drawBmp(px, py, &splite);
}
