// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "LoginDlg.h"
#include "const.h"
#include "WaitingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// 对话框数据
    enum { IDD = IDD_ABOUTBOX };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CLoginDlg 对话框

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CLoginDlg::IDD, pParent)
    , m_strLoginUserName(_T(""))
    , m_strLoginPassword(_T(""))
    , m_strRegUserName(_T(""))
    , m_strRegPassword(_T(""))
    , m_strConfirmPassword(_T(""))
    , m_strQQ(_T(""))
    , m_strMail(_T(""))
{
    m_isLoginDlg    = true;
    m_utilHandler   = CUtilHandler::GetInstance();
    m_hIcon         = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_LOGIN_EDIT_USER_NAME, m_strLoginUserName);
    DDX_Text(pDX, IDC_LOGIN_EDIT_PASSWORD, m_strLoginPassword);
    DDX_Text(pDX, IDC_REG_EDIT_USER_NAME, m_strRegUserName);
    DDX_Text(pDX, IDC_REG_EDIT_PASSWORD, m_strRegPassword);
    DDX_Text(pDX, IDC_REG_EDIT_CONFIRM_PASSWORD, m_strConfirmPassword);
    DDX_Text(pDX, IDC_REG_EDIT_QQ, m_strQQ);
    DDX_Text(pDX, IDC_REG_EDIT_EMAIL, m_strMail);

    DDX_Control(pDX, IDC_REG_TEXT_TIP_INFO, m_staticTipInfo);
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_LOGIN_BUTTON_LOGIN, &CLoginDlg::OnBnClickedLoginButtonLogin)
    ON_BN_CLICKED(IDC_LOGIN_BUTTON_REGISTER, &CLoginDlg::OnBnClickedLoginButtonRegister)
    ON_BN_CLICKED(IDC_LOGIN_BUTTON_SUBMIT, &CLoginDlg::OnBnClickedLoginButtonSubmit)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

BOOL CLoginDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    // TODO: 在此添加额外的初始化代码

    //
    // 获取注册对话框位置参数
    //
    GetWindowRect(&m_rectRegister);
    //
    // 获取登陆与注册分隔线的位置参数（有用的是bottom）
    //
    GetDlgItem(IDC_LOGIN_SEPARATOR)->GetWindowRect(&m_rectSeparator);
    //
    // 保存登陆对话框位置参数
    //
    m_rectLogin.left   = m_rectRegister.left;
    m_rectLogin.top    = m_rectRegister.top;
    m_rectLogin.right  = m_rectRegister.right;
    m_rectLogin.bottom = m_rectSeparator.bottom;

    //
    // 默认显示登陆对话框
    //
    SetWindowPos(NULL, 0, 0, m_rectLogin.Width(), m_rectLogin.Height(), SWP_NOMOVE | SWP_NOZORDER);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLoginDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLoginDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

//
// 处理登陆逻辑
//
void CLoginDlg::OnBnClickedLoginButtonLogin()
{
    //
    // 获取对话框输入数据
    //
    UpdateData(true);

    if (m_strLoginUserName.GetLength() <= 0 || m_strLoginPassword.GetLength() <= 0)
    {
        return;
    }

    //if (m_loginHandler->doLogin(m_strLoginUserName, m_strLoginPassword))
    //{
        //return CDialog::OnOK();
        CWaitingDlg WaitingDlg(this);
        WaitingDlg.PerformSelectorAndBeginWaitingDlg(_T("登录中..."), m_loginHandler->doLogin, NULL);
    //}
}

//
// 处理注册逻辑
//
void CLoginDlg::OnBnClickedLoginButtonRegister()
{
    if (m_isLoginDlg)
    {
        SetWindowPos(NULL, 0, 0, m_rectRegister.Width(), m_rectRegister.Height(), SWP_NOMOVE | SWP_NOZORDER);
        m_isLoginDlg = false;
        (CButton*)GetDlgItem(IDC_LOGIN_BUTTON_LOGIN)->EnableWindow(false);
    }
    else
    {
        SetWindowPos(NULL, 0, 0, m_rectLogin.Width(), m_rectLogin.Height(), SWP_NOMOVE | SWP_NOZORDER);
        m_isLoginDlg = true;
        (CButton*)GetDlgItem(IDC_LOGIN_BUTTON_LOGIN)->EnableWindow(true);
    }
}

void CLoginDlg::OnOK()
{
    //
    // 屏蔽系统回车键
    //
    return;
}

//
// 处理提交注册逻辑
//
void CLoginDlg::OnBnClickedLoginButtonSubmit()
{
    //
    // 获取对话框输入数据
    //
    UpdateData(true);

    //
    // 检查参数合法性
    //
    if (m_strRegUserName.GetLength() <= 0)
    {
        SetDlgItemText(IDC_REG_TEXT_TIP_INFO, _T("注册用户名不能为空"));
        return;
    }

    if (m_strRegPassword.GetLength() < 6)
    {
        SetDlgItemText(IDC_REG_TEXT_TIP_INFO, _T("注册密码不能低于6位"));
        return;
    }

    if (m_strRegPassword.Compare(m_strConfirmPassword) != 0)
    {
        SetDlgItemText(IDC_REG_TEXT_TIP_INFO, _T("两次输入密码不一致"));
        return;
    }

    if (m_strQQ.GetLength() <= 0)
    {
        SetDlgItemText(IDC_REG_TEXT_TIP_INFO, _T("注册QQ号不能为空"));
        return;
    }
    
    if ( !m_utilHandler->IsValidEmail(m_strMail))
    {
        SetDlgItemText(IDC_REG_TEXT_TIP_INFO, _T("注册邮箱地址非法"));
        return;
    }
    
    //
    // TODO 参数正确 注册逻辑
    //
    if (!m_loginHandler->doRegister(m_strRegUserName,
                                    m_strRegPassword,
                                    m_strQQ,
                                    m_strMail))
    {
        //
        // TODO 处理错误逻辑
        //
    }
}

//
// 自定义文本颜色
//
HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  Change any attributes of the DC here
    if (GetDlgItem(IDC_REG_TEXT_TIP_INFO) == pWnd)
    {
        pDC->SetTextColor(RGB(255, 0, 0));
    }

    // TODO:  Return a different brush if the default is not desired
    return hbr;
}