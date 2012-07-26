#pragma once

#include "UserItem.h"

typedef struct {
    CString szUserName;
    CString szPassword;
    CString szQQ;
    CString szMail;
} UserLoginInfo, *LPUserLoginInfo;

typedef struct {
    CString szMyAccount;
    CString szMyCredie;
    CString szWinCount;
    CString szEqualCount;
    CString szLoseCount;
    CString szWinPercentCount;
    CString szTotalRank;
    CString szGoalCount;
    CString szLostCount;
    CString szRedCount;
    CString szYellowCount;
    CString szNeedConfirmCount;
    CString szNotConfirmCount;
    CString szLeagueWinCount;
    CString szLeagueEqualCount;
    CString szLeagueLoseCount;
    CString szLeagueWinPercentCount;
    CString szLeagueRank;
    CString szLeagueMoney;
    CString szLeagueTheFirst;
    CString szLeagueTheEnd;
    CString szLeaguePlayerCount;
    CString szLeagueInfo;
    CString szLeagueSignCount;
} UserCenterInfo, *LPUserCenterInfo;

class CSyncHandler
{
public:
    CSyncHandler(void);
    ~CSyncHandler(void);
    
    //
    // 用户登录
    //
    static UINT32 Login(LPVOID params);
    //
    // 用户注册
    //
    static UINT32 Register(LPVOID params);
    //
    // 获取用户中心信息
    //
    static UINT32 RequestUserCenterInfo(LPVOID params);
    //
    // 获取用户信息
    //
    static UINT32 RequestUserInfo(LPVOID params);
    //
    // 获取联赛信息
    //
    static UINT32 RequestLeagueInfo(LPVOID params);
    //
    // 获取联赛详情
    //
    static UINT32 RequestLeagueDetail(LPVOID params);
    //
    // 获取荣誉殿堂信息
    //
    static UINT32 RequestHonorInfo(LPVOID params);
    //
    // 获取转会市场信息
    //
    static UINT32 RequestMarketInfo(LPVOID params);

private:
    CUserItem* m_pUserItem;
};
