#include "stdafx.h"
#include "SpliteObject.h"
SpliteObject::SpliteObject(std::string name, int tag, bool state, float px, float py)
	:GameObject(name,tag,state,px,py)//���ӿ�����Ʈ ������ ��ӹ��� ��
{
}


SpliteObject::~SpliteObject()
{
	//�ε��� �̹��� �޸𸮸� ������
	delete splite.argb;
}

void SpliteObject::draw()
{
	drawBmp(px, py, &splite);
}
