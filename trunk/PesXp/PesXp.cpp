// PesXp.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "PesXp.h"
#include "LoginDlg.h"
#include "UserCenterDlg.h"
#include "UtilHandler.h"
#include "USkin.h"      // ���ؽ����

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPesXpApp

BEGIN_MESSAGE_MAP(CPesXpApp, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPesXpApp ����

CPesXpApp::CPesXpApp()
{
    // TODO: �ڴ˴���ӹ�����룬
    // ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPesXpApp ����

CPesXpApp theApp;


// CPesXpApp ��ʼ��

BOOL CPesXpApp::InitInstance()
{
    // ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
    // ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
    //����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
    // �����ؼ��ࡣ
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();

    AfxEnableControlContainer();

    // ��׼��ʼ��
    // ���δʹ����Щ���ܲ�ϣ����С
    // ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
    // ����Ҫ���ض���ʼ������
    // �������ڴ洢���õ�ע�����
    // TODO: Ӧ�ʵ��޸ĸ��ַ�����
    // �����޸�Ϊ��˾����֯��
    SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

    //
    // ����USkin�����
    // TODO USkin����ⲻ֧��unicode���� �����Ժ���������
    //
    CUtilHandler* pUtilHandler = CUtilHandler::GetInstance();
    CString appPath = pUtilHandler->GetAppPath();
    USkinInit(NULL, NULL, appPath + _T("\\skin\\pesxp.msstyles"));

    while (true)
    {
          CLoginDlg* pDlg = new CLoginDlg();
//          m_pMainWnd = pDlg;
          INT_PTR nResponse = pDlg->DoModal();
          if (nResponse == IDCANCEL)
          {
              break;
          }

        CUserCenterDlg* pUserCenterDlg = new CUserCenterDlg();
//        m_pMainWnd = pUserCenterDlg;
        pUserCenterDlg->DoModal();

        break;
    }

    // ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
    //  ����������Ӧ�ó������Ϣ�á�
    return FALSE;
}
