// View\LeagueHonorPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PesXp.h"
#include "LeagueHonorPage.h"
#include "WaitingDlg.h"
#include "SyncHandler.h"

// CLeagueHonorPage �Ի���

IMPLEMENT_DYNAMIC(CLeagueHonorPage, CPropertyPage)

CLeagueHonorPage::CLeagueHonorPage()
    : CPropertyPage(CLeagueHonorPage::IDD)
{
    m_bInitData = false;
}

CLeagueHonorPage::~CLeagueHonorPage()
{
}

void CLeagueHonorPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_HONOR, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CLeagueHonorPage, CPropertyPage)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CLeagueHonorPage ��Ϣ�������

BOOL CLeagueHonorPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    //
    // ��ʼ����ҫ�����б�
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

    m_listCtrl.InsertColumn( 0, _T("����"), LVCFMT_LEFT, 80);//������
    m_listCtrl.InsertColumn( 1, _T("�����"), LVCFMT_LEFT, 55);
    m_listCtrl.InsertColumn( 2, _T("�ھ�"), LVCFMT_LEFT, 60);
    m_listCtrl.InsertColumn( 3, _T("�Ǿ�"), LVCFMT_LEFT, 60);
    m_listCtrl.InsertColumn( 5, _T("��ѥ��"), LVCFMT_LEFT, 70);
    m_listCtrl.InsertColumn( 6, _T("������"), LVCFMT_LEFT, 70);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CLeagueHonorPage::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    if (!m_bInitData)
    {
        CWaitingDlg::GetInstance()->PerformSelectorAndBeginWaitingDlg((CDialog*)(CPropertySheet*)this->GetParent(), _T("��ȡ��ҫ�����Ϣ"), CSyncHandler::RequestHonorInfo , this);
        m_bInitData = true;
    }
    // ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
}
