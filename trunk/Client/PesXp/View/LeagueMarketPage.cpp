// View\LeagueMarketPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PesXp.h"
#include "LeagueMarketPage.h"
#include "PlayerLibDlg.h"
#include "WaitingDlg.h"
#include "SyncHandler.h"

// CLeagueMarketPage �Ի���

IMPLEMENT_DYNAMIC(CLeagueMarketPage, CPropertyPage)

CLeagueMarketPage::CLeagueMarketPage()
    : CPropertyPage(CLeagueMarketPage::IDD)
{
    m_bInitData = false;
}

CLeagueMarketPage::~CLeagueMarketPage()
{
}

void CLeagueMarketPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_MARKET, m_listCtrl);
    DDX_Control(pDX, IDC_LIST_MY_MARKET, m_listCtrlMyTeam);
}


BEGIN_MESSAGE_MAP(CLeagueMarketPage, CPropertyPage)
    ON_BN_CLICKED(IDC_MARKET_BUTTON, &CLeagueMarketPage::OnBnClickedMarketButton)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CLeagueMarketPage ��Ϣ�������

BOOL CLeagueMarketPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    //
    // ��ʼ��ת���г��б�
    //
    LONG lStyle;
    lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
    lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
    lStyle |= LVS_REPORT; //����style
    SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle);//����style

    DWORD dwStyles = m_listCtrl.GetExtendedStyle();
    dwStyles |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
    dwStyles |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
    m_listCtrl.SetExtendedStyle(dwStyles); //������չ���

    m_listCtrl.InsertColumn( 0, _T("����"), LVCFMT_LEFT, 55);//������
    m_listCtrl.InsertColumn( 1, _T("��Ա"), LVCFMT_LEFT, 65);
    m_listCtrl.InsertColumn( 2, _T("���"), LVCFMT_LEFT, 50);
    m_listCtrl.InsertColumn( 3, _T("�ȼ�"), LVCFMT_LEFT, 55);
    m_listCtrl.InsertColumn( 5, _T("ת��"), LVCFMT_LEFT, 60);
    m_listCtrl.InsertColumn( 6, _T("ת��"), LVCFMT_LEFT, 60);
    m_listCtrl.InsertColumn( 7, _T("����"), LVCFMT_LEFT, 50);

    //
    // �ҵ�ת�ᶯ̬
    //
    lStyle = GetWindowLong(m_listCtrlMyTeam.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
    lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
    lStyle |= LVS_REPORT; //����style
    SetWindowLong(m_listCtrlMyTeam.m_hWnd, GWL_STYLE, lStyle);//����style

    dwStyles = m_listCtrlMyTeam.GetExtendedStyle();
    dwStyles |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
    dwStyles |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
    m_listCtrlMyTeam.SetExtendedStyle(dwStyles); //������չ���

    m_listCtrlMyTeam.InsertColumn( 0, _T("����"), LVCFMT_LEFT, 55);//������
    m_listCtrlMyTeam.InsertColumn( 1, _T("��Ա"), LVCFMT_LEFT, 65);
    m_listCtrlMyTeam.InsertColumn( 2, _T("���"), LVCFMT_LEFT, 55);
    m_listCtrlMyTeam.InsertColumn( 3, _T("�ȼ�"), LVCFMT_LEFT, 55);
    m_listCtrlMyTeam.InsertColumn( 7, _T("����"), LVCFMT_LEFT, 50);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CLeagueMarketPage::OnBnClickedMarketButton()
{
    CPlayerLibDlg* pPlayerLibDlg = new CPlayerLibDlg();
    pPlayerLibDlg->DoModal();
}

void CLeagueMarketPage::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    
    if (!m_bInitData)
    {
        CWaitingDlg::GetInstance()->PerformSelectorAndBeginWaitingDlg((CDialog*)(CPropertySheet*)this->GetParent(), _T("��ȡת���г���Ϣ"), CSyncHandler::RequestMarketInfo , this);
        m_bInitData = true;
    }
    // ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
}
