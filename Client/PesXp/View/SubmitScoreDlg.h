#pragma once


// CSubmitScoreDlg dialog

class CSubmitScoreDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubmitScoreDlg)

public:
	CSubmitScoreDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubmitScoreDlg();

// Dialog Data
	enum { IDD = IDD_SUBMIT_SCORE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
