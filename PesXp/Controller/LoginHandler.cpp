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
// �����û���½��֤�߼�
//
bool CLoginHandler::doLogin(CString strUserName, CString strPassword)
{
    return true;
}

//
// �����û�ע���߼�
//
bool CLoginHandler::doRegister(
                                CString strUserName,
                                CString strPassword,
                                CString strQQ,
                                CString strMail)
{
    return true;
}