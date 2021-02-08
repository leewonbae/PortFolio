#include "cAcceptor.h"
cAcceptor::cAcceptor()
{

}
cAcceptor::~cAcceptor()
{

}
//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : SERVER �ʱ�ȭ 
//�ۼ��� : �̿���
//��  �� : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cAcceptor::InitServer()
{
	WSADATA wsa;

	WSAStartup(MAKEWORD(2, 2), &wsa);

	mListenSock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	bind(mListenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

	listen(mListenSock, SOMAXCONN);

	ShowStatus("INIT SERVER OK");
}
//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : Ŭ���̾�Ʈ accept
//�ۼ��� : �̿���
//��  �� : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cAcceptor::AcceptClient()
{
	ShowStatus("START ACCEPT CLIENT");
	 
	while (1)
	{
		SOCKADDR_IN clientaddr;
		int addlen = sizeof(clientaddr);
		SOCKET clientsock = accept(mListenSock, (SOCKADDR*)&clientaddr, &addlen);

		cSession* temp = SINGLETON(cSessionManager).MakeSession();
		if (temp != NULL)
		{
			 
			SINGLETON(cIOCPhandler).setCompletionPort(temp, clientsock);
			
			temp->setUserNum(mAutoUserNum);
			temp->setSock(clientsock);
			temp->OnRecv();
			mAutoUserNum++;
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : cACCEPT ���� ���
//�ۼ��� : �̿���
//��  �� : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cAcceptor::ShowStatus(const char* _show_msg)
{
	// �Էµ� �޼��� ���
	cout << "SHOW ACCEPTOR STATUS = [ " << _show_msg << " ] " << endl;
}