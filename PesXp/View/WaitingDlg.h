#pragma once
#include "afxwin.h"
#include "PictureEx.h"

// CWaitingDlg �Ի���

class CWaitingDlg : public CDialog
{
    DECLARE_DYNAMIC(CWaitingDlg)

public:
    CWaitingDlg(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~CWaitingDlg();

// �Ի�������
    enum { IDD = IDD_WAITING_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    void PerformSelectorAndBeginWaitingDlg(LPCTSTR szMsg, LPVOID selector, LPVOID params);
    void EndWaitingDlg();

private:
    CWnd *m_pParentWnd;
protected:
    virtual void OnOK();
    virtual void OnCancel();
public:
    CPictureEx m_gifWaiting;
    CStatic m_textWaiting;
    CString m_szMessage;
};
