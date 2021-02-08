#include "cUser.h"
#include "cGameManager.h"
#include "cLobbyManager.h"
 
cUser::cUser()
{
	mMap.insert(make_pair(PROTOCOL_GAMESTART_REQ, &cUser::GameStartReq));
	mMap.insert(make_pair(PROTOCOL_LOGIN_REQ, &cUser::LoginReq));
	mMap.insert(make_pair(PROTOCOL_NEWUSER_REQ, &cUser::NewUserReq));
	mMap.insert(make_pair(PROTOCOL_ITEM_RESOURCE_REQ, &cUser::ItemResourceReq));
	mMap.insert(make_pair(PROTOCOL_BUY_ITEM_REQ, &cUser::BuyItemReq));
	mMap.insert(make_pair(PROTOCOL_RECHARGE_MONEY_REQ, &cUser::RechargeMoneyReq));
	mMap.insert(make_pair(PROTOCOL_RANKING_REQ, &cUser::RankingReq));
	mMap.insert(make_pair(PROTOCOL_GAMESTART_CALCNE_REQ, &cUser::GameStartCancleReq));
	mMap.insert(make_pair(PROTOCOL_TURNCHANGE_REQ, &cUser::TurnChangeReq));
	mMap.insert(make_pair(PROTOCOL_CHOICE_CARD_REQ, &cUser::ChoiceCardReq));
	mMap.insert(make_pair(PROTOCOL_GAMERESULT_REQ, &cUser::GameResult));
	mMap.insert(make_pair(PROTOCOL_CHATTING_REQ, &cUser::ChattingReq));
	mMap.insert(make_pair(PROTOCOL_USER_MOVE_REQ, &cUser::UserMoveReq));
	mMap.insert(make_pair(PROTOCOL_LOBBY_IN_REQ, &cUser::InLobbyReq));
	mMap.insert(make_pair(PROTOCOL_LOBBY_OUT_REQ, &cUser::OutLobbyReq));


}
cUser::~cUser()
{

}

void cUser::Parsing(PACKET_HEAD* _packet)
{
	fp	Temp;
	mIter = mMap.find(_packet->mCmd);

	if (mIter != mMap.end())
	{
		Temp = mIter->second;
		(this->*Temp)(_packet);
	}
}
 
void cUser::RankingReq(PACKET_HEAD* _packet)
{
	cout << "RankingReq" << endl;
	PACKET_RANKING_ACK sendpacket;

	memcpy(&sendpacket.mRankingResource,
		&SINGLETON(cResourceManager).GetRankResource(),
		sizeof(RANKING_RESOURCE));

	OnSend(&sendpacket, sendpacket.mPacketSize);

}

void cUser::BuyItemReq(PACKET_HEAD* _packet)
{
	cout << "BuyItemReq" << endl;
	PACKET_BUY_ITEM_REQ* recvpacket = (PACKET_BUY_ITEM_REQ*)_packet;
	PACKET_BUY_ITEM_ACK sendpacket;
	ITEM_RESOURCE* temp = &mGameResource.mItemResource;
	if (temp->mItemList[0] - recvpacket->mItemAllPrice < 0)
	{
		sendpacket.mApproved = false;
		OnSend(&sendpacket, sendpacket.mPacketSize);
	}
	else
	{
		sendpacket.mApproved = true;
		temp->mItemList[0] -= recvpacket->mItemAllPrice;
		temp->mItemList[recvpacket->mItemNum] += recvpacket->mItemBuyCount;

		sendpacket.mItemAllPrice = recvpacket->mItemAllPrice;
		sendpacket.mItemBuyCount = recvpacket->mItemBuyCount;
		sendpacket.mItemNum = recvpacket->mItemNum;
		OnSend(&sendpacket, sendpacket.mPacketSize);
	}
}

void cUser::RechargeMoneyReq(PACKET_HEAD* _packet)
{
	cout << "RechargeMoneyReq" << endl;
	PACKET_RECHARGE_MONEY_REQ* recvpacket = (PACKET_RECHARGE_MONEY_REQ*)_packet;
	PACKET_RECHARGE_MONEY_ACK sendpacket;

	ITEM_RESOURCE* temp = &mGameResource.mItemResource;
	temp->mItemList[0] += recvpacket->mReqMoney;

	sendpacket.mAckMoney = recvpacket->mReqMoney;

	OnSend(&sendpacket, sendpacket.mPacketSize);

}

void cUser::GameStartReq(PACKET_HEAD* _packet)
{
	cout << "gamestart req" << endl;
	SINGLETON(cGameManager).MatchingReq(this);
}
void cUser::GameStartCancleReq(PACKET_HEAD* _packet)
{
	cout << "gamestart cancle req" << endl;
	PACKET_GAMESTART_CANCLE_ACK sendpacket;
	SINGLETON(cGameManager).MatchingCancle(this);
	OnSend(&sendpacket, sendpacket.mPacketSize);
	
}
void cUser::TurnChangeReq(PACKET_HEAD* _packet)
{
	cout << "TurnChangeReq" << endl;
	PACKET_TURNCHANGE_ACK sendpacket;
	
	cGameRoom* temp = SINGLETON(cGameManager).getRoomPtr(mMyRoomNum);
	
	cUser* enermy = temp->getEnermyPtr(this);
	
	enermy->OnSend(&sendpacket, sendpacket.mPacketSize);

}

void cUser::ChoiceCardReq(PACKET_HEAD* _packet)
{
	cout << "ChoiceCardReq" << endl;
	PACKET_CHOICE_CARD_REQ* recvpacket = (PACKET_CHOICE_CARD_REQ*)_packet;
	PACKET_CHOICE_CARD_ACK sendpacket;
	sendpacket.mEnermyCard_X = recvpacket->mCard_X;
	sendpacket.mEnermyCard_Y = recvpacket->mCard_Y;
	
	cGameRoom* room = SINGLETON(cGameManager).getRoomPtr(mMyRoomNum);
	
	cUser* enermy = room->getEnermyPtr(this);
	
	enermy->OnSend(&sendpacket, sendpacket.mPacketSize);
}

void cUser::GameResult(PACKET_HEAD* _packet)
{
	cout << "GameResultReq" << endl;
	PACKET_GAMERESULT_REQ* recvpacket = (PACKET_GAMERESULT_REQ*)_packet;

	cGameRoom* temp =  SINGLETON(cGameManager).getRoomPtr(mMyRoomNum);

	if (temp->SendResult(recvpacket->mScore, this) == true)
	{
		
		SINGLETON(cGameManager).DeleteRoom(mMyRoomNum);
	}
}
void cUser::ChattingReq(PACKET_HEAD* _packet)
{
	cout << "ChattingReq" << endl;
	PACKET_CHATTING_REQ* recvpacket = (PACKET_CHATTING_REQ*)_packet;
	
	SINGLETON(cLobbyManager).BroadChattingPacket(_packet, this);
	SINGLETON(cMysql).GameMsgLog(recvpacket->mToNum, recvpacket->mMsg);
}
void cUser::UserMoveReq(PACKET_HEAD* _packet)
{
	cout << "UserMoveReq" << endl;
	SINGLETON(cLobbyManager).BroadMovePacket(_packet, this);
}
void cUser::InLobbyReq(PACKET_HEAD* _packet)
{
	cout << "InLobbyReq" << endl;
	SINGLETON(cLobbyManager).InLobby(this);
}
void cUser::OutLobbyReq(PACKET_HEAD* _packet)
{
	cout << "OutLobbyReq" << endl;
	SINGLETON(cLobbyManager).OutLobby(this);
}
void cUser::LoginReq(PACKET_HEAD* _packet)
{
	cout << "LoginReq" << endl;
	PACKET_LOGIN_REQ* recvpacket = (PACKET_LOGIN_REQ*)_packet;
	
	int num = SINGLETON(cMysql).LoginReq(recvpacket->mID, recvpacket->mPassword);
	if (num != -1)
	{
		this->setUserNum(num);
		cout << "SHOW LOGIN_USER_NUM = [ " << num << "  ] " << endl;
	}

	PACKET_LOGIN_ACK sendpacket;
	sendpacket.mDataBaseNum = num;
	OnSend(&sendpacket, sendpacket.mPacketSize);
}
void cUser::NewUserReq(PACKET_HEAD* _packet)
{
	cout << "NewUserReq" << endl;
	PACKET_NEWUSER_REQ* recvpacket = (PACKET_NEWUSER_REQ*)_packet;
	bool result = SINGLETON(cMysql).NewUserReq(recvpacket->mNewID, recvpacket->mNewPassword);

	PACKET_NEWUSER_ACK sendpacket;
	sendpacket.mNewUser = result;

	OnSend(&sendpacket, sendpacket.mPacketSize);

}

void cUser::ItemResourceReq(PACKET_HEAD* _packet)
{
	 cout << "ItemResourceReq" << endl;
	 PACKET_ITEM_RESOURCE_ACK sendpacket;
	 int usernum = this->getUserNUM();
	 memcpy(&mGameResource.mItemResource,
		 &SINGLETON(cResourceManager).GetItemResource(usernum),
		 sizeof(ITEM_RESOURCE));

	 if (mGameResource.mItemResource.mDBnum == -1)
	 {
		 memset(&mGameResource.mItemResource, 0, sizeof(ITEM_RESOURCE));
		 memcpy(&mGameResource.mItemResource,
			 &SINGLETON(cMysql).GetMysqlItemResource(usernum),
			 sizeof(ITEM_RESOURCE));
	 }

	 memcpy(&sendpacket.mItemRecource, &mGameResource.mItemResource, sizeof(ITEM_RESOURCE));
	 OnSend(&sendpacket, sendpacket.mPacketSize);

}
