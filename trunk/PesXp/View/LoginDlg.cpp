// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PesXp.h"
#include "LoginDlg.h"
#include "const.h"
#include "WaitingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// �Ի�������
    enum { IDD = IDD_ABOUTBOX };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLoginDlg �Ի���

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


// CLoginDlg ��Ϣ�������

BOOL CLoginDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // ��������...���˵�����ӵ�ϵͳ�˵��С�

    // IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    // TODO: �ڴ���Ӷ���ĳ�ʼ������

    //
    // ��ȡע��Ի���λ�ò���
    //
    GetWindowRect(&m_rectRegister);
    //
    // ��ȡ��½��ע��ָ��ߵ�λ�ò��������õ���bottom��
    //
    GetDlgItem(IDC_LOGIN_SEPARATOR)->GetWindowRect(&m_rectSeparator);
    //
    // �����½�Ի���λ�ò���
    //
    m_rectLogin.left   = m_rectRegister.left;
    m_rectLogin.top    = m_rectRegister.top;
    m_rectLogin.right  = m_rectRegister.right;
    m_rectLogin.bottom = m_rectSeparator.bottom;

    //
    // Ĭ����ʾ��½�Ի���
    //
    SetWindowPos(NULL, 0, 0, m_rectLogin.Width(), m_rectLogin.Height(), SWP_NOMOVE | SWP_NOZORDER);

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLoginDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // ���ڻ��Ƶ��豸������

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // ʹͼ���ڹ����������о���
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // ����ͼ��
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLoginDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

//
// �����½�߼�
//
void CLoginDlg::OnBnClickedLoginButtonLogin()
{
    //
    // ��ȡ�Ի�����������
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
        WaitingDlg.PerformSelectorAndBeginWaitingDlg(_T("��¼��..."), m_loginHandler->doLogin, NULL);
    //}
}

//
// ����ע���߼�
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
    // ����ϵͳ�س���
    //
    return;
}

//
// �����ύע���߼�
//
void CLoginDlg::OnBnClickedLoginButtonSubmit()
{
    //
    // ��ȡ�Ի�����������
    //
    UpdateData(true);

    //
    // �������Ϸ���
    //
    if (m_strRegUserName.GetLength() <= 0)
    {
        SetDlgItemText(IDC_REG_TEXT_TIP_INFO, _T("ע���û�������Ϊ��"));
        return;
    }

    if (m_strRegPassword.GetLength() < 6)
    {
        SetDlgItemText(IDC_REG_TEXT_TIP_INFO, _T("ע�����벻�ܵ���6λ"));
        return;
    }

    if (m_strRegPassword.Compare(m_strConfirmPassword) != 0)
    {
        SetDlgItemText(IDC_REG_TEXT_TIP_INFO, _T("�����������벻һ��"));
        return;
    }

    if (m_strQQ.GetLength() <= 0)
    {
        SetDlgItemText(IDC_REG_TEXT_TIP_INFO, _T("ע��QQ�Ų���Ϊ��"));
        return;
    }
    
    if ( !m_utilHandler->IsValidEmail(m_strMail))
    {
        SetDlgItemText(IDC_REG_TEXT_TIP_INFO, _T("ע�������ַ�Ƿ�"));
        return;
    }
    
    //
    // TODO ������ȷ ע���߼�
    //
    if (!m_loginHandler->doRegister(m_strRegUserName,
                                    m_strRegPassword,
                                    m_strQQ,
                                    m_strMail))
    {
        //
        // TODO ��������߼�
        //
    }
}

//
// �Զ����ı���ɫ
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