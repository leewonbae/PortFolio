#pragma once
#include "Resource.h"
#include "cUser.h"
#include "cCriticalSection.h"

//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : session ��ü�� ������
//�ۼ��� : �̿���
//��  �� : 2020. 12. 01
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class cSessionManager : public cSingleton< cSessionManager>
{
	friend class  cSingleton< cSessionManager>;
public:

	cSession* MakeSession();
	void ClientOut(int _sessionkey);

private:
	cSessionManager();
	~cSessionManager();

	void ShowSessionCount();

	cCriticalSection mCS_SessionManager;
	cSession* mSessionArray[MAX_SESSION_COUNT] = { NULL, };

	int mSessionCount = 0;
};

