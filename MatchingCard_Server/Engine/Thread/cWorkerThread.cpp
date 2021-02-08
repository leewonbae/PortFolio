#include "cWorkerThread.h"
DWORD WINAPI cWorkerThread::SwitchThread(LPVOID arg)
{

	cWorkerThread* thread = (cWorkerThread*)arg;
	thread->WorkerThread();
	return 0;

}
cWorkerThread::cWorkerThread()
{
	mMakeThreadEvent = CreateEvent(NULL, true, false, NULL);
}
cWorkerThread::~cWorkerThread()
{

}

//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : THREAD ����
//�ۼ��� : �̿���
//��  �� : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cWorkerThread::MakeThread()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	for (int i = 0;i < (int)si.dwNumberOfProcessors * 2 + 1;i++)
	{
		CreateThread(NULL, 0, SwitchThread, this, 0, NULL);
		WaitForSingleObject(mMakeThreadEvent, INFINITE);
	}

	cout << "SHOW WORKERTHREAD = [ MAKE THREAD OK ] " << endl;
}


//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : ���� �۾� ó�� �ð� ���
//�ۼ��� : �̿���
//��  �� : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
void cWorkerThread::ShowClock(clock_t _start, clock_t _end)
{
	clock_t result =  _end - _start;
	printf("SHOW WORKERTHREAD TIME = [ %d ms ]  \n\n", result);
}



//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : Ŭ���̾�Ʈ ���� �Ǿ��� ��, �۾� ó��
//�ۼ��� : �̿���
//��  �� : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
void cWorkerThread::ClientOut(cSession* _session)
{
	
	cUser* temp = (cUser*)_session;
	if (temp->getUserNUM() != -1)
	{
		SINGLETON(cMysql).ResourceUpdate(&temp->GetResource()->mItemResource, temp->getUserNUM());
		SINGLETON(cResourceManager).UpdateItemResource(&temp->GetResource()->mItemResource,temp->getUserNUM());
	}
	 
	cout << "client out" << endl;

}

//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : ���� �۾� ���� THREAD
//�ۼ��� : �̿���
//��  �� : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cWorkerThread::WorkerThread()
{
	SetEvent(mMakeThreadEvent);
	OVERDATA* ptr_overdata;
	cSession* ptr_session;
	PACKET_HEAD* recvpacket;
	clock_t start_clock, end_clock;
	SOCKADDR_IN client;
	
	while (1)
	{
		HANDLE hcp = SINGLETON(cIOCPhandler).getHandle();
		DWORD transbytes;
		int retval = GetQueuedCompletionStatus(hcp, &transbytes, (PULONG_PTR)&ptr_session, (LPOVERLAPPED*)&ptr_overdata, INFINITE);

		if (retval == 0 || transbytes == 0)
		{
			ClientOut(ptr_session);
			continue;
		}
		int len = sizeof(client);
		
		switch (ptr_overdata->mWorkFleg)
		{
		case WORKFLEG_RECV:
			start_clock = clock();
			getpeername(ptr_session->getSock(), (SOCKADDR*)&client,&len);
			
			cout << "ip = " << inet_ntoa(client.sin_addr);
			cout << "  port = " << ntohs(client.sin_port)<<"   ";

			recvpacket = (PACKET_HEAD*)ptr_overdata->mWsabuf.buf;
			ptr_session->Parsing(recvpacket);

			ptr_session->OnRecv();
			end_clock = clock();
			ShowClock(start_clock, end_clock);
			break;

		case WORKFLEG_SEND:
			break;
		}


	}



}