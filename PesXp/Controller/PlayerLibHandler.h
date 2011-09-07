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

	CPlayerLibHandler(HWND, CTreeCtrl*, CListCtrl*, CStatic*, CToolTipCtrl*);

    bool initContinents();
	bool initTeams();
	bool initPlayers();
	bool initDB();
	bool getPlayerListByTeamName(const char* team, bool club);
	bool getPlayerDetail(const char* name, const char* club);
	bool getPlayerListByCustom(const char* name,
							   const char* we_name,
							   const char* country,
							   const char* club,
							   const char* pos,
							   const char* birth,
							   const char* cons,
							   const char* foot,
							   const char* side,
							   int age_min,
							   int age_max,
							   int height_min,
							   int height_max,
							   int weight_min,
							   int weight_max,
							   int value_min,
							   int value_max);

    HWND m_playerLibHwnd;
    CTreeCtrl*           m_pTreeCtrl;                 // ѡ����������ؼ�
    CListCtrl*           m_pListCtrl;                 // ��Ա�б�ؼ�
    CStatic*             m_pPictureCtrl;              // ��Աͷ����ʾ�ؼ�
	CToolTipCtrl*        m_pToolTipCtrl;			  // ��ʾ��Ϣ�ؼ�
	 
	vector<pair<int, HTREEITEM> > m_continent_list;
	vector<pair<string, string> > m_player_list;
	map<string, vector<string> >  m_team_dict;

	sqlite3 * m_pDb;	

	HTREEITEM m_pSubItem;

};
