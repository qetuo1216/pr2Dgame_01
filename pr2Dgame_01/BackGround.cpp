#include "stdafx.h"
#include "BackGround.h"
#include "timer.h"
#include "graphic.h"
BackGround::BackGround(float px, float py):SpliteObject("���",0,true,px,py)//���� 0�� �Ʊ�,1���� ��,2�� �������
{
}

BackGround::~BackGround()
{
}

void BackGround::init()
{
	//��� �̹��� �ε��ϱ�
	readBMPRect("asset/���.bmp", 0, 0, 4303, 224, &sprite);

	//�÷��̾� �̵��� ���� �浹ü �߰�. 0�� ��,1�� �Ʒ�, 2�� ����,3�� ������
	addCollider(new AABB(0, 140, 4304, 25, 0));//���� �̵� ���� �浹ü
	addCollider(new AABB(208, 160, 35, 15, 0));//���� �̵� ���� �浹ü(��ֹ�)
	addCollider(new AABB(0, 220, 4304, 25, 1));//�Ʒ��� �̵� ���� �浹ü

	leftAABB = new AABB(-30, 140, 25, 105, 2);//���� �浹ü
	addCollider(leftAABB);

	rightAABB = new AABB(getClientWidth()+15, 140, 25, 105, 3);//���� �浹ü
	addCollider(rightAABB);
	

	//��ũ�� �ӵ� �ʱ�ȭ
	speed = 100;//�ʴ� 100px�� �̵�
	scroll = true;//��ũ�� ����
}

void BackGround::update()
{
	if (scroll==true)
	{
		//��ũ�� �̵�
		float d = speed * getDelteTime();

		//translate(-d, 0);//��� ���Ƴ���
		//px = px - d;

		//��� ��ǥ ���
		/*printf("ȭ���� ũ�� : %d\n", getClientWidth());
		printf("�׸� ���� ���� : %d\n ", splite.width);*/
		//printf("%d\n", px);
		//��� ���� �Ǵ��ϱ�
		int minPx = -(sprite.width - getClientWidth());
		//printf("%d", minPx);

		if (px > minPx)//��� ��ũ�� ��
		{
			translate(-d, 0);//��� ���� ��ũ��
			leftAABB->translate(d, 0);//�����浹ü
			rightAABB->translate(d, 0);//�����浹ü
		}
		else//��ũ�� ���� 
		{//px�� ��ũ�� �߿� minPx���� �۾����� ���
			int dx = minPx - px+1;

			translate(dx, 0);//�� minPx�� ����ģ ��ŭ ���������� �̵�
			leftAABB->translate(-dx, 0);//�����浹ü
			rightAABB->translate(-dx, 0);//�����浹ü

			scroll = false;
		}
	}

}

void BackGround::onTriggerStay(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	if (OtherObj->GetName() == "������"&&otherAABB->getId() == 0 && myAABB->getId() == 0)
	{
		//printf("�浹");
		OtherObj->translate(0, 1);
	}

	if (OtherObj->GetName() == "������"&&otherAABB->getId() == 0 && myAABB->getId() == 1)
	{
		OtherObj->translate(0, -1);
	}

	if (OtherObj->GetName() == "������"&&otherAABB->getId() == 0 && myAABB->getId() == 2)
	{
		OtherObj->translate(1, 0);
	}
	if (OtherObj->GetName() == "������"&&otherAABB->getId() == 0 && myAABB->getId() == 3)
	{
		OtherObj->translate(-1, 0);
	}
}