#pragma once
#include <vector>
#include "GameObject.h"
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

	//���� ǥ�õ� ���ӿ�����Ʈ �����ϱ�
	void removeDeadObjs();
	
	//�߰��� ��ü debugDraw
	void debugDraw();

};

