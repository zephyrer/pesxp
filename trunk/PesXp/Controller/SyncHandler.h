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

    static AFX_THREADPROC Login(LPVOID params);
	static AFX_THREADPROC Register(LPVOID params);

private:
    CUserItem* m_pUserItem;
};
