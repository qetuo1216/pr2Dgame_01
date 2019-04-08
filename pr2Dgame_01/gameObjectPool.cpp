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

void gameObjectPool::addGameObject(GameObject * o, int order)//order�� ���̾� ��ȣ
{


		obj[order].push_back(o);	//��ü �߰�//ũ�Ⱑ �þ�鼭 ������ �ȴ�.
		o->init();			//��ü �ʱ�ȭ
	
}

void gameObjectPool::delGameObject(GameObject * o)
{
	//��ü �ȿ��� �ٷ� delete�ϴ� ���� �ڵ尡 �������� ���Ѵ�.
	int id = o->getId();
	for (int l = 0; l < MAX_LAYER; l++)
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			if (obj[l][i]->getId() == id)//��ġ�ϴ� ���̵� ã��
			{
				//1//��ü delete
				delete obj[l][i];//�Ǵ� delete o; //�Ҹ��ڰ� ����
				//2//stl vector���� ������� ����
				obj[l].erase(obj[l].begin() + i);
			}
		}
	}
}


void gameObjectPool::update()
{
	for (int l = 0; l < MAX_LAYER; l++)
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			obj[l][i]->update();
		}
	}
}

void gameObjectPool::draw()
{
	for (int l = 0; l < MAX_LAYER; l++)//l�� ���̾� ��ȣ
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			if (obj[l][i]->getState() == true)//���� �˻�
			{
				obj[l][i]->draw();
			}
		}
	}
	
}

void gameObjectPool::debugDraw()
{
	for (int l = 0; l < MAX_LAYER; l++)//l�� ���̾� ��ȣ
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			//if (obj[l][i]->getState() == true)//���� �˻�
			{
				obj[l][i]->debugDraw();
			}
		}
	}
}
