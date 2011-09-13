// PlayerLibDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <stdio.h> 
#include "PesXp.h"
#include "PlayerLibDlg.h"
#include "PlayerSearchDlg.h"


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

    m_listCtrl.InsertColumn( 0, _T("����"), LVCFMT_LEFT, 92);//������
    m_listCtrl.InsertColumn( 1, _T("����"), LVCFMT_LEFT, 75);
    m_listCtrl.InsertColumn( 2, _T("���ֲ�"), LVCFMT_LEFT, 90);
    m_listCtrl.InsertColumn( 3, _T("λ��"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 4, _T("�ۺ�"), LVCFMT_LEFT, 40);

    //
    // ������ʾ��Ϣ�ؼ�����
    //
    EnableToolTips(TRUE); 
    m_ttCtrl.Create(this); 
    m_ttCtrl.Activate(TRUE);
    
    if (!m_pPlayerLibHandler)
    {
        m_pPlayerLibHandler = new CPlayerLibHandler(m_hWnd, &m_treeCtrl, &m_listCtrl, &m_pictureCtrl, &m_ttCtrl);
    }
    m_pPlayerLibHandler->initContinents();
    m_pPlayerLibHandler->initTeams();

    //
    // ���ô�������
    //
    CWnd* pWnd   = GetDlgItem(IDC_STATIC_12);
    CFont* pFont = pWnd->GetFont(); 
    pFont-> GetLogFont(&m_boldFont);
    m_boldFont.lfWeight = FW_BOLD;
    pFont->Detach();

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
    CString team_name     = m_treeCtrl.GetItemText(select_htem);
    if (team_name == "�Զ�������")
    {
        //
        // �����Զ�����������ģ̬�Ի���
        //
        CPlayerSearchDlg playerSearchDlg;
        playerSearchDlg.setPlayerLibHandler(m_pPlayerLibHandler);
        if (playerSearchDlg.DoModal() == IDOK && !m_isShowMidWnd)
        {
            SetWindowPos(NULL, 0, 0, m_rectMid.Width(), m_rectMid.Height(), SWP_NOMOVE | SWP_NOZORDER);
            m_isShowMidWnd = true;
        }
        return;
    }
    //
    // ���ѡ���ѡ���򲻴���
    //
    HTREEITEM parent_item = m_treeCtrl.GetParentItem(select_htem);
    if (!parent_item)
    {
        return;
    }

    CString parent_name = m_treeCtrl.GetItemText(parent_item);

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
        ctrlId <= IDC_STATIC_44))
    {
        COLORREF rgb  = 0;
        CString strVal = "";
        pWnd->GetWindowText(strVal);
        if (strVal[0] >= 'A' || strVal[0] >= 'D')
        {
            if (strVal[0] == 'A')
            {
                rgb = RGB(255, 0, 0);
            }
            else if (strVal[0] == 'B')
            {
                rgb = RGB(255, 180, 0);
            }
        }
        else
        {
            int intVal = atoi(strVal);
            if (intVal >= 95)
            {
                rgb = RGB(255, 0, 0);
            }
            else if (intVal >= 90)
            {
                rgb = RGB(255, 60, 0);
            }
            else if (intVal >= 80)
            {
                rgb = RGB(255, 120, 0);
            }
            else if (intVal >= 75)
            {
                rgb = RGB(255, 180, 0);
            }
        }
        
        pDC->SetTextColor(rgb);
        if (rgb != 0)
        {
            CFont font;
            font.CreateFontIndirect(&m_boldFont);
            pDC-> SelectObject(&font); 
        }
    }

    //}
    // TODO:  Return a different brush if the default is not desired
    return hbr;
}

BOOL CPlayerLibDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: �ڴ����ר�ô����/����û���
    if (NULL != m_ttCtrl.GetSafeHwnd())            
        m_ttCtrl.RelayEvent(pMsg);


    return CDialog::PreTranslateMessage(pMsg);
}