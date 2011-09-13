// View\LeagueCalendarPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueCalendarPage.h"


// CLeagueCalendarPage �Ի���

IMPLEMENT_DYNAMIC(CLeagueCalendarPage, CPropertyPage)

CLeagueCalendarPage::CLeagueCalendarPage()
	: CPropertyPage(CLeagueCalendarPage::IDD)
{

}

CLeagueCalendarPage::~CLeagueCalendarPage()
{
}

void CLeagueCalendarPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_CALENDAR, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CLeagueCalendarPage, CPropertyPage)
END_MESSAGE_MAP()


// CLeagueCalendarPage ��Ϣ�������

BOOL CLeagueCalendarPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    //
    // ��ʼ�������б�
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

    m_listCtrl.InsertColumn( 0, _T("����"), LVCFMT_LEFT, 60);//������
    m_listCtrl.InsertColumn( 1, _T("����"), LVCFMT_LEFT, 75);
    m_listCtrl.InsertColumn( 2, _T("����"), LVCFMT_LEFT, 75);
    m_listCtrl.InsertColumn( 3, _T("�Ͷ�"), LVCFMT_LEFT, 75);
    m_listCtrl.InsertColumn( 4, _T("״̬"), LVCFMT_LEFT, 50);
    m_listCtrl.InsertColumn( 5, _T("�ȷ�"), LVCFMT_LEFT, 60);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
