#pragma once
#include "afxwin.h"
#include "PictureEx.h"
#include "resource.h"

typedef BOOL (WINAPI *SetTransparentFunc)(HWND,COLORREF,BYTE,DWORD);

// CWaitingDlg 对话框

class CWaitingDlg : public CDialog
{
    DECLARE_DYNAMIC(CWaitingDlg)

public:
    static CWaitingDlg* GetInstance();
    virtual ~CWaitingDlg();

// 对话框数据
    enum { IDD = IDD_WAITING_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    void BeginShowWaitingDlg(CDialog* pParent, LPCTSTR szMsg);
    void EndShowWaitingDlg();
    void PerformSelectorAndBeginWaitingDlg(CDialog* pParent, LPCTSTR szMsg, LPVOID selector, LPVOID params);
    void EndWaitingDlg();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:
    CWaitingDlg(CWnd* pParent = NULL);   // 标准构造函数
    static CWaitingDlg *_hInstance;
    CDialog *m_pParentDlg;
    SetTransparentFunc m_pSetTransparentFunc;
    AFX_THREADPROC m_pThreadFun;
    LPVOID m_pThreadFunParams;
    CDialog *m_pTransparentDlg;

protected:
    virtual void OnOK();
    virtual void OnCancel();
public:
    CPictureEx m_gifWaiting;
    CStatic m_textWaiting;
    CString m_szMessage;
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

//
// 等待提示对话框线程函数结构体
//
typedef struct {
    CWaitingDlg *pWaitingDlg;   // 信息提示对话框指针
    AFX_THREADPROC pThreadFun;  // 执行函数指针
    LPVOID pThreadFunParams;
} WaitingDlgThreadStruct, *LPWaitingDlgThreadStruct;