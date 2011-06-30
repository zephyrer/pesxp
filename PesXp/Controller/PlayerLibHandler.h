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

	CPlayerLibHandler(CTreeCtrl*, CListCtrl*, CStatic*);

    bool initContinents();
	bool initTeams();
	bool initPlayers();
	bool initDB();
	bool getPlayerListByTeamName(const char* team);
	bool getPlayerDetail(const char* name, const char* club);

    CTreeCtrl* m_pTreeCtrl;
	CListCtrl* m_pListCtrl;
	CStatic* m_pPictureCtrl;
	 
	vector<pair<int, HTREEITEM> > m_continent_list;
	vector<pair<string, string> > m_player_list;
	sqlite3 * m_pDb;

	HTREEITEM m_pSubItem;

};
