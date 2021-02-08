#pragma once
#include "Resource.h"
#include "Protocol.h"
#include "cCriticalSection.h"
#include "cUser.h"

#define MAX_LOBBY_USER 10
class cLobbyManager : public cSingleton<cLobbyManager>
{
	friend class cSingleton<cLobbyManager>;
public:
	void InLobby(cUser* _user);
	void OutLobby(cUser* _user);

	void BroadChattingPacket(PACKET_HEAD* _sendpacket, cUser* _user);
	void BroadMovePacket(PACKET_HEAD* _sendpacket,cUser* _sendUser);


private:
	cLobbyManager();
	~cLobbyManager();
	
	cCriticalSection mCS_LobbyManager;
	vector<cUser*> mLobbyInUser;
	
};

