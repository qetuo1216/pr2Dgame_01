#include "stdafx.h"
#include "GameObject.h"

//���̵� static ���� �ʱ�ȭ
int GameObject::ID = 0;//��ü �����ø��� ������Ŵ

GameObject::GameObject(std::string name, int tag, bool state, float px, float py)
{
	this->name = name;//string�� ����ϸ� ������ϰ� �ٷ� ���� �� �ִ�.
	this->tag = tag;
	this->state = state;

	this->px = px;
	this->py = py;

	//���̵� �Ҵ��ϱ�
	id = ID++;//��ü�� ������ �� ���� �����Ѵ�.
}


GameObject::~GameObject()//new�� �����ϸ� delete�� �ϱ����� ���
{
}

void GameObject::init()
{
}

void GameObject::update()
{
}

void GameObject::draw()
{
}

void GameObject::translate(float dx, float dy)
{
	px = px + dx;
	py = py + dy;
}
