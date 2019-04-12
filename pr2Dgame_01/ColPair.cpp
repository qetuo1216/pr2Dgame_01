#include "stdafx.h"
#include "ColPair.h"


ColPair::ColPair(GameObject *objI, GameObject *objJ, AABB *aabbI, AABB *aabbJ)
{
	this->objI = objI;
	this->objJ = objJ;
	this->aabbI = aabbI;
	this->aabbJ = aabbJ;

	collided = true;//충돌상태일때 생성자가 동작
}


ColPair::~ColPair()
{
}

bool ColPair::equal(GameObject * objI, GameObject * objJ, AABB * aabbI, AABB * aabbJ)
{
	//this->objI,this->objJ와 ObjI,ObjJ와 같은 쌍인지 파악
	if (this->objI->getId()==objI->getId()	&& this->objJ->getId() == objJ->getId()&&
		this->aabbI->getId()==aabbI->getId()&& this->aabbJ->getId() == aabbJ->getId())
	{
		return true;
	}

	//this->objI,this->objJ와 ObjJ,ObjI와 같은 쌍인지 파악
	if (this->objI->getId() == objJ->getId() && this->objJ->getId() == objI->getId()&&
		this->aabbI->getId() == aabbJ->getId() && this->aabbJ->getId() == aabbI->getId())
	{
		return true;
	}
		return false;

}

GameObject * ColPair::getObjI()
{
	return objI;
}

GameObject * ColPair::getObjJ()
{
	return objJ;
}

AABB * ColPair::getAABBI()
{
	return aabbI;
}

AABB * ColPair::getAABBJ()
{
	return aabbJ;
}

bool ColPair::getCollided()
{
	return collided;
}

void ColPair::setCollided(bool collided)
{
	this->collided = collided;
}
