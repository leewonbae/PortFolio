#pragma once
#include "Resource.h"
#include "cCriticalSection.h"
#include "Protocol.h"

class cMysql : public cSingleton<cMysql>
{
	friend class cSingleton<cMysql>;
public:
	MYSQL* getConnection();

	void InitMysql();
	// call start_procedure
	void GameStartLog(int _roomnum,int _usernum1, int _usernum2);
	// call end_procedure
	void GameOverLog(int _roomnum,int _winuser, int _loseuser, int _drawusers);
	// call msg_procedure
	void GameMsgLog(int _usernum,char* _msg);

	// resister user db
	bool NewUserReq(char* _id, int _password);

	// check db userinfo
	int LoginReq(char* _id, int _password);

	//아이템 리소스 가져오기
	ITEM_RESOURCE GetMysqlItemResource(int _key);

	//리소스 item_resource update
	bool ResourceUpdate(ITEM_RESOURCE* _item_resource, int _key);

	//랭킹 가져오기
	RANKING_RESOURCE GetRankingScore();

	void RecycleConnections(MYSQL* _connections);
	void ShowError(MYSQL* _connections);

private:
	cMysql();
	~cMysql();

	cCriticalSection mCS_Mysql;
	queue<MYSQL*> mConnectionPool;
	 
};

