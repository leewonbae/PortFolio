#pragma once
#include "Resource.h"
#include "cUser.h"
#include "cCriticalSection.h"

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : session 객체의 관리자
//작성자 : 이원배
//일  시 : 2020. 12. 01
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

