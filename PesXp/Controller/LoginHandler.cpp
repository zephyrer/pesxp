#include "StdAfx.h"
#include "LoginHandler.h"

CLoginHandler::CLoginHandler(void)
{
    m_pUserItem = CUserItem::GetInstance();
}

CLoginHandler::~CLoginHandler(void)
{
}

//
// 具体用户登陆验证逻辑
//
AFX_THREADPROC CLoginHandler::doLogin(LPVOID param)//CString strUserName, CString strPassword)
{
    Sleep(5000);
    return 0;
}

//
// 具体用户注册逻辑
//
bool CLoginHandler::doRegister(
                                CString strUserName,
                                CString strPassword,
                                CString strQQ,
                                CString strMail)
{
    return true;
}