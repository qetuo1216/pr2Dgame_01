#include "stdafx.h"
#include "SpliteObject.h"
SpliteObject::SpliteObject(std::string name, int tag, bool state, float px, float py)
	:GameObject(name,tag,state,px,py)//게임오브젝트 내용을 상속받은 것
{
	//splite구조체 초기화
	ZeroMemory(&sprite,0);//splite.height = 0 등등 메모리를 모두 0으로 초기화
}

SpliteObject::~SpliteObject()
{
	//로드한 이미지 메모리를 해제함
	/*if (splite.argb != NULL)
	{
		delete[] splite.argb;
		splite.argb = NULL;
	}*/
	SafeDeleteArray(sprite.argb);
	
}

void SpliteObject::draw()
{
	drawBmp(px, py, &sprite);
}
