#include "stdafx.h"
#include "FrameWork.h"

//static ������ �����
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
		frameWork = new FrameWork();//���� Ŭ���� ���� private�� ���� ����
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
