#include "stdafx.h"
#include "SpliteObject.h"
SpliteObject::SpliteObject(std::string name, int tag, int state, float px, float py)
	:GameObject(name,tag,state,px,py)//���ӿ�����Ʈ ������ ��ӹ��� ��
{
}


SpliteObject::~SpliteObject()
{
	//�ε��� �̹��� �޸𸮸� ������
}

void SpliteObject::draw()
{
	drawBmp(px, py, &splite);
}
