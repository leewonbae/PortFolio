#include "cLobbyManager.h"
cLobbyManager::cLobbyManager()
{

}
cLobbyManager::~cLobbyManager()
{

}

void cLobbyManager::InLobby(cUser* _user)
{
	PACKET_LOBBY_IN_ACK sendpacket;
	
	mCS_LobbyManager.Lock();
	
	mLobbyInUser.push_back(_user);
	if (mLobbyInUser.size() >= 2)
	{
		sendpacket.mInUserNum = _user->getUserNUM();
		for (int i = 0;i < mLobbyInUser.size();i++)
		{
			if (mLobbyInUser[i] == _user)
			{
				for (int k = 0;k < mLobbyInUser.size();k++)
				{
					PACKET_LOBBY_IN_ACK order_sendpacket;
					order_sendpacket.mInUserNum = mLobbyInUser[k]->getUserNUM();
					if(mLobbyInUser[k]==_user)
					{
						continue;
					}
					else
					{
						mLobbyInUser[i]->OnSend(&order_sendpacket, order_sendpacket.mPacketSize);
					}
				}
			}
			else
			{
				mLobbyInUser[i]->OnSend(&sendpacket, sendpacket.mPacketSize);
			}
		}
	}
	mCS_LobbyManager.UnLock();
	
}
void cLobbyManager::OutLobby(cUser* _user)
{
	PACKET_LOBBY_OUT_ACK sendpacket;
	mCS_LobbyManager.Lock();
	vector<cUser*>::iterator iter;
	iter = find(mLobbyInUser.begin(), mLobbyInUser.end(), _user);
	mLobbyInUser.erase(iter);
	sendpacket.mOutUserNum = _user->getUserNUM();
	if (!mLobbyInUser.empty())
	{
		for (int i = 0; i < mLobbyInUser.size();i++)
		{
			mLobbyInUser[i]->OnSend(&sendpacket, sendpacket.mPacketSize);
		}
	}
	mCS_LobbyManager.UnLock();
}
void cLobbyManager::BroadChattingPacket(PACKET_HEAD* _sendpacket, cUser* _sendUser)
{
	PACKET_CHATTING_REQ* recvpacket = (PACKET_CHATTING_REQ*)_sendpacket;
	PACKET_CHATTING_ACK sendpacket;
	sendpacket.mFromNum = recvpacket->mToNum;
	strcpy(sendpacket.mMsg, recvpacket->mMsg);

	mCS_LobbyManager.Lock();
	for (int i = 0; i < mLobbyInUser.size();i++)
	{
		if (mLobbyInUser[i] == _sendUser)
		{
			continue;
		}
		else
		{
			mLobbyInUser[i]->OnSend(&sendpacket, sendpacket.mPacketSize);
		}
	}
	mCS_LobbyManager.UnLock();
}
void cLobbyManager::BroadMovePacket(PACKET_HEAD* _sendpacket, cUser* _sendUser)
{
	PACKET_USER_MOVING_REQ* recvpacket = (PACKET_USER_MOVING_REQ*)_sendpacket;

	PACKET_USER_MOVING_ACK sendpacket;
	sendpacket.mUser_X = recvpacket->mUser_X;
	sendpacket.mUser_Y = recvpacket->mUser_Y;
	sendpacket.mUserNum = recvpacket->mUserNum;
	mCS_LobbyManager.Lock();
	
	for (int i = 0;i < mLobbyInUser.size();i++)
	{
		if (mLobbyInUser[i] == _sendUser)
		{
			continue;
		}
		else
		{
			mLobbyInUser[i]->OnSend(&sendpacket, sendpacket.mPacketSize);
		}
	}
	mCS_LobbyManager.UnLock();
}