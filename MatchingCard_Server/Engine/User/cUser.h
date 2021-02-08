#pragma once
#include "Resource.h"
#include "cSession.h"
#include "cMysql.h"
 

class cUser : public cSession
{
public:
	cUser();
	~cUser();

	

	GAME_RESOURCE* GetResource() { return& mGameResource; }

	void setRoomNum(int _roomnum) { mMyRoomNum = _roomnum; }
	int getRoomNum() { return mMyRoomNum; }
	void Parsing(PACKET_HEAD* _packet);

	typedef void (cUser::* fp)(PACKET_HEAD* _packet);

private:
	map<int, fp> mMap;
	map<int, fp>::iterator mIter;
	
	void GameStartReq(PACKET_HEAD* _packet);
	void NewUserReq(PACKET_HEAD* _packet);
	void LoginReq(PACKET_HEAD* _packet);
	void ItemResourceReq(PACKET_HEAD* _packet);
	void BuyItemReq(PACKET_HEAD* _packet);
	void RechargeMoneyReq(PACKET_HEAD* _packet);
	void RankingReq(PACKET_HEAD* _packet);
	void GameStartCancleReq(PACKET_HEAD* _packet);
	void TurnChangeReq(PACKET_HEAD* _packet);
	void ChoiceCardReq(PACKET_HEAD* _packet);
	void GameResult(PACKET_HEAD* _packet);
	void ChattingReq(PACKET_HEAD* _packet);
	void UserMoveReq(PACKET_HEAD* _packet);
	void InLobbyReq(PACKET_HEAD* _packet);
	void OutLobbyReq(PACKET_HEAD* _packet);

	
	int mMyRoomNum = 0;
	char mMyUserID[10]{ 0, };

	GAME_RESOURCE mGameResource;
};

