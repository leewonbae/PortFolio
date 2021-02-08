#pragma once
#include "Resource.h"
#include "cSession.h"

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : IOCP HANDLER CLASS
//작성자 : 이원배
//일  시 : 2020. 12. 01
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

