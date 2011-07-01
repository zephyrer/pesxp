#include "StdAfx.h"
#include "PlayerLibHandler.h"
#include "atlimage.h"
#include <io.h>

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

//GB2312到UTF-8的转换
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
// 检查文件是否存在
//
bool file_exists(const char* file_path)
{
	return (access(file_path, 0) == 0);
}
//
// 查询数据库大洲信息回调函数
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
// 查询数据库球队信息回调函数
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
// 查询数据库球队信息回调函数
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
// 查询球员详细资料回调函数
//
static int _player_detail_callback(void * param, int argc, char ** argv, char ** szColName)
{	
	CPlayerLibHandler* pPlayerLibHandler = (CPlayerLibHandler*)param;
	CStatic* pPictureCtrl = pPlayerLibHandler->m_pPictureCtrl;

	string picture_path = ".\\Bin\\face\\";
	//string picture_path = "H:\\pesxp\\PesXp\\Bin\\face\\";
	picture_path += argv[0];
	//
	// 如果球员头像不存在则加载默认头像
	//
	if (!file_exists(picture_path.c_str()))
	{
		picture_path = ".\\Bin\\face\\default";
	}

	//
	// 加载球员头像
	//
	CImage img; 
	HRESULT ret = img.Load(picture_path.c_str()); 
	HBITMAP bitmap = img.Detach(); 
	pPictureCtrl->SetBitmap(bitmap);

	string name						= U2G(argv[2]);
	string default_position			= argv[3];
	string default_complex_value	= argv[4];
	string we_name					= argv[5];
	string country_position			= argv[6];
	string country_complex_value	= argv[7];
	string country					= U2G(argv[8]);
	string club_position			= argv[9];
	string club_complex_value		= argv[10];
	string country_team				= U2G(argv[11]);
	string club						= U2G(argv[12]);
	string birth					= U2G(argv[13]);
	string constellation			= U2G(argv[14]);
	string age						= argv[15];
	string hight					= argv[16];
	string weight					= argv[17];
	string favoured_side			= U2G(argv[18]);
	string foot						= U2G(argv[19]);
	string attack					= argv[20];
	string shot_power				= argv[21];
	string defend					= argv[22];
	string shot_skill				= argv[23];
	string balance					= argv[24];
	string free_kick_accuracy		= argv[25];
	string physical					= argv[26];
	string radian					= argv[27];
	string speed					= argv[28];
	string header					= argv[29];
	string speed_up					= argv[30];
	string bounce					= argv[31];
	string reaction					= argv[32];
	string skill					= argv[33];
	string agile					= argv[34];
	string offensive				= argv[35];
	string precision_ball			= argv[36];
	string spirit					= argv[37];
	string ball_speed				= argv[38];
	string gk_skill					= argv[39];
	string short_pass_accuracy		= argv[40];
	string assort					= argv[41];
	string short_pass_speed			= argv[42];
	string state_stability			= argv[43];
	string long_pass_accuracy		= argv[44];
	string weak_foot_accuracy		= argv[45];
	string long_pass_speed			= argv[46];
	string weak_foot_frequency		= argv[47];
	string shot_accuracy			= argv[48];
	string injured					= argv[49];
	string special_ability			= U2G(argv[50]);

	//
	// 加载球员具体属性
	//


	return 0;
}

bool CPlayerLibHandler::initDB()
{
	//
	// 连接数据库
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
// 初始化大洲信息
//
bool CPlayerLibHandler::initContinents()
{
	if (!initDB())
	{
		return false;
	}
	

    char * pErrMsg = 0;
    
	const char * sSQL3 = "select * from continents;";

	// 查询数据表
    sqlite3_exec( m_pDb, sSQL3, _continents_callback, this, &pErrMsg);

    return true;
}

//
// 初始化球队信息
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
		

		// 查询数据表
		sqlite3_exec( m_pDb, sql, _teams_callback, this, &pErrMsg);
	}

	return true;
}

bool CPlayerLibHandler::getPlayerListByTeamName(const char* team, bool club)
{
	if (!initDB())
	{
		return false;
	}

	m_pListCtrl->DeleteAllItems();
	m_player_list.clear();
	char * pErrMsg = 0;

	string team_type = "club";
	if (!club)
	{
		team_type = "country";
	}

	string sql = "select * from players where ";
	sql = sql + team_type + " = \"" + G2U(team) + "\";";

	// 查询数据表
	sqlite3_exec( m_pDb, sql.c_str(), _players_callback, this, &pErrMsg);

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

	// 查询数据表
	sqlite3_exec( m_pDb, sql, _player_detail_callback, this, &pErrMsg);

	return true;
}