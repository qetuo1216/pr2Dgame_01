#pragma once
class Scene//æ¿¿∫ ø©∑Ø∞≥∂Û ΩÃ±€≈Ê æ»æ¥¥Ÿ.
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

