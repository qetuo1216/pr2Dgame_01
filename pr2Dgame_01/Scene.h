#pragma once
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
};

