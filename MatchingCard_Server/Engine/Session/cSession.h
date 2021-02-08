#pragma once
#include "Resource.h"
#include "Protocol.h"

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : Session class 
//작성자 : 이원배
//일  시 : 2020. 12. 01
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class cSession
{
public:
	cSession();
	~cSession();


	void setUserNum(int _num) { mUserNum = _num; }
	int getUserNUM() { return mUserNum; }

	void setKey(int _key) { mKey = _key; }
	int getKey() { return mKey; }
	
	
	void setSock(SOCKET _sock) { mSock = _sock; }
	SOCKET getSock() { return mSock; }


	void OnRecv();
	void OnSend(void* _packet, int _packetsize);


	virtual void Parsing(PACKET_HEAD* _packet) = 0;
private:
	OVERDATA mRecvOverdata, mSendOverdata;
	SOCKET mSock;
	char mRecvBuf[BUFFER_SIZE] = { 0, };
	char mSendBuf[BUFFER_SIZE] = { 0, };

	int mUserNum = -1;
	
	int mKey = -1;
};

