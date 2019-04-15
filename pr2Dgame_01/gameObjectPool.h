#pragma once
#include <vector>
#include "GameObject.h"
#include "ColPair.h"
//�̱������ϱ�
//���ӿ�����Ʈ�� �迭 ���·� �ۿ��� ��ü�� ���� �� ����� �Ѵ�.
#define MAX_LAYER 5
using namespace std;
class gameObjectPool
{
private:
	//�����ڿ� �Ҹ��ڸ� private�� �ֱ�
	gameObjectPool();//�⺻ ������
	virtual ~gameObjectPool();

	//�̱����� ������ ���� ������(��ü 1��)
	static gameObjectPool * pool;//
	
	//���� ������Ʈ�� �����ϴ� �迭(stl vector) �ڵ� �Ҵ�
	vector<GameObject *> obj[MAX_LAYER];//���̾� ���� //0�� 0�� ���̾�,1�� 1�� ���̾�  

	//�浹�� ���� �迭(stl Vector)
	vector<ColPair *> colPair;

public:
	//��ü �������� ����ƽ(����) �޼ҵ�
	static gameObjectPool * instance();//pool�� null�̸� ��ü�� �����, ������ ��� ����Ѵ�.

	//���� ������Ʈ �߰� �� ���� �޼ҵ�
	void addGameObject(GameObject * o, int order);//obj�迭�� ��
	void delGameObject(GameObject * o);
	//�߰��� ��ü ������Ʈ
	void update();

	//�߰��� ��ü draw
	void draw();

	//Ǯ�� �߰��� ��ü �浹�˻��ϱ�
	void checkCollision();
	void checkSameLayerCollision(int l);//1�� ���̾� �浹 �˻�

	//���� ǥ�õ� ���ӿ�����Ʈ �����ϱ�
	void removeDeadObjs();
	
	//�浹���� ����Ǿ����� �Ǵ��ϱ�
	bool checkInColPairs(GameObject *objI, GameObject *objJ, AABB *aabbI, AABB *aabbJ);
	
	//�����Ǵ� ��ü������� �浹�� �����ϱ�
	void removeDeadColPair(GameObject *o);

	//�浹�� ���� ����(�浹 ������ ���� ����)
	void resetColPairs();
	void removeUnColliedPairs();//�浹 ���� ó�� �Լ�

	//�߰��� ��ü debugDraw
	void debugDraw();

};

