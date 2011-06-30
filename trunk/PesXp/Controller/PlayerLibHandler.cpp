#include "StdAfx.h"
#include "PlayerLibHandler.h"
#include "atlimage.h"

#pragma comment(lib, ".\\Lib\\sqlite3\\lib\\sqlite3.lib");

CPlayerLibHandler::CPlayerLibHandler(void)
{
    m_pTreeCtrl = NULL;
	m_pDb = NULL;
	m_pSubItem = NULL;
}

CPlayerLibHandler::~CPlayerLibHandler(void)
{
}

CPlayerLibHandler::CPlayerLibHandler(CTreeCtrl* pTreeCtrl, CListCtrl* pListCtrl, CStatic* pPictureCtrl)
{
    m_pTreeCtrl		= pTreeCtrl;
	m_pListCtrl		= pListCtrl;
	m_pPictureCtrl	= pPictureCtrl;
	m_pDb			= NULL;
	m_pSubItem		= NULL;
}



char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}

//GB2312��UTF-8��ת��
char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}
//
// ��ѯ���ݿ������Ϣ�ص�����
//
static int _continents_callback(void * param, int argc, char ** argv, char ** szColName)
{	
	CPlayerLibHandler* pPlayerLibHandler = (CPlayerLibHandler*)param;
	CTreeCtrl* pTreeCtrl = pPlayerLibHandler->m_pTreeCtrl;
	
	
	HTREEITEM hItem;
	if (pPlayerLibHandler->m_continent_list.size() <= 0) {
		hItem = pTreeCtrl->InsertItem(U2G(argv[1]),0,1,TVI_ROOT);
		pTreeCtrl->Expand(hItem, TVE_EXPAND);
	}
	else {
		hItem = pPlayerLibHandler->m_continent_list[pPlayerLibHandler->m_continent_list.size() - 1].second;
		hItem = pTreeCtrl->InsertItem(U2G(argv[1]),0,1,TVI_ROOT,hItem);
	}
	pPlayerLibHandler->m_continent_list.push_back(make_pair(atoi(argv[0]), hItem));
	
    return 0;
}
//
// ��ѯ���ݿ������Ϣ�ص�����
//
static int _teams_callback(void * param, int argc, char ** argv, char ** szColName)
{	
	CPlayerLibHandler* pPlayerLibHandler = (CPlayerLibHandler*)param;
	CTreeCtrl* pTreeCtrl = pPlayerLibHandler->m_pTreeCtrl;


	HTREEITEM hItem, hSubItem;

	for (int i = 0; i < pPlayerLibHandler->m_continent_list.size(); i++)
	{
		if (pPlayerLibHandler->m_continent_list[i].first == atoi(argv[1]))
		{
			hItem = pPlayerLibHandler->m_continent_list[i].second;
		}
	}
	
	if (pPlayerLibHandler->m_pSubItem == NULL)
	{
		(pPlayerLibHandler->m_pSubItem) = pTreeCtrl->InsertItem(U2G(argv[2]),0,1,hItem);
	}
	else 
	{
		(pPlayerLibHandler->m_pSubItem) = pTreeCtrl->InsertItem(U2G(argv[2]),0,1,hItem, (pPlayerLibHandler->m_pSubItem));
	}
	

	return 0;
}

//
// ��ѯ���ݿ������Ϣ�ص�����
//
static int _players_callback(void * param, int argc, char ** argv, char ** szColName)
{	
	CPlayerLibHandler* pPlayerLibHandler = (CPlayerLibHandler*)param;
	CListCtrl* pListCtrl = pPlayerLibHandler->m_pListCtrl;

	int nRow = pListCtrl->InsertItem(0, U2G(argv[2]));
	pListCtrl->SetItemText(nRow, 1, U2G(argv[8]));
	pListCtrl->SetItemText(nRow, 2, U2G(argv[12]));
	pListCtrl->SetItemText(nRow, 3, U2G(argv[3]));
	pListCtrl->SetItemText(nRow, 4, U2G(argv[4]));

	pPlayerLibHandler->m_player_list.push_back(make_pair(U2G(argv[2]), U2G(argv[12])));

	return 0;
}

//
// ��ѯ��Ա��ϸ���ϻص�����
//
static int _player_detail_callback(void * param, int argc, char ** argv, char ** szColName)
{	
	CPlayerLibHandler* pPlayerLibHandler = (CPlayerLibHandler*)param;
	CStatic* pPictureCtrl = pPlayerLibHandler->m_pPictureCtrl;

	string picture_path = ".\\Bin\\face\\";
	picture_path += argv[0];


	CImage img; 
	HRESULT ret = img.Load(picture_path.c_str()); 
	HBITMAP bitmap = img.Detach(); 
	pPictureCtrl->SetBitmap(bitmap);

	return 0;
}

bool CPlayerLibHandler::initDB()
{
	//
	// �������ݿ�
	//
	if (m_pDb)
	{
		return true;
	}
	int ret = sqlite3_open("pesxp.db", &m_pDb);

	if ( ret != SQLITE_OK )
	{
		return false;
	}
	return true;
}

//
// ��ʼ��������Ϣ
//
bool CPlayerLibHandler::initContinents()
{
	if (!initDB())
	{
		return false;
	}
	

    char * pErrMsg = 0;
    
	const char * sSQL3 = "select * from continents;";

	// ��ѯ���ݱ�
    sqlite3_exec( m_pDb, sSQL3, _continents_callback, this, &pErrMsg);

    return true;
}

//
// ��ʼ�������Ϣ
//
bool CPlayerLibHandler::initTeams()
{
	if (!initDB())
	{
		return false;
	}


	char * pErrMsg = 0;
	const char* sSQL3 = "select * from teams where continent_id = ";

	for (int i = 0; i < m_continent_list.size(); i++)
	{

		char sql[255] = {0};
		char id[255] = {0};
		strcpy(sql, sSQL3);
		itoa(m_continent_list[i].first, id, 10);
		strcat(sql, id);
		strcat(sql, ";\"");
		

		// ��ѯ���ݱ�
		sqlite3_exec( m_pDb, sql, _teams_callback, this, &pErrMsg);
	}

	return true;
}

bool CPlayerLibHandler::getPlayerListByTeamName(const char* team)
{
	if (!initDB())
	{
		return false;
	}
	
	m_pListCtrl->DeleteAllItems();
	m_player_list.clear();
	char * pErrMsg = 0;
	char sql[255] = {0};
	const char* sSQL3 = "select * from players where country = \"";
	strcat(sql, sSQL3);
	strcat(sql, G2U(team));
	strcat(sql, "\";");

	// ��ѯ���ݱ�
	sqlite3_exec( m_pDb, sql, _players_callback, this, &pErrMsg);

	return true;
}

bool CPlayerLibHandler::getPlayerDetail(const char* name, const char* club)
{
	if (!initDB())
	{
		return false;
	}

	char * pErrMsg = 0;
	char sql[255] = {0};
	const char* sSQL3 = "select * from players where name = \"";
	strcat(sql, sSQL3);
	strcat(sql, G2U(name));
	strcat(sql, "\" and club = \"");
	strcat(sql, G2U(club));
	strcat(sql, "\";");

	// ��ѯ���ݱ�
	sqlite3_exec( m_pDb, sql, _player_detail_callback, this, &pErrMsg);

	return true;
}