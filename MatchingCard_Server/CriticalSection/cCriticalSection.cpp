#include "cCriticalSection.h"
cCriticalSection::cCriticalSection()
{
	//�ʱ�ȭ
	InitializeCriticalSection(&mCriticalSection);
}
cCriticalSection::~cCriticalSection()
{
	//����
	DeleteCriticalSection(&mCriticalSection);
}

void cCriticalSection::UnLock()
{
	// �Ӱ迵�� ����
	LeaveCriticalSection(&mCriticalSection);
}
void cCriticalSection::Lock()
{
	//�Ӱ迵�� ����
	EnterCriticalSection(&mCriticalSection);
}