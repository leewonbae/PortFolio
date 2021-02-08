#pragma once
#include "Resource.h"
#include "cUser.h"
#include "cCriticalSection.h"
#include "cGameRoom.h"
 

class cGameManager : public cSingleton<cGameManager>
{
	friend class cSingleton<cGameManager>;
public:
	void MatchingReq(cUser* _user);
	void MatchingCancle(cUser* _user);
	void DeleteRoom(int _roomnum);
	cGameRoom* getRoomPtr(int _roomnum);

private:
	cGameManager();
	~cGameManager();
	
	cCriticalSection mCS_GameManager;
	list<cUser*> mMatchingUserlist;
	list<cUser*>::iterator mIter;
	cGameRoom* mGameArray[26] = { NULL, };
	int mGameRoomCount = 0;

};

