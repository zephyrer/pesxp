#pragma once
#include "sqlite3.h"
#include <vector>
#include <map>
#include <string>
using namespace std;

class CPlayerLibHandler
{
public:
    CPlayerLibHandler(void);
    ~CPlayerLibHandler(void);

	CPlayerLibHandler(HWND, CTreeCtrl*, CListCtrl*, CStatic*);

    bool initContinents();
	bool initTeams();
	bool initPlayers();
	bool initDB();
	bool getPlayerListByTeamName(const char* team, bool club);
	bool getPlayerDetail(const char* name, const char* club);

    HWND m_playerLibHwnd;
    CTreeCtrl*           m_pTreeCtrl;                 // ѡ����������ؼ�
    CListCtrl*           m_pListCtrl;                 // ��Ա�б�ؼ�
    CStatic*             m_pPictureCtrl;              // ��Աͷ����ʾ�ؼ�
	 
	vector<pair<int, HTREEITEM> > m_continent_list;
	vector<pair<string, string> > m_player_list;
	sqlite3 * m_pDb;

	HTREEITEM m_pSubItem;

};
