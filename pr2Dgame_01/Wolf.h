#pragma once
#include "Animation.h"
#include"HUDBar.h"
class Wolf : public Animation
{
private:
	enum State
	{
		attack, run, hit, death
	};
	State state;

	int hp;//���� ü�� 
	HUDBar * hpBar;//ü�¹� // �����ͷ� �ؾ� ���� ���� ���� 
public:
	Wolf(float px,float py);
	~Wolf();

	void init();
	void update(); 

	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//����
	void onTriggerExit(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//��Ż

	void OnAnimationEvent(int aniId, int aniFrame);//�ִϸ��̼� ��� ��ȯ �̺�Ʈ

	void changeAniState(State s); //�ִϸ��̼� ���� ��ȯ �޼ҵ�

};

