#include "StdAfx.h"
#include "SyncHandler.h"

CSyncHandler::CSyncHandler(void)
{
    m_pUserItem = CUserItem::GetInstance();
}

CSyncHandler::~CSyncHandler(void)
{
}

//
// 具体用户登陆验证逻辑
//
AFX_THREADPROC CSyncHandler::Login(LPVOID params)
{
	LPUserLoginInfo pUserInfo = (LPUserLoginInfo)params;
	
	TRACE(_T("xxxxxxxxxxxxxxx\n"));
	TRACE(pUserInfo->szUserName + _T("\n"));
	TRACE(_T("xxxxxxxxxxxxxxx\n"));
	TRACE(pUserInfo->szPassword + _T("\n"));
	TRACE(_T("xxxxxxxxxxxxxxx\n"));
	//
	// 请求服务器进行登录
	//
    Sleep(5000);
    return 0;
}

AFX_THREADPROC CSyncHandler::Register(LPVOID params)
{
	LPUserLoginInfo pUserInfo = (LPUserLoginInfo)params;
	
	TRACE(pUserInfo->szUserName);
	TRACE(pUserInfo->szPassword);
	TRACE(pUserInfo->szQQ);
	TRACE(pUserInfo->szMail);
	//
	// 请求服务器进行注册
	//
	Sleep(5000);
    return 0;
}

//
// 具体用户注册逻辑
//
/*bool CSyncHandler::doRegister(
                                CString strUserName,
                                CString strPassword,
                                CString strQQ,
                                CString strMail)
{
    return true;
}*/