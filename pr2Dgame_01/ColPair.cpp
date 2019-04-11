#include "stdafx.h"
#include "ColPair.h"


ColPair::ColPair(GameObject *objI, GameObject *objJ, AABB *aabbI, AABB *aabbJ)
{
	this->objI = objI;
	this->objJ = objJ;
	this->aabbI = aabbI;
	this->aabbJ = aabbJ;
}


ColPair::~ColPair()
{
}

bool ColPair::equal(GameObject * objI, GameObject * objJ, AABB * aabbI, AABB * aabbJ)
{
	//this->objI,this->objJ¿Í ObjI,ObjJ¿Í °°Àº ½ÖÀÎÁö ÆÄ¾Ç
	if (this->objI->getId()==objI->getId()	&& this->objJ->getId() == objJ->getId&&
		this->aabbI->getId()==aabbI->getId()&& this->aabbJ->getId() == aabbJ->getId())
	{
		return true;
	}

	//this->objI,this->objJ¿Í ObjJ,ObjI¿Í °°Àº ½ÖÀÎÁö ÆÄ¾Ç
	if (this->objI->getId() == objJ->getId() && this->objJ->getId() == objI->getId&&
		this->aabbI->getId() == aabbJ->getId() && this->aabbJ->getId() == aabbI->getId())
	{
		return true;
	}
		return false;

}
