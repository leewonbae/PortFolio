#pragma once
#include "Resource.h"
#include "cIOCPhandler.h"
#include "cSessionManager.h"
//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : SERVER 초기화 및 ACCEPT
//작성자 : 이원배
//일  시 : 2020. 12. 01
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class cAcceptor : public cSingleton<cAcceptor>
{
	friend class cSingleton<cAcceptor>;
public:
	void InitServer();
	void AcceptClient();

private:
	cAcceptor();
	~cAcceptor();
	void ShowStatus(const char* _show_msg);
	SOCKET mListenSock;
	int mAutoUserNum = 0;
};

