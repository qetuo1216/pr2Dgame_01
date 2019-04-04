#include "stdafx.h"
#include "GameObject.h"
#include "gameObjectPool.h"
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

int GameObject::getId()
{
	return id;
}

bool GameObject::getState()
{
	return state;
}

void GameObject::setState(bool state)
{
	this->state = state;
}

void GameObject::translate(float dx, float dy)
{
	px = px + dx;
	py = py + dy;
}

void GameObject::addGameObject(GameObject * o,int order)
{
	//1//���� ������Ʈ Ǯ ��ü ��������
	gameObjectPool * pool = gameObjectPool::instance();

	//2//Ǯ�� ��ü �߰��ϱ�
	pool->addGameObject(o,order);
}

void GameObject::delGameObject(GameObject * o)
{
	//1//���� ������Ʈ Ǯ ��ü ��������
	gameObjectPool * pool = gameObjectPool::instance();

	//2//Ǯ�� ��ü �����ϱ�
	pool->delGameObject(o);//�ڵ尡 ���������� ������ �����.
}
