#pragma once
class Scene//���� �������� �̱��� �Ⱦ���.
{
private:

public:
	Scene();
	virtual ~Scene();

	void init();
	void exit();

	void update();
	void checkCollision();
	void removeDeadObjs();
	void draw();
	void debugDraw();
};

