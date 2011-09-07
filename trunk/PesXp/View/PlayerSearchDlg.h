#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "PlayerLibHandler.h"

// CPlayerSearchDlg dialog

class CPlayerSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlayerSearchDlg)

public:
	CPlayerSearchDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlayerSearchDlg();

// Dialog Data
	enum { IDD = IDD_PLAYER_SEARCH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_chkName;
	CButton m_chkWeName;
	CButton m_chkCountry;
	CButton m_chkClub;
	CButton m_chkPos;
	CButton m_chkHeight;
	CButton m_chkWeight;
	CButton m_chkBirth;
	CButton m_chkCons;
	CButton m_chkAge;
	CButton m_chkFoot;
	CButton m_chkSide;
	CButton m_chkValue;
	CEdit m_textName;
	CEdit m_textWeName;
	CComboBox m_cmbContinet;
	CComboBox m_cmbCountry;
	CComboBox m_cmbContinetClub;
	CComboBox m_cmbClub;
	CComboBox m_cmbPos;
	CComboBox m_cmbSide;
	CSpinButtonCtrl m_spHeightMin;
	CSpinButtonCtrl m_spHeightMax;
	CSpinButtonCtrl m_spWeightMin;
	CSpinButtonCtrl m_spWeightMax;
	CDateTimeCtrl m_dateBirth;
	CComboBox m_cmbCons;
	CSpinButtonCtrl m_spAgeMin;
	CSpinButtonCtrl m_spAgeMax;
	CComboBox m_cmbFoot;
	CSpinButtonCtrl m_spValueMin;
	CSpinButtonCtrl m_spValueMax;
	virtual BOOL OnInitDialog();
	CEdit m_textHeightMin;
	CEdit m_textHeightMax;
	CEdit m_textWeightMin;
	CEdit m_textWeightMax;
	CEdit m_textAgeMin;
	CEdit m_textAgeMax;
	CEdit m_textValueMin;
	CEdit m_textValueMax;
	afx_msg void OnBnClickedCheckName();
	afx_msg void OnBnClickedCheckWeName();
	afx_msg void OnBnClickedCheckCountry();
	afx_msg void OnBnClickedCheckClub();
	afx_msg void OnBnClickedCheckPos();
	afx_msg void OnBnClickedCheckHeight();
	afx_msg void OnBnClickedCheckWeight();
	afx_msg void OnBnClickedCheckBirth();
	afx_msg void OnBnClickedCheckCons();
	afx_msg void OnBnClickedCheckAge();
	afx_msg void OnBnClickedCheckFoot();
	afx_msg void OnBnClickedCheckValue();
	afx_msg void OnBnClickedCheckSide();

	void initCmbContinetCountry();
	void initCmbContinetClub();
	void initCmbCountry();
	void initCmbClub();
	void initCmbPos();
	void initCmbFoot();
	void initCmbSide();
	void initCmbCons();

	void setPlayerLibHandler(CPlayerLibHandler*);

private:
	CPlayerLibHandler* m_pPlayerLibHandler;
public:
	afx_msg void OnCbnSelchangeComboContinet();
	afx_msg void OnBnClickedButtonSearch();
};
