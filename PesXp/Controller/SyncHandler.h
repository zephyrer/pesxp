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

private:
    CUserItem* m_pUserItem;
};
