#pragma once
#include "ResourceProtocol.h"
#include "cResourceManager.h"
enum COLOR {
	GREEN = 10,
	RED = 12,
	YELLOW = 14,
	WHITE = 15,
};

enum PACKET_PROTOCOL {
	 
	PROTOCOL_LOGIN_REQ = 1, PROTOCOL_LOGIN_ACK,
	PROTOCOL_NEWUSER_REQ, PROTOCOL_NEWUSER_ACK,
	PROTOCOL_ITEM_RESOURCE_REQ, PROTOCOL_ITEM_RESOURCE_ACK,
	
	PROTOCOL_BUY_ITEM_REQ,		PROTOCOL_BUY_ITEM_ACK,
	PROTOCOL_RECHARGE_MONEY_REQ,	PROTOCOL_RECHARGE_MONEY_ACK,
	PROTOCOL_RANKING_REQ,		PROTOCOL_RANKING_ACK,

	PROTOCOL_GAMESTART_REQ, PROTOCOL_GAMESTART_ACK,
	PROTOCOL_GAMESTART_CALCNE_REQ, PROTOCOL_GAMESTART_CANCLE_ACK,
	PROTOCOL_CHOICE_CARD_REQ, PROTOCOL_CHOICE_CARD_ACK,
	PROTOCOL_TURNCHANGE_REQ, PROTOCOL_TURNCHANGE_ACK,
	PROTOCOL_GAMERESULT_REQ, PROTOCOL_GAMERESULT_ACK,
	PROTOCOL_LOBBY_IN_REQ, PROTOCOL_LOBBY_IN_ACK,
	PROTOCOL_LOBBY_OUT_REQ, PROTOCOL_LOBBY_OUT_ACK,
	PROTOCOL_USER_MOVE_REQ, PROTOCOL_USER_MOVE_ACK,
	PROTOCOL_CHATTING_REQ, PROTOCOL_CHATTING_ACK,
};


class PACKET_HEAD {
public:
	int mCmd;
	int mPacketSize;
};

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : RankingResource
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_RANKING_REQ : public PACKET_HEAD
{
public:
	PACKET_RANKING_REQ()
	{
		mCmd = PROTOCOL_RANKING_REQ;
		mPacketSize = sizeof(PACKET_RANKING_REQ);
	}
 

};


class PACKET_RANKING_ACK : public PACKET_HEAD
{
public:
	PACKET_RANKING_ACK()
	{
		mCmd = PROTOCOL_RANKING_ACK;
		mPacketSize = sizeof(PACKET_RANKING_ACK);
	}
	RANKING_RESOURCE mRankingResource;
};

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : ITEM SHOP Recharge
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_RECHARGE_MONEY_REQ : public PACKET_HEAD
{
public:
	PACKET_RECHARGE_MONEY_REQ()
	{
		mCmd = PROTOCOL_RECHARGE_MONEY_REQ;
		mPacketSize = sizeof(PACKET_RECHARGE_MONEY_REQ);
	}
	int mReqMoney = 0;

};


class PACKET_RECHARGE_MONEY_ACK : public PACKET_HEAD
{
public:
	PACKET_RECHARGE_MONEY_ACK()
	{
		mCmd = PROTOCOL_RECHARGE_MONEY_ACK;
		mPacketSize = sizeof(PACKET_RECHARGE_MONEY_ACK);
	}
	int mAckMoney = 0;
};
//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : ITEM SHOP BUY
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_BUY_ITEM_REQ : public PACKET_HEAD
{
public:
	PACKET_BUY_ITEM_REQ()
	{
		mCmd = PROTOCOL_BUY_ITEM_REQ;
		mPacketSize = sizeof(PACKET_BUY_ITEM_REQ);
	}
	int mItemNum = 0;
	int mItemBuyCount = 0;
	int mItemAllPrice = 0;

	
};


class PACKET_BUY_ITEM_ACK : public PACKET_HEAD
{
public:
	PACKET_BUY_ITEM_ACK()
	{
		mCmd = PROTOCOL_BUY_ITEM_ACK;
		mPacketSize = sizeof(PACKET_BUY_ITEM_ACK);
	}
	bool mApproved = false;
	int mItemNum = 0;
	int mItemBuyCount = 0;
	int mItemAllPrice = 0;

};

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : ITEM RESOURCE
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_ITEM_RESOURCE_REQ : public PACKET_HEAD
{
public:
	PACKET_ITEM_RESOURCE_REQ()
	{
		mCmd = PROTOCOL_ITEM_RESOURCE_REQ;
		mPacketSize = sizeof(PACKET_ITEM_RESOURCE_REQ);
	}
	 
};


class PACKET_ITEM_RESOURCE_ACK : public PACKET_HEAD
{
public:
	PACKET_ITEM_RESOURCE_ACK()
	{
		mCmd = PROTOCOL_ITEM_RESOURCE_ACK;
		mPacketSize = sizeof(PACKET_ITEM_RESOURCE_ACK);
	}
	ITEM_RESOURCE mItemRecource;
	
};

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : newsuer
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------


class PACKET_NEWUSER_REQ : public PACKET_HEAD
{
public:
	PACKET_NEWUSER_REQ()
	{
		mCmd = PROTOCOL_NEWUSER_REQ;
		mPacketSize = sizeof(PACKET_NEWUSER_REQ);
	}
	char mNewID[100] = { 0, };
	int mNewPassword = 0;
};


class PACKET_NEWUSER_ACK : public PACKET_HEAD
{
public:
	PACKET_NEWUSER_ACK()
	{
		mCmd = PROTOCOL_NEWUSER_ACK;
		mPacketSize = sizeof(PACKET_NEWUSER_ACK);
	}
	bool mNewUser = false;
};

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : LOGIN
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_LOGIN_REQ : public PACKET_HEAD
{
public:
	PACKET_LOGIN_REQ()
	{
		mCmd = PROTOCOL_LOGIN_REQ;
		mPacketSize = sizeof(PACKET_LOGIN_REQ);
	}
	char mID[100] = { 0, };
	int mPassword = 0;
};


class PACKET_LOGIN_ACK : public PACKET_HEAD
{
public:
	PACKET_LOGIN_ACK()
	{
		mCmd = PROTOCOL_LOGIN_ACK;
		mPacketSize = sizeof(PACKET_LOGIN_ACK);
	}
	int mDataBaseNum = -1;
};

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : CHATTING
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------


class PACKET_CHATTING_REQ : public PACKET_HEAD
{
public:
	PACKET_CHATTING_REQ()
	{
		mCmd = PROTOCOL_CHATTING_REQ;
		mPacketSize = sizeof(PACKET_CHATTING_REQ);
	}
	int mToNum = 0;
	char mMsg[100] = { 0, };
};


class PACKET_CHATTING_ACK : public PACKET_HEAD
{
public:
	PACKET_CHATTING_ACK()
	{
		mCmd = PROTOCOL_CHATTING_ACK;
		mPacketSize = sizeof(PACKET_CHATTING_ACK);
	}
	int mFromNum = 0;
	char mMsg[100] = { 0, };
};

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : user moving
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_USER_MOVING_REQ : public PACKET_HEAD
{
public:
	PACKET_USER_MOVING_REQ()
	{
		mCmd = PROTOCOL_USER_MOVE_REQ;
		mPacketSize = sizeof(PACKET_USER_MOVING_REQ);
	}
	int mUserNum = 0;
	int mUser_X = 0;
	int mUser_Y = 0;
};


class PACKET_USER_MOVING_ACK : public PACKET_HEAD
{
public:
	PACKET_USER_MOVING_ACK()
	{
		mCmd = PROTOCOL_USER_MOVE_ACK;
		mPacketSize = sizeof(PACKET_USER_MOVING_ACK);
	}
	int mUserNum = 0;
	int mUser_X = 0;
	int mUser_Y = 0;
};

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : user Out
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_LOBBY_OUT_REQ : public PACKET_HEAD
{
public:
	PACKET_LOBBY_OUT_REQ()
	{
		mCmd = PROTOCOL_LOBBY_OUT_REQ;
		mPacketSize = sizeof(PACKET_LOBBY_OUT_REQ);
	}
	int mOutUserNum = 0;
};


class PACKET_LOBBY_OUT_ACK : public PACKET_HEAD
{
public:
	PACKET_LOBBY_OUT_ACK()
	{
		mCmd = PROTOCOL_LOBBY_OUT_ACK;
		mPacketSize = sizeof(PACKET_LOBBY_OUT_ACK);
	}
	int mOutUserNum = 0;
};
//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : user in
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_LOBBY_IN_REQ : public PACKET_HEAD
{
public:
	PACKET_LOBBY_IN_REQ()
	{
		mCmd = PROTOCOL_LOBBY_IN_REQ;
		mPacketSize = sizeof(PACKET_LOBBY_IN_REQ);
	}
	int mInUserNum = 0;
};


class PACKET_LOBBY_IN_ACK : public PACKET_HEAD
{
public:
	PACKET_LOBBY_IN_ACK()
	{
		mCmd = PROTOCOL_LOBBY_IN_ACK;
		mPacketSize = sizeof(PACKET_LOBBY_IN_ACK);
	}
	int mInUserNum = 0;
};

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : gameresult
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------


class PACKET_GAMERESULT_REQ : public PACKET_HEAD
{
public:
	PACKET_GAMERESULT_REQ()
	{
		mCmd = PROTOCOL_GAMERESULT_REQ;
		mPacketSize = sizeof(PACKET_GAMERESULT_REQ);
	}
	int mScore = 0;
};


class PACKET_GAMERESULT_ACK : public PACKET_HEAD
{
public:
	PACKET_GAMERESULT_ACK()
	{
		mCmd = PROTOCOL_GAMERESULT_ACK;
		mPacketSize = sizeof(PACKET_GAMERESULT_ACK);
	}
	//win = 1 , lose = -1 , draw 0
	int mResult = 0;

};

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : TURN 
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------


class PACKET_TURNCHANGE_REQ : public PACKET_HEAD
{
public:
	PACKET_TURNCHANGE_REQ()
	{
		mCmd = PROTOCOL_TURNCHANGE_REQ;
		mPacketSize = sizeof(PACKET_TURNCHANGE_REQ);
	}

};


class PACKET_TURNCHANGE_ACK : public PACKET_HEAD
{
public:
	PACKET_TURNCHANGE_ACK()
	{
		mCmd = PROTOCOL_TURNCHANGE_ACK;
		mPacketSize = sizeof(PACKET_TURNCHANGE_ACK);
	}

};


//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : ChoiceCard
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------


class PACKET_CHOICE_CARD_REQ : public PACKET_HEAD
{
public:
	PACKET_CHOICE_CARD_REQ()
	{
		mCmd = PROTOCOL_CHOICE_CARD_REQ;
		mPacketSize = sizeof(PACKET_CHOICE_CARD_REQ);
	}
	int mFlipCount = 0;
	int mMapCount = 0;
	int mCard_X = 0;
	int mCard_Y = 0;
};


class PACKET_CHOICE_CARD_ACK : public PACKET_HEAD
{
public:
	PACKET_CHOICE_CARD_ACK()
	{
		mCmd = PROTOCOL_CHOICE_CARD_ACK;
		mPacketSize = sizeof(PACKET_CHOICE_CARD_ACK);
	}
	int mEnermyFlipCount = 0;
	int mEnermyMapCount = 0;
	int mEnermyCard_X = 0;
	int mEnermyCard_Y = 0;
};


//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : gamestartCancle req
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_GAMESTART_CANCLE_REQ : public PACKET_HEAD
{
public:
	PACKET_GAMESTART_CANCLE_REQ()
	{
		mCmd = PROTOCOL_GAMESTART_CALCNE_REQ;
		mPacketSize = sizeof(PACKET_GAMESTART_CANCLE_REQ);
	}
};


class PACKET_GAMESTART_CANCLE_ACK : public PACKET_HEAD
{
public:
	PACKET_GAMESTART_CANCLE_ACK()
	{
		mCmd = PROTOCOL_GAMESTART_CANCLE_ACK;
		mPacketSize = sizeof(PACKET_GAMESTART_CANCLE_ACK);
	}

};


//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : gamestart req
//작성자 : 이원배
//일  시 : 2020. 12. 23
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_GAMESTART_REQ : public PACKET_HEAD
{
public:
	PACKET_GAMESTART_REQ()
	{
		mCmd = PROTOCOL_GAMESTART_REQ;
		mPacketSize = sizeof(PACKET_GAMESTART_REQ);
	}
};


class PACKET_GAMESTART_ACK : public PACKET_HEAD
{
public:
	PACKET_GAMESTART_ACK()
	{
		mCmd = PROTOCOL_GAMESTART_ACK;
		mPacketSize = sizeof(PACKET_GAMESTART_ACK);
	}
	bool mTurnCheck = true;
	// false = enermyturn 
	// true = myturn
};


 