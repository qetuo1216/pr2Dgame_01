#include "stdafx.h"
#include "gameObjectPool.h"
#include <iostream>
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

void gameObjectPool::checkCollision()//�浹 �˻� ������Ʈ�� ������ �Ѵ�.
{
	//1//1�� ���̾� �浹�˻��ϱ�
	for (int j = 0; j < obj[1].size(); j++)
	{
		for (int i = 0; i < j; i++)
		{
			//printf("%s", obj[1][i]->GetName);;
			//if (i < j)//�ߺ��� ������ ����
			//std::cout << "[" << obj[1][i]->GetName() << ", " << obj[1][j]->GetName() << "]";
			//�浹ü ����
			GameObject * objI = obj[1][i];
			GameObject * objJ = obj[1][j];

			//objI�� objJ���� �浹ü ��� ��������
			std::vector<AABB *> colI = objI->getCollider();
			std::vector<AABB *> colJ = objJ->getCollider();

			//�浹ü (AABB)���� �浹�˻�
			for (int ii = 0; ii < colI.size(); ii++)
			{
				for (int jj = 0; jj < colJ.size(); jj++)
				{
					AABB * aabbI = colI[ii];//objI���� ������ ii��° AABB//��µ� �簢��
					AABB * aabbJ = colJ[jj];//objI���� ������ ii��° AABB

					//aabbI�� aabbJ�� �簢�� ������ �浹�ߴ��� �˻�
					//cout << objI->GetName() << ", " << objJ->GetName() << endl;
					
					//�簢���� ��ǥ�� �����ͼ� �� ������ �����´�.(�������,�����ϴ�)
					float x0, y0, x1, y1;//aabbI�� ������ ��ǥ
					float a0, b0, a1, b1;//aabbJ�� ������ ��ǥ

					aabbI->getBB(x0, y0, x1, y1);
					aabbJ->getBB(a0, b0, a1, b1);

					if (x1 >= a0 && x0 <= a1 && y1 >= b0 && b1 >= y0)
					{
						/*cout << "�浹 ����----------------------" << endl;
						cout << "ù��° ��ü :" << objI->GetName() << endl;
						cout << "ù��° ��ü aabb�� ID:" << aabbI->getId() << endl;

						cout << "�ι�° ��ü :" << objJ->GetName() << endl;
						cout << "ù��° ��ü aabb�� ID:" << aabbJ->getId() << endl;*/
						//�浹 ����(�̺�Ʈ) ����
						//1//objI���� �ڽ��� �浹ü aabbI�� ���ӿ�����Ʈ ObjJ�� �浹�ϰ�, objJ�� aabbJ�� �浹�� �߻�
						objI->onTriggerEnter(aabbI, objJ, aabbJ);

						//2//objJ���� �ڽ��� �浹ü aabbJ�� ���ӿ�����Ʈ ObjI�� �浹�ϰ�, objI�� aabbI�� �浹�� �߻�
						objJ->onTriggerEnter(aabbJ, objI, aabbI);
					}
				}
			}
		}

		
	}
		//std::cout <<endl<< "--------------------" << endl;
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
