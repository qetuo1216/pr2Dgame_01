#include "stdafx.h"
#include "SpliteObject.h"
SpliteObject::SpliteObject(std::string name, int tag, bool state, float px, float py)
	:GameObject(name,tag,state,px,py)//���ӿ�����Ʈ ������ ��ӹ��� ��
{
	//splite����ü �ʱ�ȭ
	ZeroMemory(&sprite,0);//splite.height = 0 ��� �޸𸮸� ��� 0���� �ʱ�ȭ
}

SpliteObject::~SpliteObject()
{
	//�ε��� �̹��� �޸𸮸� ������
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
