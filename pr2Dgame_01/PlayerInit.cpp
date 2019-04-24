#include "stdafx.h"
#include "Player.h"

void Player::init()
{
	//�ִϸ��̼� �ε��ϱ�
	//Sprite sprite;
	//0�� idle
	for (int i = 0; i < 4; i++)
	{

		Sprite sprite;//��

		readBMPRect("asset/naruto.bmp", 2 + i * (42 + 2), 12, 42, 54, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12

		//�浹ü �߰��ϱ�
		//sprite.col.push_back(new AABB(0, 0, 42, 54, 0));
		//sprite.col.clear();//���� �� �����

		addSpriteCollider(&sprite, new AABB(0, 50, 42, 5, 0), px, py);//�ذ��� ��ǥ�� ��� ������ ��ǥ�� ��߳�, �浹ü�� �̿��� �� ���� ���� ���־��Ѵ�.
																	//�̵� ������ ���� �浹ü : 0��
		addSpriteCollider(&sprite, new AABB(0, 0, 42, 54, 1), px, py);//�� ������ �ޱ� ���� �浹ü : 1��
		addAniFrame(sprite, idle);//0�� �迭�� �������
		//frames.push_back(sprite);//�ִϸ��̼��� frames�� ����
	}
	//sprite.col.clear();//�߰��� �浹ü ����

	//1�� walk
	for (size_t i = 0; i < 6; i++)
	{
		Sprite sprite;
		readBMPRect("asset/naruto.bmp", 2 + i * (36 + 2), 80, 36, 56, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12

		addSpriteCollider(&sprite, new AABB(4, 50, 32, 5, 0), px, py);
		addSpriteCollider(&sprite, new AABB(4, 0, 32, 56, 1), px, py);

		addAniFrame(sprite, walk);//1�� �迭�� �������
	}

	//2�� run
	for (size_t i = 0; i < 6; i++)
	{
		Sprite sprite;

		readBMPRect("asset/naruto.bmp", 2 + i * (68 + 2), 150, 68, 45, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12


		//��Ŀ����Ʈ �����ϱ�
		sprite.ax = 10;//+���̹����� �������� �̵�,-�� ������
		sprite.ay = -10;//+���̹����� ������ �̵�,-�� �Ʒ���

		addSpriteCollider(&sprite, new AABB(-15, 50, 65, 5, 0), px, py);
		addSpriteCollider(&sprite, new AABB(-15, 10, 65, 45, 1), px, py);
		addAniFrame(sprite, run);//2�� �迭�� �������
	}

	//3�� jump
	for (size_t i = 0; i < 2; i++)
	{
		Sprite sprite;

		readBMPRect("asset/naruto.bmp", 2 + i * (50 + 2), 332, 50, 51, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12

		//addSpriteCollider(&sprite, new AABB(0, 70, 50, 5, 0), px, py);
		//��Ŀ����Ʈ �����ϱ�
		//sprite.ay = 20;//+���̹����� ������ �̵�,-�� �Ʒ���

		addSpriteCollider(&sprite, new AABB(0, 0, 45, 49, 1), px, py);
		addAniFrame(sprite, jump);//3�� �迭�� �������
	}

	//4�� attack
	for (size_t i = 0; i < 3; i++)
	{
		Sprite sprite;

		readBMPRect("asset/naruto.bmp", 2 + i * (58 + 2), 584, 58, 49, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12

		//��Ŀ����Ʈ �����ϱ�
		sprite.ay = -5;//+���̹����� ������ �̵�,-�� �Ʒ���

		addSpriteCollider(&sprite, new AABB(0, 48, 58, 5, 0), px, py);
		addSpriteCollider(&sprite, new AABB(0, 0, 58, 48, 1), px, py);
		addAniFrame(sprite, attack);//4�� �迭�� �������
	}

	//5�� hit
	Sprite sprite;
	readBMPRect("asset/naruto.bmp", 2, 977, 42, 40, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12
	sprite.ax = 10;//+���̹����� �������� �̵�,-�� ������

	//hit �浹ü �߰�
	addSpriteCollider(&sprite, new AABB(-5, 0, 42, 40, 1), px, py);
	addAniFrame(sprite, hit);//5�� �迭�� �������

	//6�� airAttack
	for (size_t i = 0; i < 3; i++)
	{
		Sprite sprite;

		readBMPRect("asset/naruto.bmp", 2 + i * (57 + 2), 1416, 57, 56, &sprite);
		//addSpriteCollider(&sprite, new AABB(0, 0, 57, 56, 0), px, py);

		addAniFrame(sprite, airAttack);//4�� �迭�� �������
	}

	//death �̹���
	for (int i = 0; i < 3; i++)
	{
		Sprite sprite;

		readBMPRect("asset/naruto.bmp", 2 + i * (58 + 2), 1099, 58, 40, &sprite);
		sprite.ay = -20;
		addAniFrame(sprite, death);
	}
	//�ִϸ� �ӵ� �����ϱ�
	setFrameDelay(0.15);

	//��� �̵� ���� �浹ü �߰��ϱ�
	//addCollider(new AABB(0, 55, 40, 1, 0));

	//�ʱ� �ִϸ� �����ϱ�
	state = idle;
	play(idle);

	//�̵� �ӵ� ����
	walkSpeed = 50;
	runSpeed = 100;

	//���� �ð� ���� �ʱ�ȭ
	//jumpDelay = 0.5;
	jumpTimer = 0;

	//���� �̵� �� ���ӵ�
	jumpMoveSpeed = 100;
	jumpUpSpeed = 200;
	jumpAcc = 400;//

	//hit �ִϸ��̼� ���ӽð�
	hitDelay = 0.5f;

	//hp ����
	hp = 100;
	hpBar = new HUDBar(px-6,py-5);
	addChildObject(hpBar,2);
}