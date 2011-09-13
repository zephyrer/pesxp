// View\LeagueAssitantPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueAssitantPage.h"


// CLeagueAssitantPage �Ի���

IMPLEMENT_DYNAMIC(CLeagueAssitantPage, CPropertyPage)

CLeagueAssitantPage::CLeagueAssitantPage()
	: CPropertyPage(CLeagueAssitantPage::IDD)
{

}

CLeagueAssitantPage::~CLeagueAssitantPage()
{
}

void CLeagueAssitantPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_ASSITANT_RANK, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CLeagueAssitantPage, CPropertyPage)
END_MESSAGE_MAP()


// CLeagueAssitantPage ��Ϣ�������

BOOL CLeagueAssitantPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    //
    // ��ʼ�������������б�
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

    m_listCtrl.InsertColumn( 0, _T("����"), LVCFMT_LEFT, 40);//������
    m_listCtrl.InsertColumn( 1, _T("����"), LVCFMT_LEFT, 65);
    m_listCtrl.InsertColumn( 2, _T("���"), LVCFMT_LEFT, 60);
    m_listCtrl.InsertColumn( 3, _T("���"), LVCFMT_LEFT, 50);
    m_listCtrl.InsertColumn( 4, _T("λ��"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 5, _T("����"), LVCFMT_LEFT, 50);
    m_listCtrl.InsertColumn( 6, _T("����"), LVCFMT_LEFT, 45);
    m_listCtrl.InsertColumn( 7, _T("����"), LVCFMT_LEFT, 45);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
