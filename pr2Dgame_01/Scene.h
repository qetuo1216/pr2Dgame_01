#pragma once
class Scene//���� �������� �̱��� �Ⱦ���.
{
private:

public:
	Scene();
	virtual ~Scene();

	void init();

	void update();
	void checkCollision();
	void removeDeadObjs();
	void draw();
	void debugDraw();
};

