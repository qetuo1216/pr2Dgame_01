#include "stdafx.h"
#include "gameObjectPool.h"

//static ������ �����
gameObjectPool * gameObjectPool::pool=NULL;

//������&�Ҹ���
gameObjectPool::gameObjectPool()
{
}


gameObjectPool::~gameObjectPool()
{
}

//�ν��Ͻ� ��ȯ �޼ҵ�(��ü�� �ִ��� �˻�)
gameObjectPool * gameObjectPool::instance()
{
	if (gameObjectPool::pool == NULL)
	{
		gameObjectPool::pool = new gameObjectPool();//���� Ŭ���� ���� private�� ���� ����
	}

	return gameObjectPool::pool;

}

void gameObjectPool::addGameObject(GameObject * o)
{
	obj.push_back(o);	//��ü �߰�//ũ�Ⱑ �þ�鼭 ������ �ȴ�.
	o->init();			//��ü �ʱ�ȭ
}

void gameObjectPool::update()
{
	for (int i = 0; i < obj.size(); i++)
	{
		obj[i]->update();
	}
}

void gameObjectPool::draw()
{
	for (int i = 0; i < obj.size(); i++)
	{
		obj[i]->draw();
	}
}
