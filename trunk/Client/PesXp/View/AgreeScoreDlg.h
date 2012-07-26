#pragma once


// CAgreeScoreDlg dialog

class CAgreeScoreDlg : public CDialog
{
	DECLARE_DYNAMIC(CAgreeScoreDlg)

public:
	CAgreeScoreDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAgreeScoreDlg();

// Dialog Data
	enum { IDD = IDD_AGREE_SCORE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
