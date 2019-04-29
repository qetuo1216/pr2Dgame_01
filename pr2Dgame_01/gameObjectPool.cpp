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
				//delete obj[l][i];//�Ǵ� delete o; //�Ҹ��ڰ� ����
				//2//stl vector���� ������� ����
				//obj[l].erase(obj[l].begin() + i);

				//����)�ٷ� ������ ���� ���߿� ���쵵�� �ӽ÷� ���ӿ�����Ʈ�� �����Ǿ������ ǥ���صд�.
				obj[l][i]->setAlive(false);
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

void gameObjectPool::resetColPairs()
{
	for (int k = 0; k < colPair.size(); k++)
	{
		colPair[k]->setCollided(false);//�浹�� �����ٰ� ���� ����
	}
}
void gameObjectPool::removeUnColliedPairs()
{
	//�����Ǵ� ���ӿ�����Ʈ�� �浹�ֿ� ������ ������
	for (int k = 0; k < colPair.size(); k++)
	{
		
		//o�� colPair�� i��°�� �ִ� objI�� J�� ������ ���� ����
		if (colPair[k]->getCollided()==false)
		{
			GameObject * objI = colPair[k]->getObjI();
			GameObject * objJ = colPair[k]->getObjJ();
			AABB * aabbI = colPair[k]->getAABBI();
			AABB * aabbJ = colPair[k]->getAABBJ();

			//�浹���� ���ŵǸ鼭 �߻��ϴ� �浹 ���� �̺�Ʈ�� �߻�
			objI->onTriggerExit(aabbI, objJ, aabbJ);
			objJ->onTriggerExit(aabbJ, objI, aabbI);

			//�浹�� delete�ϱ�
			delete colPair[k];

			//���� �ڸ� ����
			colPair.erase(colPair.begin() + k);

			//������ �������� k�� ����
			k--;
		}
	}
}
void gameObjectPool::clear()
{
	//Ǯ�� ��� ���ӿ�����Ʈ ����
	for (int l = 0; l < MAX_LAYER; l++)
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			delete obj[l][i];
		}
		obj[l].clear();
	}
}

GameObject * gameObjectPool::find(string name)
{
	for (int l = 0; l < MAX_LAYER; l++)
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			if (obj[l][i]->GetName()== name)
			{
				return obj[l][i];
			}
		}
		
	}
	return NULL;//���� ã�� �����Ͱ� ����.
}

void gameObjectPool::checkCollision()//�浹 �˻� ������Ʈ�� ������ �Ѵ�.
{
	//��� �浹���� ���¸� �浹�� �����ٰ� ���¸� ǥ����.
	resetColPairs();

	//���� ���̾ �ִ� ���� ������Ʈ �浹�˻�
	for (int l = 0; l < MAX_LAYER; l++)
	{
		checkSameLayerCollision(l);
	}
	
	//�ٸ� ���̾ �ִ� ���� ������Ʈ �浹�˻�

	for (int lJ = 0; lJ < MAX_LAYER; lJ++)
	{
		for (int lI = 0; lI < MAX_LAYER; lI++)
		{
			if (lI < lJ) 
			{ 
				checkDifLayerCollision(lI, lJ); 
			}
		}
	}

	removeUnColliedPairs();//�浹�� ����� �� ����
		//std::cout <<endl<< "--------------------" << endl; 
}

void gameObjectPool::checkDifLayerCollision(int lI, int lJ)
{
	//////////lI, lJ-�����̾� �浹�˻��ϱ�////////
	for (int j = 0; j < obj[lJ].size(); j++)
	{
		for (int i = 0; i < obj[lI].size(); i++)
		{
			GameObject * objI = obj[lI][i];
			GameObject * objJ = obj[lJ][j];

			//objI �� objJ�� ��������� �ƴѰ�츸..�浹 �˻縦 ������
			if (objI->getAlive() == true && objJ->getAlive() == true)
			{
				////////objI, objJ���� �浹ü ��� ��������/////
				std::vector<AABB *> colI = objI->getCollider();
				std::vector<AABB *> colJ = objJ->getCollider();

				/////////////�浹ü(AABB)���� �浹�˻�//////////
				for (int ii = 0; ii < colI.size(); ii++)
				{
					for (int jj = 0; jj < colJ.size(); jj++)
					{
						AABB * aabbI = colI[ii];  //ObjI���� ������ ii��° AABB
						AABB * aabbJ = colJ[jj];  //ObjI���� ������ jj��° AABB

						//////aabbI �� aabbJ �� �浹�ߴ����� �˻���//////
						float x0, y0, x1, y1;    //aabbI�� ��������ǥ
						float a0, b0, a1, b1;    //aabbJ�� ��������ǥ

						aabbI->getBB(x0, y0, x1, y1);
						aabbJ->getBB(a0, b0, a1, b1);

						if (x1 >= a0 && x0 <= a1 && y1 >= b0 && b1 >= y0)
						{
							///////////////�浹���� ����Ǿ� �ִ����� �Ǵ���/////////
							bool checkInColPair = checkInColPairs(objI, objJ, aabbI, aabbJ);

							if (checkInColPair == false) //[A]ObjI (aabbI), ObjJ(aabbJ)�� �浹���� ����Ǿ� ���� ������..
							{
								//// -OnTriggerEnter �̺�Ʈ �߻���Ű��..�浹���� ������									
								//[1]ObjI����..�ڽ��� �浹ü aabbI�� ���ӿ�����Ʈ ObjJ�� �浹�ϰ�..ObjJ�� aabbJ�� �浹�� �߻���
								objI->onTriggerEnter(aabbI, objJ, aabbJ);

								//[2]ObjJ����..�ڽ��� �浹ü aabbJ�� ���ӿ�����Ʈ ObjI�� �浹�ϰ�..ObjI�� aabbI�� �浹�� �߻���
								objJ->onTriggerEnter(aabbJ, objI, aabbI);

								//[3]�浹 ���� �����ϱ�...
								colPair.push_back(new ColPair(objI, objJ, aabbI, aabbJ));
							}
							else { //[B]ObjI (aabbI), ObjJ(aabbJ)�� �浹���� ����Ǿ� ������...

								  //// -OnTriggerStay �̺�Ʈ �߻� (�浹�� �ݺ��ǰ� ����)
								objI->onTriggerStay(aabbI, objJ, aabbJ);

								//[2]ObjJ����..�ڽ��� �浹ü aabbJ�� ���ӿ�����Ʈ ObjI�� �浹�ϰ�..ObjI�� aabbI�� �浹�� �߻���
								objJ->onTriggerStay(aabbJ, objI, aabbI);
							}

						}

					}
				}

			}
		}
	}
}

void gameObjectPool::checkSameLayerCollision(int l)
{
	//1//1�� ���̾� �浹�˻��ϱ�
	for (int j = 0; j < obj[l].size(); j++)
	{
		for (int i = 0; i < j; i++)
		{
			//printf("%s", obj[1][i]->GetName);;
			//if (i < j)//�ߺ��� ������ ����
			//std::cout << "[" << obj[1][i]->GetName() << ", " << obj[1][j]->GetName() << "]";
			//�浹ü ����
			GameObject * objI = obj[l][i];
			GameObject * objJ = obj[l][j];

			//objI�� objJ�� ���� ����� �ƴ� ��츸 �浹�˻��Ѵ�.
			if (objI->getAlive() == true && objJ->getAlive() == true)
			{
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
							bool checkColPair = checkInColPairs(objI, objJ, aabbI, aabbJ);

							if (checkColPair == false)
							{
								//A//objI(aabbI),objJ(aabbJ)�� �浹���� ����Ǿ� ���� ������
								//////onTrigerEnter�̺�Ʈ �߻�
								//�浹 ����(�̺�Ʈ) ����
									//1//objI���� �ڽ��� �浹ü aabbI�� ���ӿ�����Ʈ ObjJ�� �浹�ϰ�, objJ�� aabbJ�� �浹�� �߻�
								objI->onTriggerEnter(aabbI, objJ, aabbJ);

								//2//objJ���� �ڽ��� �浹ü aabbJ�� ���ӿ�����Ʈ ObjI�� �浹�ϰ�, objI�� aabbI�� �浹�� �߻�
								objJ->onTriggerEnter(aabbJ, objI, aabbI);

								//3//�浹 ���� �����ϱ�
								colPair.push_back(new ColPair(objI, objJ, aabbI, aabbJ));
							}
							else
							{
								//B//objI(aabbI),objJ(aabbJ)�� �浹���� ����Ǿ� ������
								//////onTrigerStay�̺�Ʈ �߻�(�ݺ� �浹)
									//objI->onTriggerStay()

									//1//objI���� �ڽ��� �浹ü aabbI�� ���ӿ�����Ʈ ObjJ�� �浹�ϰ�, objJ�� aabbJ�� �浹�� �߻�(���)
								objI->onTriggerStay(aabbI, objJ, aabbJ);

								//2//objJ���� �ڽ��� �浹ü aabbJ�� ���ӿ�����Ʈ ObjI�� �浹�ϰ�, objI�� aabbI�� �浹�� �߻�(���)
								objJ->onTriggerStay(aabbJ, objI, aabbI);
							}

							/*cout << "�浹 ����----------------------" << endl;
							cout << "ù��° ��ü :" << objI->GetName() << endl;
							cout << "ù��° ��ü aabb�� ID:" << aabbI->getId() << endl;

							cout << "�ι�° ��ü :" << objJ->GetName() << endl;
							cout << "ù��° ��ü aabb�� ID:" << aabbJ->getId() << endl;*/

						}
					}
				}
				/*//�浹 ���°� �浹 ������ �����Ǵ� �浹���� �浹�� �� ������ ǥ��
				for (int k = 0; k < colPair.size(); k++)
				{
					if (colPair[k]->getCollided() == false)
					{
						printf("\n�浹�� ����");

						//�浹�� ����
						delete colPair[k];

						//stlVector ����
						colPair.erase(colPair.begin() + k);
						k--;
					}
				}*/
			}
		}


	}
}

void gameObjectPool::removeDeadObjs()
{
	//��ü �ȿ��� �ٷ� delete�ϴ� ���� �ڵ尡 �������� ���Ѵ�.
	for (int l = 0; l < MAX_LAYER; l++)
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
				GameObject *o = obj[l][i];
			
			if (o->getAlive()==false)//��ġ�ϴ� ���̵� ã��
			{
				removeDeadColPair(o);

				//1//���ӿ�����Ʈ delete
				delete o;

				//2//stl vector���� ������� ����
				obj[l].erase(obj[l].begin() + i);

				i--;//������ ��� 1ĭ�� ��� ���� ��ܿ;��Ѵ�.
				
			}
		}
	}
}

void gameObjectPool::removeDeadColPair(GameObject * o)
{
	//�����Ǵ� ���ӿ�����Ʈ�� �浹�ֿ� ������ ������
	for (int k = 0; k < colPair.size(); k++)
	{
		GameObject * objI = colPair[k]->getObjI();
		GameObject * objJ = colPair[k]->getObjJ();
		//o�� colPair�� i��°�� �ִ� objI�� J�� ������ ���� ����
		if (o->getId() == objI->getId() || o->getId() == objJ->getId())
		{
			AABB * aabbI = colPair[k]->getAABBI();
			AABB * aabbJ = colPair[k]->getAABBJ();

			//�浹���� ���ŵǸ鼭 �߻��ϴ� �浹 ���� �̺�Ʈ�� �߻�
			objI->onTriggerExit(aabbI, objJ, aabbJ);
			objJ->onTriggerExit(aabbJ, objI, aabbI);

			//�浹�� delete�ϱ�
			delete colPair[k];

			//���� �ڸ� ����
			colPair.erase(colPair.begin() + k);

			//������ �������� k�� ����
			k--;
		}
	}

}

bool gameObjectPool::checkInColPairs(GameObject * objI, GameObject * objJ, AABB * aabbI, AABB * aabbJ)
{
	
	//�浹���� ����Ǿ��ִ��� �Ǵ�.
	for (int k = 0; k < colPair.size(); k++)
	{
		//calPair�ְ� objI(aabbI),objJ(aabbJ)�� ����Ǿ��ִ°�
		if (colPair[k]->equal(objI, objJ, aabbI, aabbJ) == true)
		{
			colPair[k]->setCollided(true);//���� �浹�� ������ ����
			
			return true;
		}
	}

	return false;
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
