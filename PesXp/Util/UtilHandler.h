#pragma once

class CUtilHandler
{
public:
    ~CUtilHandler(void);
    static CUtilHandler* GetInstance();
    bool IsValidEmail(CString);
	CString GetAppPath();
private:
    CUtilHandler(void);
    bool IsValidChar(TCHAR);
    static CUtilHandler* _instance;
};
