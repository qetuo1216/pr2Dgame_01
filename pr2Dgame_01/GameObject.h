#include <string>
#define SafeDeleteArray(X) if(X != NULL) {	delete[] X;	X = NULL;}
#include <vector>
#include "AABB.h"
#pragma once
class GameObject	//�÷��̾�,����� ���� �ֻ��� ����
{
protected:		  //��ӹ��� �� ���� private��� �����

	//���ӿ�����Ʈ ���̵�
	static int ID;//ī��Ʈ
	int id;//���ӿ�����Ʈ�� �Ҵ���� ���̵�

	//�⺻ ������ -�̸�(string) �±�(int),����
	std::string name;	//�̸�		//const char * name;	//string ���� 	usingname space std;
	int tag;			//�±�				
	bool state;			//����
	//transform - �̵�
	float px, py;		//��ġ�̵�

	//�浹ü �߰��ϱ�
	std::vector<AABB *> col;
	//�浹ü rgb ����
	unsigned char colR, colG, colB;

public:
	//������&�Ҹ���
	GameObject(std::string name, int tag, bool state,float px, float py);
	virtual ~GameObject();

	//�⺻Ȱ�� �Լ�
	virtual void init();
	virtual void update();
	virtual void draw();
	//�浹ü �׸����Լ� �߰�
	virtual void debugDraw();


	//getter&setter
	//�ʿ�ÿ� ����
	int getId();
	int getTag();
	bool getState();
	void setState(bool state);
	std::string GetName();
	std::vector<AABB *> getCollider();
	//��Ÿ
	void translate(float dx,float dy);//�̵�(translate) �Լ�

	void addGameObject(GameObject * o,int order);//��ü �߰� �޼ҵ�
	void delGameObject(GameObject * o);//��ü ���� �޼ҵ�
	
	//�浹ü �߰� �Լ�
	void addCollider(AABB *aabb);
	void setColColor(unsigned char r, unsigned char g, unsigned char b);//�浹ü ��� ����

	//�浹 �̺�Ʈ �޼ҵ�
	virtual void onTriggerEnter(AABB* myAABB,GameObject *OtherObj,AABB* otherAABB);
};

