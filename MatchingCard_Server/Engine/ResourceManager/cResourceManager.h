#pragma once
#include "Resource.h"
#include "Protocol.h"
#include "cCriticalSection.h"



class cResourceManager : cSingleton<cResourceManager>
{
	friend class cSingleton<cResourceManager>;
public:
	
	ITEM_RESOURCE GetItemResource(int _key);
	void UpdateItemResource(ITEM_RESOURCE* _resource, int _key);

	RANKING_RESOURCE GetRankResource();
	void UpdateRanking(int _usernum, int _score);
	

private:
	cResourceManager();
	~cResourceManager();

	cCriticalSection mCS_ItemResource;
	cCriticalSection mCS_RankingResource;

	list<ITEM_RESOURCE> mItemResourceList;
	map<int, list<ITEM_RESOURCE>::iterator> mItemMap;

	vector<pair<int, int>> mRankingList;
	// first usernum, second score;

};

