#pragma once
#include "afxwin.h"


// CLeagueInfoPage 对话框

class CLeagueInfoPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CLeagueInfoPage)

public:
    CLeagueInfoPage();
    virtual ~CLeagueInfoPage();
    
    //
    // 设置是否显示报名参赛按钮
    //
    void ShowJoinButton(bool show);

// 对话框数据
    enum { IDD = IDD_LEAGUE_INFO_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

private:
    bool m_bShowJoinButton;
    bool m_bInitData;
public:
    virtual BOOL OnInitDialog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnPaint();
    CButton m_btnUpdate;
    void OnButtonUpdate();
};
