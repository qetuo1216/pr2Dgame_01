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
