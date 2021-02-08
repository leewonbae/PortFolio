#include "cGameManager.h"
cGameManager::cGameManager()
{

}
cGameManager::~cGameManager()
{


}

void cGameManager::MatchingReq(cUser* _user)
{
	mCS_GameManager.Lock();
	if (mMatchingUserlist.empty())
	{
		mMatchingUserlist.push_back(_user);
	}

	else
	{
		PACKET_GAMESTART_ACK sendpacket;
		cUser* temp = mMatchingUserlist.front();
		mMatchingUserlist.pop_front();
		
		for (int i = 1;i < 26;i++)
		{
			if (mGameArray[i] == NULL)
			{
				cGameRoom* newroom = new cGameRoom;
				mGameArray[i] = newroom;
				newroom->setRoomNum(i);
				newroom->InputUser(temp);
				newroom->InputUser(_user);
				
				temp->OnSend(&sendpacket, sendpacket.mPacketSize);
				sendpacket.mTurnCheck = false;
				_user->OnSend(&sendpacket, sendpacket.mPacketSize);
				
				SINGLETON(cMysql).GameStartLog(i, temp->getUserNUM(), _user->getUserNUM());
				
				mGameRoomCount++;
				break;
			}
		}
	}

	mCS_GameManager.UnLock();

}
void cGameManager::DeleteRoom(int _roomnum)
{
	mCS_GameManager.Lock();

	cGameRoom* temp = mGameArray[_roomnum];
	mGameArray[_roomnum] = NULL;
	mGameRoomCount--;
	delete temp;

	
	cout << _roomnum << " ¹æ Á¾·á" << endl;
	mCS_GameManager.UnLock();
}

void cGameManager::MatchingCancle(cUser* _user)
{
	mCS_GameManager.Lock();

	mIter = find(mMatchingUserlist.begin(), mMatchingUserlist.end(), _user);
	 mMatchingUserlist.erase(mIter);

	mCS_GameManager.UnLock();
}

cGameRoom* cGameManager::getRoomPtr(int _roomnum)
{
	return mGameArray[_roomnum];
}