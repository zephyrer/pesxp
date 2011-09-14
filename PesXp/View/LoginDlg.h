// LoginDlg.h : 头文件
//

#pragma once

#include "SyncHandler.h"
#include "UtilHandler.h"
#include "afxwin.h"
#include "PictureEx.h"

// CLoginDlg 对话框
class CLoginDlg : public CDialog
{
// 构造
public:
    CLoginDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
    enum { IDD = IDD_LOGIN_DIALOG };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
    HICON m_hIcon;

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    //
    // 响应登陆按钮事件
    //
    afx_msg void OnBnClickedLoginButtonLogin();
    //
    // 响应注册按钮事件
    //
    afx_msg void OnBnClickedLoginButtonRegister();
    //
    // 响应提交注册按钮事件
    //
    afx_msg void OnBnClickedLoginButtonSubmit();

private:
    CString         m_strLoginUserName;     // 用户登陆输入的用户名
    CString         m_strLoginPassword;     // 用户登陆输入的密码
    CString         m_strRegUserName;       // 用户注册输入的用户名
    CString         m_strRegPassword;       // 用户注册输入的密码
    CString         m_strConfirmPassword;   // 用户输入的确认密码
    CString         m_strQQ;                // 用户输入的qq
    CString         m_strMail;              // 用户输入的邮箱地址

    bool            m_isLoginDlg;           // 当前是否显示登陆对话框
    CRect           m_rectLogin;            // 登陆对话框的大小
    CRect           m_rectRegister;         // 注册对话框的大小
    CRect           m_rectSeparator;        // 登陆与注册的分隔线
    CUtilHandler   *m_utilHandler;          // 工具类
    CSyncHandler   *m_syncHandler;         // 处理登陆/注册具体逻辑
public:
    CStatic m_staticTipInfo;
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnOK();
};
