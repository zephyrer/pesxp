#pragma once
#include "afxcmn.h"
#include "PlayerLibHandler.h"
#include "afxwin.h"

// CPlayerLibDlg �Ի���

class CPlayerLibDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlayerLibDlg)

public:
	CPlayerLibDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPlayerLibDlg();

// �Ի�������
	enum { IDD = IDD_PLAYER_LIB_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

private:
	CRect            m_rectLarge;               // �����Ի���Ĵ�С
	CRect            m_rectMid;                 // �еȶԻ���Ĵ�С
    CRect            m_rectSmall;			    // ��С�Ի���Ĵ�С
    CRect            m_rectSeparatorVertical;   // ��ֱ�ָ���
	CRect            m_rectSeparatorHorizontal; // ˮƽ�ָ���
	bool			 m_isShowMidWnd;			// �Ƿ���ʾ�еȶԻ����С
	bool			 m_isShowLargeWnd;			// �Ƿ���ʾ�����Ի����С
	CTreeCtrl		 m_treeCtrl;				// ѡ����������ؼ�
	CListCtrl		 m_listCtrl;				// ��Ա�б�ؼ�
	CStatic			 m_pictureCtrl;				// ��Աͷ����ʾ�ؼ�

	CPlayerLibHandler* m_pPlayerLibHandler;		// ��Ա��Ϣ����

	CFont*   m_pFont; 
	LOGFONT   m_lf;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedPlayerLibTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkPlayerLibList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
