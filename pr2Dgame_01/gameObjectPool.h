#pragma once
#include <vector>
#include "GameObject.h"
//�̱������ϱ�
//���ӿ�����Ʈ�� �迭 ���·� �ۿ��� ��ü�� ���� �� ����� �Ѵ�.
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
	vector<GameObject *> obj;

public:
	//��ü �������� ����ƽ(����) �޼ҵ�
	static gameObjectPool * instance();//pool�� null�̸� ��ü�� �����, ������ ��� ����Ѵ�.

	//���� ������Ʈ �߰� �޼ҵ�
	void addGameObject(GameObject * o);//obj�迭�� ��

	//�߰��� ��ü ������Ʈ
	void update();

	//�߰��� ��ü draw
	void draw();
};

