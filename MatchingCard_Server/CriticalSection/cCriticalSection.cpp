#include "cCriticalSection.h"
cCriticalSection::cCriticalSection()
{
	//초기화
	InitializeCriticalSection(&mCriticalSection);
}
cCriticalSection::~cCriticalSection()
{
	//제거
	DeleteCriticalSection(&mCriticalSection);
}

void cCriticalSection::UnLock()
{
	// 임계영역 해제
	LeaveCriticalSection(&mCriticalSection);
}
void cCriticalSection::Lock()
{
	//임계영역 설정
	EnterCriticalSection(&mCriticalSection);
}