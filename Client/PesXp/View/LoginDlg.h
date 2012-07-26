// LoginDlg.h : ͷ�ļ�
//

#pragma once

#include "SyncHandler.h"
#include "UtilHandler.h"
#include "afxwin.h"
#include "PictureEx.h"

// CLoginDlg �Ի���
class CLoginDlg : public CDialog
{
// ����
public:
    CLoginDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
    enum { IDD = IDD_LOGIN_DIALOG };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
    HICON m_hIcon;

    // ���ɵ���Ϣӳ�亯��
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    //
    // ��Ӧ��½��ť�¼�
    //
    afx_msg void OnBnClickedLoginButtonLogin();
    //
    // ��Ӧע�ᰴť�¼�
    //
    afx_msg void OnBnClickedLoginButtonRegister();
    //
    // ��Ӧ�ύע�ᰴť�¼�
    //
    afx_msg void OnBnClickedLoginButtonSubmit();

private:
    CString         m_strLoginUserName;     // �û���½������û���
    CString         m_strLoginPassword;     // �û���½���������
    CString         m_strRegUserName;       // �û�ע��������û���
    CString         m_strRegPassword;       // �û�ע�����������
    CString         m_strConfirmPassword;   // �û������ȷ������
    CString         m_strQQ;                // �û������qq
    CString         m_strMail;              // �û�����������ַ

    bool            m_isLoginDlg;           // ��ǰ�Ƿ���ʾ��½�Ի���
    CRect           m_rectLogin;            // ��½�Ի���Ĵ�С
    CRect           m_rectRegister;         // ע��Ի���Ĵ�С
    CRect           m_rectSeparator;        // ��½��ע��ķָ���
    CUtilHandler   *m_utilHandler;          // ������
    CSyncHandler   *m_syncHandler;         // �����½/ע������߼�
public:
    CStatic m_staticTipInfo;
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnOK();
};
