#pragma once
#include "GameObject.h"
class Scene//���� �������� �̱��� �Ⱦ���.
{
private:

public:
	Scene();
	virtual ~Scene();

	virtual void init();
	void exit();

	void update();
	void checkCollision();
	void removeDeadObjs();
	void draw();
	void debugDraw();

	void addGameObject(GameObject *o,int order);
};

