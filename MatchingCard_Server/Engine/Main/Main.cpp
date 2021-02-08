#include "Resource.h"
#include "cAcceptor.h"
#include "cIOCPhandler.h"
#include "cWorkerThread.h"
#include "cMysql.h"
int main()
{
	SINGLETON(cAcceptor).InitServer();
	SINGLETON(cIOCPhandler).InitHcp();
	SINGLETON(cWorkerThread).MakeThread();
	SINGLETON(cMysql).InitMysql();
	SINGLETON(cAcceptor).AcceptClient();
	return 0;
}