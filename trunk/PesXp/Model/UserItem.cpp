#include "StdAfx.h"
#include "UserItem.h"

CUserItem* 	CUserItem::_instance = NULL;

CUserItem::CUserItem(void)
    :strUserName(_T(""))
    ,strPassword(_T(""))
    ,strQQ(_T(""))
    ,strMail(_T(""))
{
    isLogin = false;
}

CUserItem::~CUserItem(void)
{
}

CUserItem* 	CUserItem::GetInstance()
{
    if (_instance == NULL)
    {
        _instance = new CUserItem();
    }
    return _instance;
}
