#pragma once
#include "Resource.h"
#include "cIOCPhandler.h"
#include "cUser.h"
#include "cResourceManager.h"
#include "cMysql.h"
//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : WORKERTHREAD ���� �� �ʱ�ȭ
//�ۼ��� : �̿���
//��  �� : 2020. 12.23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------


class cWorkerThread : public cSingleton< cWorkerThread>
{
	friend class cSingleton< cWorkerThread>;
public:

	void MakeThread();
	void WorkerThread();
	void ClientOut(cSession* _session);
	void ShowClock(clock_t _start, clock_t _end);
	static DWORD WINAPI SwitchThread(LPVOID arg);

private:
	cWorkerThread();
	~cWorkerThread();

	HANDLE mMakeThreadEvent;
};

