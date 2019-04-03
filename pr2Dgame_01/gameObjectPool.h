#pragma once
//싱글톤사용하기
//게임오브젝트를 배열 형태로 밖에서 객체를 못만들게 한다.
class gameObjectPool
{
private:
	//생성자와 소멸자를 private로 넣기
	gameObjectPool();//기본 생성자
	virtual ~gameObjectPool();

	//싱글톤을 저장할 정적 포인터(객체 1개)
	static gameObjectPool * pool;//
	
public:
	//객체 가져오기 스테틱(정적) 메소드
	static gameObjectPool * instance();//pool이 null이면 객체를 만들고, 있으면 계속 사용한다.
};

