#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(std::string name, int tag, int state, float px, float py)
{
	this->name = name;//string�� ����ϸ� ������ϰ� �ٷ� ���� �� �ִ�.
	this->tag = tag;
	this->state = state;
	this->px = px;
	this->py = py;

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
