#include "stdafx.h"
#include "SpliteObject.h"
SpliteObject::SpliteObject(std::string name, int tag, bool state, float px, float py)
	:GameObject(name,tag,state,px,py)//���ӿ�����Ʈ ������ ��ӹ��� ��
{
	//splite����ü �ʱ�ȭ
	ZeroMemory(&splite,0);//splite.height = 0 ��� �޸𸮸� ��� 0���� �ʱ�ȭ
}

#define SafeDeleteArray(X) if(X != NULL) {	delete[] X;	X = NULL;}
SpliteObject::~SpliteObject()
{
	//�ε��� �̹��� �޸𸮸� ������
	/*if (splite.argb != NULL)
	{
		delete[] splite.argb;
		splite.argb = NULL;
	}*/
	SafeDeleteArray(splite.argb);
}

void SpliteObject::draw()
{
	drawBmp(px, py, &splite);
}
