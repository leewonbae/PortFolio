#pragma once
#include "Resource.h"
#include "cSession.h"

//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : IOCP HANDLER CLASS
//�ۼ��� : �̿���
//��  �� : 2020. 12. 01
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------


class cIOCPhandler : public cSingleton< cIOCPhandler>
{
	friend class cSingleton< cIOCPhandler>;
public:
	void InitHcp();
	void setCompletionPort(cSession* _session, SOCKET _clientsock);
	HANDLE getHandle() { return mHCP; }

private:
	cIOCPhandler();
	~cIOCPhandler();
	void ShowIOCPhandleStatus(const char* _msg);
	HANDLE mHCP;
};

