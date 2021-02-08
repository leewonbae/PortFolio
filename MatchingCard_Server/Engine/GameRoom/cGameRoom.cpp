#include "cGameRoom.h"
cGameRoom::cGameRoom()
{

}
cGameRoom::~cGameRoom()
{

}

void cGameRoom::InputUser(cUser* _user)
{
	mCS_GameRoom.Lock();
	_user->setRoomNum(mRoomNum);
	if (mUserCount == 0)
	{
		mUserArray[0] = _user;
	}
	else
	{
		mUserArray[1] = _user;
	}

	mUserCount++;
	mCS_GameRoom.UnLock();
}
cUser* cGameRoom::getEnermyPtr(cUser* _user)
{
	if (mUserArray[0] == NULL || mUserArray[1] == NULL)
	{
		return NULL;
	}
	if (mUserArray[0] == _user)
	{
		return mUserArray[1];
	}
	else
	{
		return mUserArray[0];
	}
}
void cGameRoom::BroadMsg(void* _packet, int _packetsize)
{
	
	for (int i = 0;i < 2;i++)
	{
		mUserArray[i]->OnSend(_packet, _packetsize);
	}
}

bool cGameRoom::SendResult(int _score, cUser* _user)
{
	bool result = false;
	mCS_GameRoom.Lock();
	PACKET_GAMERESULT_ACK sendpacket;
	mCallResultCount++;
	if (mUserArray[0] == _user)
	{
		mSaveScore[0] = _score;
		 
	}
	else
	{
		mSaveScore[1] = _score;
		 
	}

	if (mCallResultCount == 2)
	{
		 
		int winuser = 0;
		int draw = -1;
		int loseuser = 0;
		if (mSaveScore[0] > mSaveScore[1])
		{
			sendpacket.mResult = 1;
			mUserArray[0]->OnSend(&sendpacket, sendpacket.mPacketSize);
			winuser = mUserArray[0]->getUserNUM();

			sendpacket.mResult = -1;
			mUserArray[1]->OnSend(&sendpacket, sendpacket.mPacketSize);
			loseuser = mUserArray[1]->getUserNUM();
		}
		else if(mSaveScore[0]< mSaveScore[1])
		{
			sendpacket.mResult = -1;
			mUserArray[0]->OnSend(&sendpacket, sendpacket.mPacketSize);
			loseuser = mUserArray[0]->getUserNUM();

			sendpacket.mResult = 1;
			mUserArray[1]->OnSend(&sendpacket, sendpacket.mPacketSize);
			winuser = mUserArray[1]->getUserNUM();
		}
		else
		{
			draw = 0;
			sendpacket.mResult = 0;
			mUserArray[0]->OnSend(&sendpacket, sendpacket.mPacketSize);
			mUserArray[1]->OnSend(&sendpacket, sendpacket.mPacketSize);
		}
		if (draw == 0)
		{
			SINGLETON(cMysql).GameOverLog(_user->getRoomNum(), 0, 0, 0);
		}
		else
		{
			SINGLETON(cMysql).GameOverLog(_user->getRoomNum(), winuser, loseuser, -1);
		}
		
		result = true;
	}

	mCS_GameRoom.UnLock();

	return result;
}
