// PlayerLibDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <stdio.h> 
#include "PesXp.h"
#include "PlayerLibDlg.h"


// CPlayerLibDlg 对话框

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


// CPlayerLibDlg 消息处理程序

BOOL CPlayerLibDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//
    // 获取注册对话框位置参数
    //
    GetWindowRect(&m_rectLarge);
    //
    // 获取登陆与注册分隔线的位置参数（有用的是bottom）
    //
	GetDlgItem(IDC_PLAYER_LIB_SEPARATOR1)->GetWindowRect(&m_rectSeparatorVertical);
    GetDlgItem(IDC_PLAYER_LIB_SEPARATOR2)->GetWindowRect(&m_rectSeparatorHorizontal);

	//
	// 获取默认显示的对话框位置大小
	//
    m_rectMid.left    = m_rectSmall.left   = m_rectLarge.left;
    m_rectMid.top     = m_rectSmall.top    = m_rectLarge.top;
    m_rectMid.bottom  = m_rectSmall.bottom = m_rectSeparatorHorizontal.bottom;
	m_rectMid.right   = m_rectLarge.right;
	m_rectSmall.right = m_rectSeparatorVertical.right;

    //
    // 默认显示最小对话框
    //
    SetWindowPos(NULL, 0, 0, m_rectSmall.Width(), m_rectSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);

	//
	// 初始化球队列表
	//
	DWORD dwStyles=GetWindowLong(m_treeCtrl.m_hWnd,GWL_STYLE);//获取树控制原风格
	dwStyles|=TVS_EDITLABELS|TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT;
	SetWindowLong(m_treeCtrl.m_hWnd,GWL_STYLE,dwStyles);//设置风格

	m_treeCtrl.ModifyStyle(LVS_SORTASCENDING|LVS_SORTDESCENDING,0);

	//
	// 初始化球员列表
	//
	LONG lStyle;
	lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle);//设置style

	dwStyles = m_listCtrl.GetExtendedStyle();
	dwStyles |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyles |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listCtrl.SetExtendedStyle(dwStyles); //设置扩展风格

	m_listCtrl.InsertColumn( 0, "姓名", LVCFMT_LEFT, 92);//插入列
	m_listCtrl.InsertColumn( 1, "国籍", LVCFMT_LEFT, 75);
	m_listCtrl.InsertColumn( 2, "俱乐部", LVCFMT_LEFT, 90);
	m_listCtrl.InsertColumn( 3, "位置", LVCFMT_LEFT, 40);
	m_listCtrl.InsertColumn( 4, "综合", LVCFMT_LEFT, 40);
	
	if (!m_pPlayerLibHandler)
	{
		m_pPlayerLibHandler = new CPlayerLibHandler(&m_treeCtrl, &m_listCtrl, &m_pictureCtrl);
	}
	m_pPlayerLibHandler->initContinents();
	m_pPlayerLibHandler->initTeams();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//
// 当选择树形控件中的某一项后会调用此函数
//
void CPlayerLibDlg::OnTvnSelchangedPlayerLibTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	//
    // 获得选项句柄
	//
    HTREEITEM select_htem = m_treeCtrl.GetSelectedItem();
	//
	// 如果选择根选项则不处理
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
	if (parent_name == "欧洲" || parent_name == "非洲" || parent_name == "北、中、南美洲" || parent_name == "亚洲、大洋洲")
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
// 自定义文本颜色
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