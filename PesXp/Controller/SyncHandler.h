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
    // �û���¼
    //
    static UINT32 Login(LPVOID params);
    //
    // �û�ע��
    //
    static UINT32 Register(LPVOID params);
    //
    // ��ȡ�û�������Ϣ
    //
    static UINT32 RequestUserCenterInfo(LPVOID params);
    //
    // ��ȡ�û���Ϣ
    //
    static UINT32 RequestUserInfo(LPVOID params);
    //
    // ��ȡ������Ϣ
    //
    static UINT32 RequestLeagueInfo(LPVOID params);
    //
    // ��ȡ��������
    //
    static UINT32 RequestLeagueDetail(LPVOID params);
    //
    // ��ȡ����������Ϣ
    //
    static UINT32 RequestHonorInfo(LPVOID params);
    //
    // ��ȡת���г���Ϣ
    //
    static UINT32 RequestMarketInfo(LPVOID params);

private:
    CUserItem* m_pUserItem;
};
