#pragma once
#include "afxwin.h"


// CLeagueInfoPage �Ի���

class CLeagueInfoPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CLeagueInfoPage)

public:
    CLeagueInfoPage();
    virtual ~CLeagueInfoPage();
    
    //
    // �����Ƿ���ʾ����������ť
    //
    void ShowJoinButton(bool show);

// �Ի�������
    enum { IDD = IDD_LEAGUE_INFO_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
