#pragma once

#include "UserItem.h"

class CLoginHandler
{
public:
    CLoginHandler(void);
    ~CLoginHandler(void);

    static AFX_THREADPROC doLogin(LPVOID param);//CString strUserName, CString strPassword);
    bool doRegister(
        CString strUserName,
        CString strPassword,
        CString strQQ,
        CString strMail);

private:
    CUserItem* m_pUserItem;
};
