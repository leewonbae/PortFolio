#pragma once
#include <iostream>
#include <WinSock2.h>
#include <string>
#include <map>
#include <time.h>
#include <vector>
#include "cSingleton.h"
#include <mysql.h>
#include <queue>
#include <list>
#pragma comment (lib,"ws2_32.lib")
#pragma comment (lib,"libmysql.lib")


#define BUFFER_SIZE 1024
#define PORT 7296

#define WORKFLEG_SEND 1
#define WORKFLEG_RECV 2

#define DB_ID "root"
#define DB_HOST "127.0.0.1"
#define DB_NAME "SCEMA_MATCHINGCARD"
#define DB_PASSWORD "814dnjsqo*"
#define DB_PORT 3306

#define MAX_SESSION_COUNT 50
#define MAX_CONNECTIONS_COUNT 8
#define MAX_ROOM_COUNT 20

#define MAX_SAVE_RESOURCE_SIZE 10

using namespace std;

struct OVERDATA {
	OVERLAPPED mOverlapped;
	WSABUF mWsabuf;
	int mWorkFleg;
};




