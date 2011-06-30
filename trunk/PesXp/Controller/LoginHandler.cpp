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
bool CLoginHandler::doLogin(CString strUserName, CString strPassword)
{
    return true;
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