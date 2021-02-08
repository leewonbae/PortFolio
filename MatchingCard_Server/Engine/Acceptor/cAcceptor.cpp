#include "cAcceptor.h"
cAcceptor::cAcceptor()
{

}
cAcceptor::~cAcceptor()
{

}
//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : SERVER 초기화 
//작성자 : 이원배
//일  시 : 2020. 12. 23
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
//목  적 : 클라이언트 accept
//작성자 : 이원배
//일  시 : 2020. 12. 23
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
//목  적 : cACCEPT 상태 출력
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cAcceptor::ShowStatus(const char* _show_msg)
{
	// 입력된 메세지 출력
	cout << "SHOW ACCEPTOR STATUS = [ " << _show_msg << " ] " << endl;
}