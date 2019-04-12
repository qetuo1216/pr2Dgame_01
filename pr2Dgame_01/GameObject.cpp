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
	this->alive = true;	//�����ڿ��� ��ü�� ����������� �ʱ�ȭ
	this->px = px;
	this->py = py;

	//�浹ü �⺻ ���� ����
	colR = 255;
	colG = 0;
	colB = 0;

	//���̵� �Ҵ��ϱ�
	id = ID++;//��ü�� ������ �� ���� �����Ѵ�.
}


GameObject::~GameObject()//new�� �����ϸ� delete�� �ϱ����� ���
{
	//���� ������Ʈ�� �߰��� AABB�����ϱ�
	for (int i = 0; i < col.size(); i++)
	{
		delete col[i];
	}
	//stl vector �Ѳ����� �����
	col.clear();
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

void GameObject::debugDraw()
{
	//���ӿ�����Ʈ �浹ü �׸���
	for (int i = 0; i < col.size(); i++)
	{
		col[i]->debugDraw(colR,colG,colB);
	}
}


int GameObject::getId()
{
	return id;
}

int GameObject::getTag()
{
	return tag;
}

bool GameObject::getState()
{
	return state;
}

void GameObject::setState(bool state)
{
	this->state = state;
}

bool GameObject::getAlive()
{
	return alive;
}

void GameObject::setAlive(bool alive)
{
	this->alive = alive;
}

std::string GameObject::GetName()
{
	return name;
}

std::vector<AABB*> GameObject::getCollider()
{
	return col;
}

void GameObject::translate(float dx, float dy)
{
	px = px + dx;
	py = py + dy;

	//�浹ü �̵���Ű��
	for (int i = 0; i < col.size(); i++)
	{
		col[i]->translate(dx, dy);
	}
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

void GameObject::addCollider(AABB * aabb)
{
	//���ӿ�����Ʈ ��ǥ �����ϱ�
	aabb->translate(px, py);

	//�浹ü �߰��ϱ� 
	col.push_back(aabb);

}

void GameObject::setColColor(unsigned char r, unsigned char g, unsigned char b)
{
	colR = r;
	colG = g;
	colB = b;
}

void GameObject::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
}

void GameObject::onTriggerStay(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
}

void GameObject::onTriggerExit(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
}
