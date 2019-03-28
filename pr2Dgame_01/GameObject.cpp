#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(std::string name, int tag, int state, float px, float py)
{
	this->name = name;//string을 사용하면 복사안하고 바로 넣을 수 있다.
	this->tag = tag;
	this->state = state;
	this->px = px;
	this->py = py;

}


GameObject::~GameObject()//new를 생성하면 delete를 하기위해 사용
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
