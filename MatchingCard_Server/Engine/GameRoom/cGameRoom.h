#pragma once

#include "Resource.h"
#include "cCriticalSection.h"
#include "cUser.h"
#include "Protocol.h"
#include "cMysql.h"

class cGameRoom
{
public:
	cGameRoom();
	~cGameRoom();
	void setRoomNum(int _roomnum) { mRoomNum = _roomnum; }
	int getRoomNum() { return mRoomNum; }

	void InputUser(cUser* _user);
	void BroadMsg(void* _packet, int _packetsize);
	cUser* getEnermyPtr(cUser* _user);
	
	bool SendResult(int _score, cUser* _user);

private:
	cCriticalSection mCS_GameRoom;
	int mRoomNum = 0;
	int mUserCount = 0;
	int mCheckGameResult = 0;
	cUser* mUserArray[2] = { NULL, };
	int mSaveScore[2] = { 0, };
	int mCallResultCount = 0;

};

