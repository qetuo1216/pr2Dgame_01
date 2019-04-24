#include "stdafx.h"
#include "FrameWork.h"

//static 포인터 만들기
FrameWork * FrameWork::frameWork = NULL;

FrameWork::FrameWork()
{

}

FrameWork::~FrameWork()
{
}

FrameWork * FrameWork::instance()
{
	if (frameWork == NULL)
	{
		frameWork = new FrameWork();//같은 클래스 안의 private는 접근 가능
	}

	return frameWork;
}

void FrameWork::init()
{
}

void FrameWork::run()
{
}

void FrameWork::exit()
{
}
