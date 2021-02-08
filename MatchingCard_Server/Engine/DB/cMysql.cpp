#include "cMysql.h"
cMysql::cMysql()
{
	 
}
cMysql::~cMysql()
{
	 
}


void cMysql::InitMysql()
{
	for (int i = 0;i < 8;i++)
	{
		
		MYSQL* temp = new MYSQL;
		mysql_init(temp);
		MYSQL* Connections= mysql_real_connect(temp, DB_HOST, DB_ID, DB_PASSWORD, DB_NAME, 3306, NULL, 0);
		 
		if (Connections == NULL)
		{
			ShowError(temp);
		}
		else
		{
			mConnectionPool.push(temp);
		}
		
	}

	cout << "SHOW MYSQL SET OK " << endl;
	 
}
void cMysql::ShowError(MYSQL* _connections)
{
	cout << "SHOW DATABASES ERROR = " << mysql_error(_connections) << endl;
}



MYSQL* cMysql::getConnection()
{
	MYSQL* temp = NULL;
	mCS_Mysql.Lock();
	if (mConnectionPool.empty())
	{
		temp = NULL;
	}
	else
	{
		temp = mConnectionPool.front();
		mConnectionPool.pop();
	}
	

	mCS_Mysql.UnLock();

	return temp;

}

void cMysql::RecycleConnections(MYSQL* _connections)
{
	mCS_Mysql.Lock();
	mConnectionPool.push(_connections);
	mCS_Mysql.UnLock();
}

void  cMysql::GameStartLog(int _roomnum, int _usernum1, int _usernum2)
{
	
	char sql_start[256] = { 0, };
	MYSQL* connection = getConnection();
	if (connection == NULL)
	{
		cout << "connections error" << endl;
		return;
	}
	 
	sprintf(sql_start, "CALL START_PROCEDURE(%d,%d,%d)", _roomnum, _usernum1, _usernum2);
	 

	int query_state = mysql_query(connection, sql_start);
	if (query_state != 0)
	{
		ShowError(connection);
	}
	else
	{
		cout << "SHOW SAVE LOG OK" << endl;

	}

	MYSQL_RES* res = mysql_store_result(connection);
	mysql_free_result(res);

	RecycleConnections(connection);

	
	//CHATTING_PROCEDURE
	
}
void cMysql::GameMsgLog(int _usernum, char* _msg)
{
	char sql_chatting[256] = { 0, };
	MYSQL* connection = getConnection();
	if (connection != NULL)
	{
		sprintf(sql_chatting, "CALL CHATTING_PROCEDURE(%d,'%s')", _usernum, _msg);
		int query_state = mysql_query(connection, sql_chatting);
		if (query_state != 0)
		{
			ShowError(connection);
		}
		else
		{
			cout << "SHOW SAVE LOG OK" << endl;
		} 
	}
	MYSQL_RES* res = mysql_store_result(connection);
	mysql_free_result(res);

	RecycleConnections(connection);
}
bool cMysql::NewUserReq(char* _id, int _password)
{
	char sql_newuser[256] = { 0, };
	bool result = false;
	MYSQL* connection = getConnection();
	if (connection == NULL)
	{
		cout << "connections error" << endl;
		
		return false;
	}
	 
	mCS_Mysql.Lock();
	 
	
	sprintf(sql_newuser, "CALL CHECK_PROCEDURE('%s',%d)", _id, _password);
	int query_state1 = mysql_query(connection, sql_newuser);
	MYSQL_RES* res1 = mysql_store_result(connection);
	if (query_state1 != 0)
	{
		ShowError(connection);
	}
	else
	{
		if (res1->row_count ==0)
		{
			
			MYSQL* connection1 = getConnection();
			memset(sql_newuser, 0, 256);
			sprintf(sql_newuser, "CALL NEWUSER_PROCEDURE('%s',%d)", _id, _password);
			int query_state2 = mysql_query(connection1, sql_newuser);
			if (query_state2 != 0)
			{
				ShowError(connection1);
			}
			else
			{
				result = true;
			}
			MYSQL_RES* res2 = mysql_store_result(connection1);
			mysql_free_result(res2);
			RecycleConnections(connection1);

		}
		
	}
	 

	mysql_free_result(res1);
	RecycleConnections(connection);

	mCS_Mysql.UnLock();
	
	return result;
}

 
int cMysql::LoginReq(char* _id, int _password)
{
	int result =-1;
	char sql_login[256] = { 0, };
	MYSQL* connection = getConnection();
	if (connection == NULL)
	{
		cout << "connections error" << endl;
		return result;
	}

	sprintf(sql_login, "CALL LOGIN_PROCEDURE('%s',%d)", _id, _password);


	int query_state = mysql_query(connection, sql_login);
	MYSQL_RES* res = mysql_store_result(connection);
	if (query_state != 0)
	{
		ShowError(connection);
	}
	else
	{
		MYSQL_ROW mysql_row;
		while ((mysql_row = mysql_fetch_row(res)) != NULL)
		{
			if (strcmp(_id, mysql_row[1]) == 0 && stoi(mysql_row[2]) == _password)
			{
				result = stoi(mysql_row[0]);
				break;
			}
		}
	}
	
	mysql_free_result(res);

	RecycleConnections(connection);

	return result;
}
void  cMysql::GameOverLog(int _roomnum, int _winuser, int _loseuser, int _drawusers)
{
	
	char sql_end[256] = { 0, };
	MYSQL* connection = getConnection();
	if (connection == NULL)
	{
		cout << "connections error" << endl;
		return;
	}
	if (_drawusers == 0)
	{
		sprintf(sql_end, "CALL END_PROCEDURE(%d,%d,%d)", _roomnum, 0, 0);
	}
	else
	{
		sprintf(sql_end, "CALL END_PROCEDURE(%d,%d,%d)", _roomnum, _winuser, _loseuser);
		
	}

	int query_state = mysql_query(connection, sql_end);
	if (query_state != 0)
	{
		ShowError(connection);
	}
	else
	{
		cout << "SHOW SAVE LOG OK" << endl;

	}

	MYSQL_RES* res = mysql_store_result(connection);
	mysql_free_result(res);

	RecycleConnections(connection);

}
// 성공적으로 반환이 되었다면, mdbnum == _key 값이랑 같을 것이다.
ITEM_RESOURCE cMysql::GetMysqlItemResource(int _key)
{
	ITEM_RESOURCE result;

	MYSQL* connection = getConnection();
	char sql_itemresource[256] = { 0, };

	sprintf(sql_itemresource, "CALL GET_ITEM_PROCEDURE(%d)", _key);
	int query_state = mysql_query(connection, sql_itemresource);
	if (query_state != 0)
	{
		ShowError(connection);
		RecycleConnections(connection);
		
	}
	else
	{
		MYSQL_RES* mysql_res = mysql_store_result(connection);
		MYSQL_ROW mysql_row ;
		result.mDBnum = _key;
		while ((mysql_row = mysql_fetch_row(mysql_res)) != NULL)
		{
			result.mItemList[stoi(mysql_row[1])] = stoi(mysql_row[2]);
			result.mItemPrice[stoi(mysql_row[1])] = stoi(mysql_row[3]);
		}
	
		mysql_free_result(mysql_res);
	
	}
	
	RecycleConnections(connection);
	
	return result;

}
bool cMysql::ResourceUpdate(ITEM_RESOURCE* _item_resource, int _key)
{
	bool result = true;

	MYSQL* connection = getConnection();
	
	for (int i = 0;i < MAX_ITEM_COUNT;i++)
	{
		char sql_update[256] = { 0, };

		sprintf(sql_update, "UPDATE TBL_ITEMLIST SET ITEM_COUNT = %d WHERE USER_NUM = %d and ITEM_NUM = %d"
			, _item_resource->mItemList[i], _key, i);
		int query_state = mysql_query(connection, sql_update);
		if (query_state != 0)
		{
			ShowError(connection);
			result = false;
			break;
		}
	}
	
	MYSQL_RES* res = mysql_store_result(connection);
	mysql_free_result(res);

	RecycleConnections(connection);

	return result;
}

RANKING_RESOURCE cMysql::GetRankingScore()
{
	RANKING_RESOURCE ranking;
	MYSQL* connection = getConnection();
	char sql_ranking[256] = { 0, };

	sprintf(sql_ranking, "CALL RANKING_PROCEDURE(%d);",MAX_RANKING_SIZE);
	int query_state = mysql_query(connection, sql_ranking);
	if (query_state != 0)
	{
		ShowError(connection);
	} 
	else
	{
		MYSQL_RES* res = mysql_store_result(connection);
		MYSQL_ROW row;
		int count = 0;
		ranking.mApproved = true;
		while ((row = mysql_fetch_row(res)) != NULL)
		{
			ranking.mTopUserDBnum[count] = stoi(row[0]);
			ranking.mTopUserScore[count++] = stoi(row[1]);
		}

		mysql_free_result(res);
	}

	RecycleConnections(connection);

	return ranking;
}