#include "StdAfx.h"
#include "UtilHandler.h"

CUtilHandler* CUtilHandler::_instance = NULL;

CUtilHandler::CUtilHandler(void)
{
}

CUtilHandler::~CUtilHandler(void)
{
}

CUtilHandler* CUtilHandler::GetInstance()
{
    //
    // TODO 异常处理
    //
    if (_instance == NULL)
    {
        _instance = new CUtilHandler();
    }
    return _instance;
}

//
// 是否为有效字符
//
bool CUtilHandler::IsValidChar(TCHAR ch)
{
    if( (ch >= 97) && (ch <= 122) ) // 26个小写字母
        return true;

    if( (ch >= 65) && (ch <= 90) )  // 26个大写字母
        return true;

    if((ch >= 48) && (ch <= 57))    // 0~9
        return true;

    if(ch == 95 || ch == 45 || ch == 46 || ch == 64 ) // _-.@
        return true;

    return false;
}

//
//EMAIL有效性验证
//
bool CUtilHandler::IsValidEmail(CString strEmail)
{
    if(strEmail.GetLength() < 5) //a@b.c
        return false;

    TCHAR ch = strEmail[0];

    int atCount     = 0;
    int atPos       = 0;
    int dotCount    = 0;

    for(int i=1; i<strEmail.GetLength(); i++) // 0已经判断过了，从1开始
    {
        ch = strEmail[i];
        if(IsValidChar(ch))
        {
            if(ch == 64) //"@"
            {
                atCount ++;
                atPos = i;
            }
            else if( (atCount>0) && (ch==46) ) // @符号后的"."号
                dotCount ++;
        }
        else
            return false;
    }

    //6.   结尾不得是字符“@”或者“.”
    if( ch == 46 )
        return false;

    //2.   必须包含一个并且只有一个符号“@” 
    //3.   @后必须包含至少一个至多三个符号“.”
    if( (atCount != 1) || (dotCount < 1) || (dotCount > 3) )
        return false;

    //5.   不允许出现“@.”或者.@
    if( strEmail.Find(_T("@."))>0 || strEmail.Find(_T(".@"))>0 )
        return false;

    return true;
}

CString CUtilHandler::GetAppPath() 
{	
	CString  sPath; 
	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1) ,MAX_PATH); 
	sPath.ReleaseBuffer(); 
	 
	int nPos = sPath.ReverseFind('\\'); 
	sPath = sPath.Left(nPos); 
	return sPath; 
}