// View\WaitingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "WaitingDlg.h"
#include <process.h>


//
// 等待提示对话框线程函数结构体
//
typedef struct {
    CWaitingDlg *pWaitingDlg;   // 信息提示对话框指针
    AFX_THREADPROC pThreadFun;  // 执行函数指针
    LPVOID pThreadFunParams;
} WaitingDlgThreadStruct, *LPWaitingDlgThreadStruct;


// CWaitingDlg 对话框

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


// CWaitingDlg 消息处理程序

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
        //取得SetLayeredWindowAttributes函数指针
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
    // 异常: OCX 属性页应返回 FALSE
}

void CWaitingDlg::OnOK()
{
    //
    // 屏蔽回车键
    //
    return;

    //CDialog::OnOK();
}

void CWaitingDlg::OnCancel()
{
    //
    // 屏蔽ESC键
    //
    return;

    //CDialog::OnCancel();
}

//
// 后台处理线程
//
AFX_THREADPROC backgroundThreadFun(LPWaitingDlgThreadStruct param)
{

    AFX_THREADPROC workFunc = param->pThreadFun;
    LPVOID params           = param->pThreadFunParams;

    UINT threadRet          = workFunc(params);

    //
    // 执行完毕关闭等待提示信息
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
    // 设置提示文字
    //
    m_szMessage             = szMsg;
    //
    // 开启线程处理函数
    //
    AfxBeginThread((AFX_THREADPROC)backgroundThreadFun, &wts);
    //
    // 显示等待提示信息
    //
    this->DoModal();
}

void CWaitingDlg::EndWaitingDlg()
{
    //
    // 释放GIF资源
    //
    m_gifWaiting.UnLoad();
    //
    // 关闭提示对话框
    //
    this->EndDialog(0);
}