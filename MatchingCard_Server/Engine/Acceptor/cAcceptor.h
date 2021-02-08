#pragma once
#include "Resource.h"
#include "cIOCPhandler.h"
#include "cSessionManager.h"
//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : SERVER �ʱ�ȭ �� ACCEPT
//�ۼ��� : �̿���
//��  �� : 2020. 12. 01
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

