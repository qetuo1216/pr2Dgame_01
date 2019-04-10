#include "stdafx.h"
#include "TestObjA.h"
#include "timer.h"
#include "Input.h"
TestObjA::TestObjA(float px, float py) :GameObject("�׽�ƮA", 0, 1, px, py)
{
}

TestObjA::~TestObjA()
{
}

void TestObjA::init()
{
	//�浹ü �߰��ϱ�
	//col.push_back(new AABB(0+px, 0+py, 100, 100));//���ӿ�����Ʈ�� ��������
	addCollider(new AABB(0 + px, 0 + py, 100, 100,0));
	//�̵��ӵ� �ʱ�ȭ
	speed = 100;
}

void TestObjA::update()
{
	float dist = speed * getDelteTime();

	if (getKey(VK_RIGHT) == true)
	{
		translate(dist, 0);
		//printf("���������� �̵�");
	}
	if (getKey(VK_LEFT) == true)
	{
		translate(-dist, 0);
		//printf("���������� �̵�");
	}
	if (getKey(VK_UP) == true)
	{
		translate(0, -dist);
		//printf("���������� �̵�");
	}
	if (getKey(VK_DOWN) == true)
	{
		translate(0, dist);
		//printf("���������� �̵�");
	}
}

void TestObjA::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	std::cout << "testObjA�� " << OtherObj->GetName() << " �� �浹��" << std::endl;
	std::cout << "myAABB ���̵� " << myAABB->getId() << ", otherAABB ���̵�" << otherAABB->getId()<<std::endl;
}
