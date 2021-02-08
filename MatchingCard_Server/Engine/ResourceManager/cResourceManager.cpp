#include "cResourceManager.h"
#include "cMysql.h"
cResourceManager::cResourceManager()
{

}
cResourceManager::~cResourceManager()
{

}
ITEM_RESOURCE cResourceManager::GetItemResource(int _key)
{
	map<int, list<ITEM_RESOURCE>::iterator>::iterator iter;
	ITEM_RESOURCE result;
	iter = mItemMap.find(_key);
	
	if (iter == mItemMap.end())
	{
		// 해당하는 메모리가 없다. 
		 
	}
	else
	{
		mCS_ItemResource.Lock();

		
		
		list<ITEM_RESOURCE>::iterator temp_iter = iter->second;
		memcpy(&result, &temp_iter, sizeof(ITEM_RESOURCE));

		result.mDBnum = _key;
		
		mItemResourceList.erase(temp_iter);
		mItemMap.erase(_key);

		mCS_ItemResource.UnLock();


		
	}

	return result;

}
void cResourceManager::UpdateItemResource(ITEM_RESOURCE* _resource, int _key)
{
	// 맨앞에 갱신
	mCS_ItemResource.Lock();
	
	ITEM_RESOURCE input_resource;
	memcpy(&input_resource, _resource, sizeof(ITEM_RESOURCE));
	mItemResourceList.push_front(input_resource);
	mItemMap.insert(make_pair(_key, mItemResourceList.begin()));

	
	mCS_ItemResource.UnLock();
}

RANKING_RESOURCE cResourceManager::GetRankResource()
{
	RANKING_RESOURCE result;
	result.mApproved = true;
	mCS_RankingResource.Lock();

	if (mRankingList.empty())
	{
		memcpy(&result, &SINGLETON(cMysql).GetRankingScore(), sizeof(RANKING_RESOURCE));
		for (int i = 0;i < MAX_RANKING_SIZE;i++)
		{
			mRankingList.push_back(make_pair(result.mTopUserDBnum[i], result.mTopUserScore[i]) );
		}
	}
	else
	{
		for (int i = 0;i < MAX_RANKING_SIZE;i++)
		{
			result.mTopUserDBnum[i] = mRankingList[i].first;
			result.mTopUserScore[i] = mRankingList[i].second;
			 
		}
	}

	mCS_RankingResource.UnLock();



	return result;
}

void cResourceManager::UpdateRanking(int _usernum, int _score)
{
	mCS_RankingResource.Lock();

	bool usercheck = false;
	vector<pair<int, int>>::iterator iter;
	
	iter = mRankingList.begin();
	for (int i = 0;i < MAX_RANKING_SIZE;i++)
	{
		if (mRankingList[i].first == _usernum)
		{
			mRankingList.erase(iter);
			usercheck = true;
			break;
		}
		iter++;
	}

	iter = mRankingList.begin();
	pair<int, int> temp = make_pair(_usernum, _score);
	for (int i = 0; i < MAX_RANKING_SIZE;i++)
	{
		if (_score >= mRankingList[i].second)
		{
			mRankingList.insert(iter, temp);
			break;
		}
		else
		{
			continue;
		}
	}

	mCS_RankingResource.UnLock();
}