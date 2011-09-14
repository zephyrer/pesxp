// View\WaitingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PesXp.h"
#include "WaitingDlg.h"
#include <process.h>


//
// �ȴ���ʾ�Ի����̺߳����ṹ��
//
typedef struct {
    CWaitingDlg *pWaitingDlg;   // ��Ϣ��ʾ�Ի���ָ��
    AFX_THREADPROC pThreadFun;  // ִ�к���ָ��
    LPVOID pThreadFunParams;
} WaitingDlgThreadStruct, *LPWaitingDlgThreadStruct;


// CWaitingDlg �Ի���

IMPLEMENT_DYNAMIC(CWaitingDlg, CDialog)

CWaitingDlg::CWaitingDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CWaitingDlg::IDD, pParent)
{
    m_pParentWnd = pParent;
}

CWaitingDlg::~CWaitingDlg()
{
}

void CWaitingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_WAITING_GIF, m_gifWaiting);
    DDX_Control(pDX, IDC_WAITING_MESSAGE_TEXT, m_textWaiting);
}


BEGIN_MESSAGE_MAP(CWaitingDlg, CDialog)
END_MESSAGE_MAP()


// CWaitingDlg ��Ϣ�������

BOOL CWaitingDlg::OnInitDialog()
{
    if (!m_pParentWnd)
    {
        CDialog::OnCancel();
        return FALSE;
    }

    CDialog::OnInitDialog();

    SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);HINSTANCE hInst = LoadLibrary("User32.DLL");
    if(hInst)
    {
        typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD);
        MYFUNC fun = NULL;
        //ȡ��SetLayeredWindowAttributes����ָ��
        fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
        if(fun) {
            fun(this->GetSafeHwnd(), RGB(240,240,240), 128, LWA_COLORKEY);
        }

        FreeLibrary(hInst);
    }

    RECT rect;
    m_pParentWnd->GetWindowRect(&rect);
    SetWindowPos(NULL, rect.left + 0.5, rect.top + 3.5, rect.right - rect.left, rect.bottom - rect.top - 3, SWP_NOZORDER | SWP_SHOWWINDOW);

    m_gifWaiting.SetWindowPos(NULL, (rect.right - rect.left) / 2 - 50, (rect.bottom - rect.top) / 2 - 10, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
    m_textWaiting.SetWindowPos(NULL, (rect.right - rect.left) / 2 - 10, (rect.bottom - rect.top) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);

    if (m_gifWaiting.Load(MAKEINTRESOURCE(IDR_GIF_WAITING),_T("GIF")))
        m_gifWaiting.Draw();

    m_textWaiting.SetWindowText(m_szMessage);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CWaitingDlg::OnOK()
{
    //
    // ���λس���
    //
    return;

    //CDialog::OnOK();
}

void CWaitingDlg::OnCancel()
{
    //
    // ����ESC��
    //
    return;

    //CDialog::OnCancel();
}

//
// ��̨�����߳�
//
AFX_THREADPROC backgroundThreadFun(LPWaitingDlgThreadStruct param)
{

    AFX_THREADPROC workFunc = param->pThreadFun;
    LPVOID params           = param->pThreadFunParams;

    UINT threadRet          = workFunc(params);

    //
    // ִ����Ϲرյȴ���ʾ��Ϣ
    //
    param->pWaitingDlg->EndWaitingDlg();
    return 0;
}

void CWaitingDlg::PerformSelectorAndBeginWaitingDlg(LPCTSTR szMsg, LPVOID selector, LPVOID params)
{
    WaitingDlgThreadStruct wts;
    wts.pWaitingDlg         = this;
    wts.pThreadFun          = (AFX_THREADPROC)selector;
    wts.pThreadFunParams    = params;
    //
    // ������ʾ����
    //
    m_szMessage             = szMsg;
    //
    // �����̴߳�����
    //
    AfxBeginThread((AFX_THREADPROC)backgroundThreadFun, &wts);
    //
    // ��ʾ�ȴ���ʾ��Ϣ
    //
    this->DoModal();
}

void CWaitingDlg::EndWaitingDlg()
{
    //
    // �ͷ�GIF��Դ
    //
    m_gifWaiting.UnLoad();
    //
    // �ر���ʾ�Ի���
    //
    this->EndDialog(0);
}