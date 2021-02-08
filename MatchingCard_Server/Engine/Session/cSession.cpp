#include "cSession.h"
cSession::cSession()
{

}
cSession::~cSession()
{

}
//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : Session Recv set
//작성자 : 이원배
//일  시 : 2020. 12. 01
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cSession::OnRecv()
{

	DWORD recvbytes, flag = 0;
	mRecvOverdata.mWorkFleg = WORKFLEG_RECV;

	ZeroMemory(&mRecvOverdata.mOverlapped, sizeof(mRecvOverdata.mOverlapped));
	ZeroMemory(mRecvBuf, BUFFER_SIZE);

	mRecvOverdata.mWsabuf.buf = mRecvBuf;
	mRecvOverdata.mWsabuf.len = BUFFER_SIZE;

	WSARecv(mSock, &mRecvOverdata.mWsabuf, 1, &recvbytes, &flag, &mRecvOverdata.mOverlapped, NULL);
}

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : Session Send set
//작성자 : 이원배
//일  시 : 2020. 12. 01
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cSession::OnSend(void* _packet, int _packetsize)
{
	DWORD sendbytes;
	mSendOverdata.mWorkFleg = WORKFLEG_SEND;

	ZeroMemory(&mSendOverdata.mOverlapped, sizeof(mSendOverdata.mOverlapped));
	ZeroMemory(mSendBuf, BUFFER_SIZE);

	memcpy(mSendBuf, _packet, _packetsize);

	mSendOverdata.mWsabuf.buf = mSendBuf;
	mSendOverdata.mWsabuf.len = BUFFER_SIZE;
	WSASend(mSock, &mSendOverdata.mWsabuf, 1, &sendbytes, 0, &mSendOverdata.mOverlapped, NULL);
}