#pragma once
#include "afxwin.h"
#include "PictureEx.h"

// CWaitingDlg 对话框

class CWaitingDlg : public CDialog
{
    DECLARE_DYNAMIC(CWaitingDlg)

public:
    CWaitingDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CWaitingDlg();

// 对话框数据
    enum { IDD = IDD_WAITING_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
