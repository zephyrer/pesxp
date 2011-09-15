// View\WaitingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "WaitingDlg.h"
#include "UserItem.h"
#include "UserCenterDlg.h"
#include <process.h>

CWaitingDlg* CWaitingDlg::_hInstance = NULL;

// CWaitingDlg 对话框
AFX_THREADPROC backgroundThreadFun(LPWaitingDlgThreadStruct param);

IMPLEMENT_DYNAMIC(CWaitingDlg, CDialog)

CWaitingDlg* CWaitingDlg::GetInstance()
{
    if (_hInstance == NULL)
    {
        _hInstance = new CWaitingDlg();
    }
    return _hInstance;
}

CWaitingDlg::CWaitingDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CWaitingDlg::IDD, pParent)
{
    m_pParentDlg            = NULL;
    m_pThreadFun            = NULL;
    m_pThreadFunParams      = NULL;
    m_pTransparentDlg       = NULL;
    m_pSetTransparentFunc   = NULL;
    m_pTransparentDlg = new CDialog();
}

CWaitingDlg::~CWaitingDlg()
{
    if (m_pTransparentDlg)
    {
        m_pTransparentDlg->EndDialog(0);
        delete m_pTransparentDlg;
        m_pTransparentDlg = NULL;
    }
}

void CWaitingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_WAITING_GIF, m_gifWaiting);
    DDX_Control(pDX, IDC_WAITING_MESSAGE_TEXT, m_textWaiting);
}


BEGIN_MESSAGE_MAP(CWaitingDlg, CDialog)
    ON_WM_CTLCOLOR()
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CWaitingDlg 消息处理程序

BOOL CWaitingDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (m_pTransparentDlg == NULL)
    {
        m_pTransparentDlg = new CDialog();
        //m_pTransparentDlg->Create(IDD_TRANSPARENT_DIALOG);
        //m_pTransparentDlg->EnableWindow(FALSE);
    }

    SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
    SetWindowLong(m_pTransparentDlg->GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(m_pTransparentDlg->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);

    HINSTANCE hInst = LoadLibrary("User32.DLL");
    if(hInst)
    {
        //
        // 取得SetLayeredWindowAttributes函数指针
        //
        m_pSetTransparentFunc = (SetTransparentFunc)GetProcAddress(hInst, "SetLayeredWindowAttributes");
        if(m_pSetTransparentFunc) {
            m_pSetTransparentFunc(this->GetSafeHwnd(), RGB(240,240,240), 255, LWA_COLORKEY);
            m_pSetTransparentFunc(m_pTransparentDlg->GetSafeHwnd(), NULL, 128, LWA_ALPHA);
        }

        FreeLibrary(hInst);
    }

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
    UINT retCode            = workFunc(param);
    if (retCode > 0)
    {
        //
        // 异常处理
        //
        ;
    }
    //
    // 执行完毕关闭等待提示信息
    //
    param->pWaitingDlg->EndWaitingDlg();

    free(param);

    return 0;
}

void CWaitingDlg::BeginShowWaitingDlg(CDialog* pParent, LPCTSTR szMsg)
{
    m_pParentDlg    = pParent;
    m_szMessage     = szMsg;
    _hInstance->ShowWindow(SW_SHOW);
}

void CWaitingDlg::EndShowWaitingDlg()
{
    this->ShowWindow(SW_HIDE);
    m_pTransparentDlg->ShowWindow(SW_HIDE);
    //
    // 释放GIF资源
    //
    m_gifWaiting.UnLoad();
}

void CWaitingDlg::PerformSelectorAndBeginWaitingDlg(CDialog* pParent, LPCTSTR szMsg, LPVOID selector, LPVOID params)
{
    m_pThreadFun          = (AFX_THREADPROC)selector;
    m_pThreadFunParams    = params;
    m_pParentDlg          = pParent;
    m_szMessage           = szMsg;

    m_pTransparentDlg->Create(IDD_TRANSPARENT_DIALOG);
    m_pTransparentDlg->EnableWindow(FALSE);
    _hInstance->Create(IDD_WAITING_DIALOG);
    _hInstance->ShowWindow(SW_SHOW);
}

void CWaitingDlg::EndWaitingDlg()
{
    this->ShowWindow(SW_HIDE);
    m_pTransparentDlg->ShowWindow(SW_HIDE);
    //
    // 释放GIF资源
    //
    m_gifWaiting.UnLoad();

    //
    // 只是登录后才关闭
    //
    m_pParentDlg->EndDialog(IDOK);

    return;
//     //
//     // 关闭提示对话框
//     //
//     if (m_hWnd)
//     {
//         this->m_nFlags &= ~WF_CONTINUEMODAL;
//         this->EndDialog(0);
//     }
// 
//     m_pSetTransparentFunc(m_pParentWnd->GetSafeHwnd(), RGB(240,240,240), 255, LWA_ALPHA);
}
HBRUSH CWaitingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    if (GetDlgItem(IDC_WAITING_MESSAGE_TEXT)->m_hWnd == pWnd->m_hWnd)
    {
        pDC->SetTextColor(RGB(0, 0, 240));
        //
        // 设置粗体字体
        //
//         LOGFONT boldFont;
//         CFont* pFont = pWnd->GetFont(); 
//         pFont-> GetLogFont(&boldFont);
//         boldFont.lfWeight = FW_BOLD;
//         pFont->Detach();
// 
//         CFont font;
//         font.CreateFontIndirect(&boldFont);
//         pDC-> SelectObject(&font); 

    }

    return hbr;
}

void CWaitingDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

    if (!bShow)
    {
        return;
    }

    RECT rect;
    m_pParentDlg->GetWindowRect(&rect);
    m_pTransparentDlg->SetWindowPos(NULL, rect.left + 0.5, rect.top + 3.5, rect.right - rect.left, rect.bottom - rect.top - 3, SWP_NOZORDER | SWP_SHOWWINDOW);
    m_pTransparentDlg->ShowWindow(SW_SHOW);

    SetWindowPos(NULL, rect.left + 0.5, rect.top + 3.5, rect.right - rect.left, rect.bottom - rect.top - 3, SWP_NOZORDER | SWP_SHOWWINDOW);

    m_gifWaiting.SetWindowPos(NULL, (rect.right - rect.left) / 2 - 50, (rect.bottom - rect.top) / 2 - 10, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
    m_textWaiting.SetWindowPos(NULL, (rect.right - rect.left) / 2 - 10, (rect.bottom - rect.top) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);

    if (m_gifWaiting.Load(MAKEINTRESOURCE(IDR_GIF_WAITING),_T("GIF")))
        m_gifWaiting.Draw();

    m_textWaiting.SetWindowText(m_szMessage);

    if (m_pThreadFun)
    {
        LPWaitingDlgThreadStruct pWts   = (LPWaitingDlgThreadStruct)malloc(sizeof(WaitingDlgThreadStruct));
        pWts->pWaitingDlg               = this;
        pWts->pThreadFun                = m_pThreadFun;
        pWts->pThreadFunParams          = m_pThreadFunParams;
        //
        // 开启线程处理函数
        //
        AfxBeginThread((AFX_THREADPROC)backgroundThreadFun, pWts);
    }
}
