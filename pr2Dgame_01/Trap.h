#pragma once
#include "Animation.h"
class Trap :public Animation
{
private:
	//�ִϸ��̼� ����
	enum State
	{idle=0,attack,death,die};

	//�ִϸ��̼� ���� ����
	State state;
	int hp;//Ʈ�� ü��
public:
	Trap(float px,float py);
	~Trap();

	void init();
	void update();
	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//����
	void onTriggerExit(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//��Ż
	void changeAniState(State s);
	//���� �̺�Ʈ �޼ҵ� �������̵�
	//void DoDamage(GameObject *fromObj, GameObject *toObj, AABB* fromAABB, int damage);

	//�ִϸ��̼� ��� ��ȯ �̺�Ʈ
	void OnAnimationEvent(int aniId, int aniFrame);
};

