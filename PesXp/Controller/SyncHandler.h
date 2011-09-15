#pragma once

#include "UserItem.h"

typedef struct {
    CString szUserName;
    CString szPassword;
    CString szQQ;
    CString szMail;
} UserLoginInfo, *LPUserLoginInfo;

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

private:
    CUserItem* m_pUserItem;
};
