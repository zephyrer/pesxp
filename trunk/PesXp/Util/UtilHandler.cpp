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
    // TODO �쳣����
    //
    if (_instance == NULL)
    {
        _instance = new CUtilHandler();
    }
    return _instance;
}

//
// �Ƿ�Ϊ��Ч�ַ�
//
bool CUtilHandler::IsValidChar(TCHAR ch)
{
    if( (ch >= 97) && (ch <= 122) ) // 26��Сд��ĸ
        return true;

    if( (ch >= 65) && (ch <= 90) )  // 26����д��ĸ
        return true;

    if((ch >= 48) && (ch <= 57))    // 0~9
        return true;

    if(ch == 95 || ch == 45 || ch == 46 || ch == 64 ) // _-.@
        return true;

    return false;
}

//
//EMAIL��Ч����֤
//
bool CUtilHandler::IsValidEmail(CString strEmail)
{
    if(strEmail.GetLength() < 5) //a@b.c
        return false;

    TCHAR ch = strEmail[0];

    int atCount     = 0;
    int atPos       = 0;
    int dotCount    = 0;

    for(int i=1; i<strEmail.GetLength(); i++) // 0�Ѿ��жϹ��ˣ���1��ʼ
    {
        ch = strEmail[i];
        if(IsValidChar(ch))
        {
            if(ch == 64) //"@"
            {
                atCount ++;
                atPos = i;
            }
            else if( (atCount>0) && (ch==46) ) // @���ź��"."��
                dotCount ++;
        }
        else
            return false;
    }

    //6.   ��β�������ַ���@�����ߡ�.��
    if( ch == 46 )
        return false;

    //2.   �������һ������ֻ��һ�����š�@�� 
    //3.   @������������һ�������������š�.��
    if( (atCount != 1) || (dotCount < 1) || (dotCount > 3) )
        return false;

    //5.   ��������֡�@.������.@
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