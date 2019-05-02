#pragma once
#include "Animation.h"
#include "HUDBar.h" 
class Ninja :public Animation
{
private:
	//�ִϸ��̼� ����
	enum State
	{
		drop = 0, idle, attack, hit, death
	};

	//�ִϸ��̼� ���� ����
	State state;

	int hp;//���� ü�� 
	HUDBar * hpBar;//ü�¹� // �����ͷ� �ؾ� ���� ���� ���� 

	float dieDelay;//die�ִϸ��̼� ���� �ð�
	
	float dropSpeed;
	float groundY;

	//���ڰ� ������������ �Ǵ��ϴ� ����
	bool isAttack;

public:
	Ninja(float px,float py);
	~Ninja();

	void init();
	void update();

	void aniDrop();
	void aniTest();

	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//����
	void onTriggerExit(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//��Ż
		
	void OnAnimationEvent(int aniId, int aniFrame);//�ִϸ��̼� ��� ��ȯ �̺�Ʈ

	void changeAniState(State s); //�ִϸ��̼� ���� ��ȯ �޼ҵ�
};

