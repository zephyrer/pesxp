#pragma once
#include "afxcmn.h"
#include "PlayerLibHandler.h"
#include "afxwin.h"

// CPlayerLibDlg 对话框

class CPlayerLibDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlayerLibDlg)

public:
	CPlayerLibDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPlayerLibDlg();

// 对话框数据
	enum { IDD = IDD_PLAYER_LIB_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

private:
	CRect            m_rectLarge;               // 完整对话框的大小
	CRect            m_rectMid;                 // 中等对话框的大小
    CRect            m_rectSmall;			    // 最小对话框的大小
    CRect            m_rectSeparatorVertical;   // 垂直分隔线
	CRect            m_rectSeparatorHorizontal; // 水平分隔线
	bool			 m_isShowMidWnd;			// 是否显示中等对话框大小
	bool			 m_isShowLargeWnd;			// 是否显示完整对话框大小
	CTreeCtrl		 m_treeCtrl;				// 选择查找条件控件
	CListCtrl		 m_listCtrl;				// 球员列表控件
	CStatic			 m_pictureCtrl;				// 球员头像显示控件

	CPlayerLibHandler* m_pPlayerLibHandler;		// 球员信息处理

	CFont*   m_pFont; 
	LOGFONT   m_lf;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedPlayerLibTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkPlayerLibList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
