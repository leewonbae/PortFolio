#include "cSessionManager.h"
cSessionManager::cSessionManager()
{

}
cSessionManager::~cSessionManager()
{

}

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : session 객체의 생성
//작성자 : 이원배
//일  시 : 2020. 12. 01
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
cSession* cSessionManager::MakeSession()
{
	if (mSessionCount >= MAX_SESSION_COUNT)
	{
		return NULL;
	}
	// 객체 생성
	cUser* newsession = new cUser;

	mCS_SessionManager.Lock();
	for (int i = 0;i < MAX_SESSION_COUNT;i++)
	{

		if (mSessionArray[i] == NULL)
		{
			// 세션 배열에 추가
			mSessionArray[i] = newsession;


			// 세션 객체에 배열 번호 할당
			newsession->setKey(i);
			mSessionCount++;
			break;
		}
	}
	ShowSessionCount();
	mCS_SessionManager.UnLock();

	return newsession;

}


//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : session 객체의 제거
//작성자 : 이원배
//일  시 : 2020. 12. 01
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cSessionManager::ClientOut(int _sessionkey)
{
	mCS_SessionManager.Lock();
	cSession* temp = mSessionArray[_sessionkey];
	mSessionArray[_sessionkey] = NULL;
	delete temp;
	mSessionCount--;
	ShowSessionCount();
	mCS_SessionManager.UnLock();

}


//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : session 객체의 카운트 출력
//작성자 : 이원배
//일  시 : 2020. 12. 01
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cSessionManager::ShowSessionCount()
{
	cout << "SHOW SESSIONMANAGER SESSION COUNT = [ " << mSessionCount << " ] " << endl;
}