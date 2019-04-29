#include "stdafx.h"
#include "gameObjectPool.h"
#include <iostream>
//static 포인터 만들기
gameObjectPool * gameObjectPool::pool=NULL;

//생성자&소멸자
gameObjectPool::gameObjectPool()
{
}


gameObjectPool::~gameObjectPool()
{
}

//인스턴스 반환 메소드(객체가 있는지 검사)
gameObjectPool * gameObjectPool::instance()
{
	if (gameObjectPool::pool == NULL)
	{
		gameObjectPool::pool = new gameObjectPool();//같은 클래스 안의 private는 접근 가능
	}

	return gameObjectPool::pool;

}

void gameObjectPool::addGameObject(GameObject * o, int order)//order은 레이어 번호
{


		obj[order].push_back(o);	//객체 추가//크기가 늘어나면서 저장이 된다.
		o->init();			//객체 초기화
	
}

void gameObjectPool::delGameObject(GameObject * o)
{
	//객체 안에서 바로 delete하는 것은 코드가 안전하지 못한다.
	int id = o->getId();
	for (int l = 0; l < MAX_LAYER; l++)
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			if (obj[l][i]->getId() == id)//일치하는 아이디를 찾음
			{
				//1//객체 delete
				//delete obj[l][i];//또는 delete o; //소멸자가 실행
				//2//stl vector에서 저장공간 삭제
				//obj[l].erase(obj[l].begin() + i);

				//수정)바로 지우지 말고 나중에 지우도록 임시로 게임오브젝트가 삭제되어야함을 표시해둔다.
				obj[l][i]->setAlive(false);
			}
		}
	}
}


void gameObjectPool::update()
{
	for (int l = 0; l < MAX_LAYER; l++)
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			obj[l][i]->update();
		}
	}
}

void gameObjectPool::draw()
{
	for (int l = 0; l < MAX_LAYER; l++)//l은 레이어 번호
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			if (obj[l][i]->getState() == true)//상태 검사
			{
				obj[l][i]->draw();
			}
		}
	}
	
}

void gameObjectPool::resetColPairs()
{
	for (int k = 0; k < colPair.size(); k++)
	{
		colPair[k]->setCollided(false);//충돌이 끝났다고 상태 변경
	}
}
void gameObjectPool::removeUnColliedPairs()
{
	//삭제되는 게임오브젝트가 충돌쌍에 있으면 제거함
	for (int k = 0; k < colPair.size(); k++)
	{
		
		//o가 colPair의 i번째에 있는 objI나 J와 같으면 쌍을 제거
		if (colPair[k]->getCollided()==false)
		{
			GameObject * objI = colPair[k]->getObjI();
			GameObject * objJ = colPair[k]->getObjJ();
			AABB * aabbI = colPair[k]->getAABBI();
			AABB * aabbJ = colPair[k]->getAABBJ();

			//충돌쌍이 제거되면서 발생하는 충돌 종료 이벤트를 발생
			objI->onTriggerExit(aabbI, objJ, aabbJ);
			objJ->onTriggerExit(aabbJ, objI, aabbI);

			//충돌쌍 delete하기
			delete colPair[k];

			//백터 자리 제거
			colPair.erase(colPair.begin() + k);

			//지우지 않은때만 k를 증가
			k--;
		}
	}
}
void gameObjectPool::clear()
{
	//풀의 모든 게임오브젝트 삭제
	for (int l = 0; l < MAX_LAYER; l++)
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			delete obj[l][i];
		}
		obj[l].clear();
	}
}

GameObject * gameObjectPool::find(string name)
{
	for (int l = 0; l < MAX_LAYER; l++)
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			if (obj[l][i]->GetName()== name)
			{
				return obj[l][i];
			}
		}
		
	}
	return NULL;//내가 찾는 포인터가 없다.
}

void gameObjectPool::checkCollision()//충돌 검사 업데이트가 끝나면 한다.
{
	//모든 충돌쌍의 상태를 충돌이 끝났다고 상태를 표시함.
	resetColPairs();

	//같은 레이어에 있는 게임 오브젝트 충돌검사
	for (int l = 0; l < MAX_LAYER; l++)
	{
		checkSameLayerCollision(l);
	}
	
	//다른 레이어에 있는 게임 오브젝트 충돌검사

	for (int lJ = 0; lJ < MAX_LAYER; lJ++)
	{
		for (int lI = 0; lI < MAX_LAYER; lI++)
		{
			if (lI < lJ) 
			{ 
				checkDifLayerCollision(lI, lJ); 
			}
		}
	}

	removeUnColliedPairs();//충돌이 종료된 쌍 제거
		//std::cout <<endl<< "--------------------" << endl; 
}

void gameObjectPool::checkDifLayerCollision(int lI, int lJ)
{
	//////////lI, lJ-번레이어 충돌검사하기////////
	for (int j = 0; j < obj[lJ].size(); j++)
	{
		for (int i = 0; i < obj[lI].size(); i++)
		{
			GameObject * objI = obj[lI][i];
			GameObject * objJ = obj[lJ][j];

			//objI 와 objJ가 삭제대상이 아닌경우만..충돌 검사를 실행함
			if (objI->getAlive() == true && objJ->getAlive() == true)
			{
				////////objI, objJ에서 충돌체 목록 가져오기/////
				std::vector<AABB *> colI = objI->getCollider();
				std::vector<AABB *> colJ = objJ->getCollider();

				/////////////충돌체(AABB)간의 충돌검사//////////
				for (int ii = 0; ii < colI.size(); ii++)
				{
					for (int jj = 0; jj < colJ.size(); jj++)
					{
						AABB * aabbI = colI[ii];  //ObjI에서 가져온 ii번째 AABB
						AABB * aabbJ = colJ[jj];  //ObjI에서 가져온 jj번째 AABB

						//////aabbI 와 aabbJ 가 충돌했는지를 검사함//////
						float x0, y0, x1, y1;    //aabbI의 꼭지점좌표
						float a0, b0, a1, b1;    //aabbJ의 꼭지점좌표

						aabbI->getBB(x0, y0, x1, y1);
						aabbJ->getBB(a0, b0, a1, b1);

						if (x1 >= a0 && x0 <= a1 && y1 >= b0 && b1 >= y0)
						{
							///////////////충돌쌍이 저장되어 있는지를 판단함/////////
							bool checkInColPair = checkInColPairs(objI, objJ, aabbI, aabbJ);

							if (checkInColPair == false) //[A]ObjI (aabbI), ObjJ(aabbJ)의 충돌쌍이 저장되어 있지 않으면..
							{
								//// -OnTriggerEnter 이벤트 발생시키고..충돌쌍을 저장함									
								//[1]ObjI에게..자신의 충돌체 aabbI와 게임오브젝트 ObjJ와 충돌하고..ObjJ의 aabbJ와 충돌이 발생함
								objI->onTriggerEnter(aabbI, objJ, aabbJ);

								//[2]ObjJ에게..자신의 충돌체 aabbJ와 게임오브젝트 ObjI와 충돌하고..ObjI의 aabbI와 충돌이 발생함
								objJ->onTriggerEnter(aabbJ, objI, aabbI);

								//[3]충돌 정보 저장하기...
								colPair.push_back(new ColPair(objI, objJ, aabbI, aabbJ));
							}
							else { //[B]ObjI (aabbI), ObjJ(aabbJ)의 충돌쌍이 저장되어 있으면...

								  //// -OnTriggerStay 이벤트 발생 (충돌이 반복되고 있음)
								objI->onTriggerStay(aabbI, objJ, aabbJ);

								//[2]ObjJ에게..자신의 충돌체 aabbJ와 게임오브젝트 ObjI와 충돌하고..ObjI의 aabbI와 충돌이 발생함
								objJ->onTriggerStay(aabbJ, objI, aabbI);
							}

						}

					}
				}

			}
		}
	}
}

void gameObjectPool::checkSameLayerCollision(int l)
{
	//1//1번 레이어 충돌검사하기
	for (int j = 0; j < obj[l].size(); j++)
	{
		for (int i = 0; i < j; i++)
		{
			//printf("%s", obj[1][i]->GetName);;
			//if (i < j)//중복된 순서쌍 제거
			//std::cout << "[" << obj[1][i]->GetName() << ", " << obj[1][j]->GetName() << "]";
			//충돌체 생성
			GameObject * objI = obj[l][i];
			GameObject * objJ = obj[l][j];

			//objI와 objJ가 삭제 대상이 아닌 경우만 충돌검사한다.
			if (objI->getAlive() == true && objJ->getAlive() == true)
			{
				//objI와 objJ에서 충돌체 목록 가져오기
				std::vector<AABB *> colI = objI->getCollider();
				std::vector<AABB *> colJ = objJ->getCollider();

				//충돌체 (AABB)간의 충돌검사
				for (int ii = 0; ii < colI.size(); ii++)
				{
					for (int jj = 0; jj < colJ.size(); jj++)
					{
						AABB * aabbI = colI[ii];//objI에서 가져온 ii번째 AABB//출력된 사각형
						AABB * aabbJ = colJ[jj];//objI에서 가져온 ii번째 AABB

						//aabbI와 aabbJ가 사각형 단위로 충돌했는지 검사
						//cout << objI->GetName() << ", " << objJ->GetName() << endl;

						//사각형의 좌표를 가져와서 선 단위로 가져온다.(좌측상단,우측하단)
						float x0, y0, x1, y1;//aabbI의 꼭지점 좌표
						float a0, b0, a1, b1;//aabbJ의 꼭지점 좌표

						aabbI->getBB(x0, y0, x1, y1);
						aabbJ->getBB(a0, b0, a1, b1);

						if (x1 >= a0 && x0 <= a1 && y1 >= b0 && b1 >= y0)
						{
							bool checkColPair = checkInColPairs(objI, objJ, aabbI, aabbJ);

							if (checkColPair == false)
							{
								//A//objI(aabbI),objJ(aabbJ)의 충돌쌍이 저장되어 있지 않으면
								//////onTrigerEnter이벤트 발생
								//충돌 정보(이벤트) 전달
									//1//objI에게 자신의 충돌체 aabbI와 게임오브젝트 ObjJ와 충돌하고, objJ의 aabbJ와 충돌이 발생
								objI->onTriggerEnter(aabbI, objJ, aabbJ);

								//2//objJ에게 자신의 충돌체 aabbJ와 게임오브젝트 ObjI와 충돌하고, objI의 aabbI와 충돌이 발생
								objJ->onTriggerEnter(aabbJ, objI, aabbI);

								//3//충돌 정보 저장하기
								colPair.push_back(new ColPair(objI, objJ, aabbI, aabbJ));
							}
							else
							{
								//B//objI(aabbI),objJ(aabbJ)의 충돌쌍이 저장되어 있으면
								//////onTrigerStay이벤트 발생(반복 충돌)
									//objI->onTriggerStay()

									//1//objI에게 자신의 충돌체 aabbI와 게임오브젝트 ObjJ와 충돌하고, objJ의 aabbJ와 충돌이 발생(계속)
								objI->onTriggerStay(aabbI, objJ, aabbJ);

								//2//objJ에게 자신의 충돌체 aabbJ와 게임오브젝트 ObjI와 충돌하고, objI의 aabbI와 충돌이 발생(계속)
								objJ->onTriggerStay(aabbJ, objI, aabbI);
							}

							/*cout << "충돌 정보----------------------" << endl;
							cout << "첫번째 객체 :" << objI->GetName() << endl;
							cout << "첫번째 객체 aabb의 ID:" << aabbI->getId() << endl;

							cout << "두번째 객체 :" << objJ->GetName() << endl;
							cout << "첫번째 객체 aabb의 ID:" << aabbJ->getId() << endl;*/

						}
					}
				}
				/*//충돌 상태가 충돌 끝으로 유지되는 충돌쌍은 충돌이 된 것으로 표시
				for (int k = 0; k < colPair.size(); k++)
				{
					if (colPair[k]->getCollided() == false)
					{
						printf("\n충돌이 끝남");

						//충돌쌍 삭제
						delete colPair[k];

						//stlVector 삭제
						colPair.erase(colPair.begin() + k);
						k--;
					}
				}*/
			}
		}


	}
}

void gameObjectPool::removeDeadObjs()
{
	//객체 안에서 바로 delete하는 것은 코드가 안전하지 못한다.
	for (int l = 0; l < MAX_LAYER; l++)
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
				GameObject *o = obj[l][i];
			
			if (o->getAlive()==false)//일치하는 아이디를 찾음
			{
				removeDeadColPair(o);

				//1//게임오브젝트 delete
				delete o;

				//2//stl vector에서 저장공간 삭제
				obj[l].erase(obj[l].begin() + i);

				i--;//지원진 경우 1칸이 비는 것을 당겨와야한다.
				
			}
		}
	}
}

void gameObjectPool::removeDeadColPair(GameObject * o)
{
	//삭제되는 게임오브젝트가 충돌쌍에 있으면 제거함
	for (int k = 0; k < colPair.size(); k++)
	{
		GameObject * objI = colPair[k]->getObjI();
		GameObject * objJ = colPair[k]->getObjJ();
		//o가 colPair의 i번째에 있는 objI나 J와 같으면 쌍을 제거
		if (o->getId() == objI->getId() || o->getId() == objJ->getId())
		{
			AABB * aabbI = colPair[k]->getAABBI();
			AABB * aabbJ = colPair[k]->getAABBJ();

			//충돌쌍이 제거되면서 발생하는 충돌 종료 이벤트를 발생
			objI->onTriggerExit(aabbI, objJ, aabbJ);
			objJ->onTriggerExit(aabbJ, objI, aabbI);

			//충돌쌍 delete하기
			delete colPair[k];

			//백터 자리 제거
			colPair.erase(colPair.begin() + k);

			//지우지 않은때만 k를 증가
			k--;
		}
	}

}

bool gameObjectPool::checkInColPairs(GameObject * objI, GameObject * objJ, AABB * aabbI, AABB * aabbJ)
{
	
	//충돌쌍이 저장되어있는지 판단.
	for (int k = 0; k < colPair.size(); k++)
	{
		//calPair쌍과 objI(aabbI),objJ(aabbJ)이 저장되어있는가
		if (colPair[k]->equal(objI, objJ, aabbI, aabbJ) == true)
		{
			colPair[k]->setCollided(true);//아직 충돌이 끝나지 않음
			
			return true;
		}
	}

	return false;
}



void gameObjectPool::debugDraw()
{
	for (int l = 0; l < MAX_LAYER; l++)//l은 레이어 번호
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			//if (obj[l][i]->getState() == true)//상태 검사
			{
				obj[l][i]->debugDraw();
			}
		}
	}
}
