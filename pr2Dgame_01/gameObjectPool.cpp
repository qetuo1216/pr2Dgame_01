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
		gameObjectPool::pool = new gameObjectPool();
	}

	return gameObjectPool::pool;

}
