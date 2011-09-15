#pragma once

class CUserItem
{
public:
    ~CUserItem(void);
    
    static CUserItem* GetInstance();
    
    CString strUserName;
    CString strPassword;
    unsigned int uiCreateTime;
    CString strQQ;
    CString strMail;
    int iWinnerCount;
    int iEqualCount;
    int iLoserCount;
    int iWaiverCount;
    int iCredie;

    bool isLogin;

private:
    CUserItem(void);
    static CUserItem* _instance;
};
