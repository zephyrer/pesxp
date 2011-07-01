// PlayerLibDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <stdio.h> 
#include "PesXp.h"
#include "PlayerLibDlg.h"


// CPlayerLibDlg �Ի���

IMPLEMENT_DYNAMIC(CPlayerLibDlg, CDialog)

CPlayerLibDlg::CPlayerLibDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayerLibDlg::IDD, pParent)
{
	m_isShowMidWnd = false;
	m_isShowLargeWnd = false;
	m_pPlayerLibHandler = NULL;
}

CPlayerLibDlg::~CPlayerLibDlg()
{
}

void CPlayerLibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAYER_LIB_TREE, m_treeCtrl);
	DDX_Control(pDX, IDC_PLAYER_LIB_LIST, m_listCtrl);
	DDX_Control(pDX, IDC_PIC_STATIC, m_pictureCtrl);
}
BEGIN_MESSAGE_MAP(CPlayerLibDlg, CDialog)

	ON_NOTIFY(TVN_SELCHANGED, IDC_PLAYER_LIB_TREE, &CPlayerLibDlg::OnTvnSelchangedPlayerLibTree)
	ON_NOTIFY(NM_DBLCLK, IDC_PLAYER_LIB_LIST, &CPlayerLibDlg::OnNMDblclkPlayerLibList)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPlayerLibDlg ��Ϣ�������

BOOL CPlayerLibDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//
    // ��ȡע��Ի���λ�ò���
    //
    GetWindowRect(&m_rectLarge);
    //
    // ��ȡ��½��ע��ָ��ߵ�λ�ò��������õ���bottom��
    //
	GetDlgItem(IDC_PLAYER_LIB_SEPARATOR1)->GetWindowRect(&m_rectSeparatorVertical);
    GetDlgItem(IDC_PLAYER_LIB_SEPARATOR2)->GetWindowRect(&m_rectSeparatorHorizontal);

	//
	// ��ȡĬ����ʾ�ĶԻ���λ�ô�С
	//
    m_rectMid.left    = m_rectSmall.left   = m_rectLarge.left;
    m_rectMid.top     = m_rectSmall.top    = m_rectLarge.top;
    m_rectMid.bottom  = m_rectSmall.bottom = m_rectSeparatorHorizontal.bottom;
	m_rectMid.right   = m_rectLarge.right;
	m_rectSmall.right = m_rectSeparatorVertical.right;

    //
    // Ĭ����ʾ��С�Ի���
    //
    SetWindowPos(NULL, 0, 0, m_rectSmall.Width(), m_rectSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);

	//
	// ��ʼ������б�
	//
	DWORD dwStyles=GetWindowLong(m_treeCtrl.m_hWnd,GWL_STYLE);//��ȡ������ԭ���
	dwStyles|=TVS_EDITLABELS|TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT;
	SetWindowLong(m_treeCtrl.m_hWnd,GWL_STYLE,dwStyles);//���÷��

	m_treeCtrl.ModifyStyle(LVS_SORTASCENDING|LVS_SORTDESCENDING,0);

	//
	// ��ʼ����Ա�б�
	//
	LONG lStyle;
	lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle);//����style

	dwStyles = m_listCtrl.GetExtendedStyle();
	dwStyles |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyles |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listCtrl.SetExtendedStyle(dwStyles); //������չ���

	m_listCtrl.InsertColumn( 0, "����", LVCFMT_LEFT, 92);//������
	m_listCtrl.InsertColumn( 1, "����", LVCFMT_LEFT, 75);
	m_listCtrl.InsertColumn( 2, "���ֲ�", LVCFMT_LEFT, 90);
	m_listCtrl.InsertColumn( 3, "λ��", LVCFMT_LEFT, 40);
	m_listCtrl.InsertColumn( 4, "�ۺ�", LVCFMT_LEFT, 40);
	
	if (!m_pPlayerLibHandler)
	{
		m_pPlayerLibHandler = new CPlayerLibHandler(&m_treeCtrl, &m_listCtrl, &m_pictureCtrl);
	}
	m_pPlayerLibHandler->initContinents();
	m_pPlayerLibHandler->initTeams();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//
// ��ѡ�����οؼ��е�ĳһ������ô˺���
//
void CPlayerLibDlg::OnTvnSelchangedPlayerLibTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//
    // ���ѡ����
	//
    HTREEITEM select_htem = m_treeCtrl.GetSelectedItem();
	//
	// ���ѡ���ѡ���򲻴���
	//
	HTREEITEM parent_item = m_treeCtrl.GetParentItem(select_htem);
	if (!parent_item)
	{
		return;
	}

	CString parent_name = m_treeCtrl.GetItemText(parent_item);
    CString team_name   = m_treeCtrl.GetItemText(select_htem);

	if (!m_isShowMidWnd)
	{
		SetWindowPos(NULL, 0, 0, m_rectMid.Width(), m_rectMid.Height(), SWP_NOMOVE | SWP_NOZORDER);
		m_isShowMidWnd = true;
	}

	bool is_club = true;
	if (parent_name == "ŷ��" || parent_name == "����" || parent_name == "�����С�������" || parent_name == "���ޡ�������")
	{
		is_club = false;
	}

	m_pPlayerLibHandler->getPlayerListByTeamName(team_name.GetBuffer(), is_club);

	*pResult = 0;
}
void CPlayerLibDlg::OnNMDblclkPlayerLibList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if (pNMLV->iItem == -1)
	{
		return;
	}

	if (!m_isShowLargeWnd)
	{
		SetWindowPos(NULL, 0, 0, m_rectLarge.Width(), m_rectLarge.Height(), SWP_NOMOVE | SWP_NOZORDER);
		m_isShowLargeWnd = true;
		//SendMessage(WM_CTLCOLOR);
	}
	
	int player_count = m_pPlayerLibHandler->m_player_list.size();
	string name = m_pPlayerLibHandler->m_player_list[player_count - pNMLV->iItem - 1].first;
	string club = m_pPlayerLibHandler->m_player_list[player_count - pNMLV->iItem - 1].second;
	
	m_pPlayerLibHandler->getPlayerDetail(name.c_str(), club.c_str());

	*pResult = 0;
}

//
// �Զ����ı���ɫ
//
HBRUSH CPlayerLibDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	int ctrlId = pWnd->GetDlgCtrlID();

	if (ctrlId == IDC_STATIC_12 ||
		(ctrlId >= IDC_STATIC_15 && 
		ctrlId <= IDC_STATIC_40))
	{
		pDC->SetTextColor(RGB(255, 0, 0));

// 		CFont*   pFont=pWnd-> GetFont(); 
// 		LOGFONT   lf; 
// 		pFont-> GetLogFont(&lf); 
// 		lf.lfWeight=FW_BOLD; 
// 		pFont-> DeleteObject(); 
// 		pFont-> CreateFontIndirect(&lf); 
// 		pWnd-> SetFont(pFont); 
// 		pFont-> DeleteObject(); 
	}
	else {
	}
// 	// TODO:  Change any attributes of the DC here
// 	if (GetDlgItem(IDC_STATIC_12) == pWnd || \
// 		GetDlgItem(IDC_STATIC_15) == pWnd || \
// 		GetDlgItem(IDC_STATIC_16) == pWnd || \
// 		GetDlgItem(IDC_STATIC_17) == pWnd || \
// 		GetDlgItem(IDC_STATIC_18) == pWnd || \
// 		GetDlgItem(IDC_STATIC_19) == pWnd || \
// 		GetDlgItem(IDC_STATIC_20) == pWnd || \
// 		GetDlgItem(IDC_STATIC_21) == pWnd || \
// 		GetDlgItem(IDC_STATIC_22) == pWnd || \
// 		GetDlgItem(IDC_STATIC_23) == pWnd || \
// 		GetDlgItem(IDC_STATIC_24) == pWnd || \
// 		GetDlgItem(IDC_STATIC_25) == pWnd || \
// 		GetDlgItem(IDC_STATIC_26) == pWnd || \
// 		GetDlgItem(IDC_STATIC_27) == pWnd || \
// 		GetDlgItem(IDC_STATIC_28) == pWnd || \
// 		GetDlgItem(IDC_STATIC_29) == pWnd || \
// 		GetDlgItem(IDC_STATIC_30) == pWnd || \
// 		GetDlgItem(IDC_STATIC_31) == pWnd || \
// 		GetDlgItem(IDC_STATIC_32) == pWnd || \
// 		GetDlgItem(IDC_STATIC_33) == pWnd || \
// 		GetDlgItem(IDC_STATIC_34) == pWnd || \
// 		GetDlgItem(IDC_STATIC_35) == pWnd || \
// 		GetDlgItem(IDC_STATIC_36) == pWnd || \
// 		GetDlgItem(IDC_STATIC_37) == pWnd || \
// 		GetDlgItem(IDC_STATIC_38) == pWnd || \
// 		GetDlgItem(IDC_STATIC_39) == pWnd || \
// 		GetDlgItem(IDC_STATIC_40) == pWnd)
// 	{
		
	//}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}