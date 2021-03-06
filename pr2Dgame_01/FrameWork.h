#pragma once
#include "Scene.h"
class FrameWork	//특별히 상속 필요 없다.
{
private:
	//생성자&소멸자
	FrameWork();
	virtual ~FrameWork();

	//객체 저장하는 정적 포인터(객체 1개)
	static FrameWork * frameWork;

	Scene * scene;//scene객체 포인터 : 현재 사용중인 씬
	Scene * nextScene;//전환할 다음 씬 포인터
public:
	//싱글톤 객체(인스턴스) 반환 메소드(static)
	static FrameWork * instance();//pool이 null이면 객체를 만들고, 있으면 계속 사용한다.

	//프레임워크 활용 메소드
	void init(HWND hWnd,int width,int hight);
	void run();
	void exit();

	//씬 로드 기능
	void LoadScene(Scene * nextScene);
};

