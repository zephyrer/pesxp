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
// �����û���½��֤�߼�
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
	// ������������е�¼
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
	// �������������ע��
	//
	Sleep(5000);
    return 0;
}

//
// �����û�ע���߼�
//
/*bool CSyncHandler::doRegister(
                                CString strUserName,
                                CString strPassword,
                                CString strQQ,
                                CString strMail)
{
    return true;
}*/