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
AFX_THREADPROC CLoginHandler::doLogin(LPVOID param)//CString strUserName, CString strPassword)
{
    Sleep(5000);
    return 0;
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