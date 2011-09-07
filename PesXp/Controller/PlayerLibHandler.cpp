#include "StdAfx.h"
#include "PlayerLibHandler.h"
#include "atlimage.h"
#include "resource.h"
#include "UtilHandler.h"
#include <io.h>

#pragma comment(lib, ".\\Lib\\sqlite3\\lib\\sqlite3.lib");

CPlayerLibHandler::CPlayerLibHandler(void)
{
    m_pDb = NULL;
    m_pSubItem = NULL;
    m_pTreeCtrl     = NULL;
    m_pListCtrl     = NULL;
    m_pPictureCtrl  = NULL;
}

CPlayerLibHandler::~CPlayerLibHandler(void)
{
}

CPlayerLibHandler::CPlayerLibHandler(HWND hWnd, CTreeCtrl* pTreeCtrl, CListCtrl* pListCtrl, CStatic* pPictureCtrl, CToolTipCtrl* pToolTipCtrl)
{
    m_playerLibHwnd = hWnd;
    m_pDb			= NULL;
    m_pSubItem		= NULL;
    m_pTreeCtrl     = pTreeCtrl;
    m_pListCtrl     = pListCtrl;
    m_pPictureCtrl  = pPictureCtrl;
	m_pToolTipCtrl  = pToolTipCtrl;
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
	char* continent_name = U2G(argv[1]);
    if (pPlayerLibHandler->m_continent_list.size() <= 0) {
        hItem = pTreeCtrl->InsertItem(continent_name, 0, 1, TVI_ROOT);
        pTreeCtrl->Expand(hItem, TVE_EXPAND);
    }
    else {
        hItem = pPlayerLibHandler->m_continent_list[pPlayerLibHandler->m_continent_list.size() - 1].second;
        hItem = pTreeCtrl->InsertItem(continent_name, 0, 1, TVI_ROOT, hItem);
    }
    pPlayerLibHandler->m_continent_list.push_back(make_pair(atoi(argv[0]), hItem));
    
	delete [] continent_name;
    return 0;
}
//
// 查询数据库球队信息回调函数
//
static int _teams_callback(void * param, int argc, char ** argv, char ** szColName)
{	
    CPlayerLibHandler* pPlayerLibHandler = (CPlayerLibHandler*)param;
    CTreeCtrl* pTreeCtrl = pPlayerLibHandler->m_pTreeCtrl;
	map<string, vector<string> >* pTeamDict = &pPlayerLibHandler->m_team_dict;

    HTREEITEM hItem, hSubItem;

    for (int i = 0; i < pPlayerLibHandler->m_continent_list.size(); i++)
    {
        if (pPlayerLibHandler->m_continent_list[i].first == atoi(argv[1]))
        {
            hItem = pPlayerLibHandler->m_continent_list[i].second;
			break;
        }
    }

	string continet_name = pTreeCtrl->GetItemText(hItem);
	map<string, vector<string> >::iterator it = pTeamDict->find(continet_name);
	if(it == pTeamDict->end()) {
		vector<string> team_list;
		pTeamDict->insert(map<string, vector<string> >::value_type(continet_name, team_list));
	}
    
	char* team_name = U2G(argv[2]);
    if (pPlayerLibHandler->m_pSubItem == NULL)
    {
        (pPlayerLibHandler->m_pSubItem) = pTreeCtrl->InsertItem(team_name, 0, 1, hItem);
    }
    else 
    {
        (pPlayerLibHandler->m_pSubItem) = pTreeCtrl->InsertItem(team_name, 0, 1, hItem, (pPlayerLibHandler->m_pSubItem));
    }

	it = pTeamDict->find(continet_name);
	it->second.push_back(team_name);

	delete [] team_name;
    return 0;
}

//
// 查询数据库球队信息回调函数
//
static int _players_callback(void * param, int argc, char ** argv, char ** szColName)
{	
    CPlayerLibHandler* pPlayerLibHandler = (CPlayerLibHandler*)param;
    CListCtrl* pListCtrl = pPlayerLibHandler->m_pListCtrl;

	char* name    = U2G(argv[2]);
	char* country = U2G(argv[8]);
	char* club    = U2G(argv[12]);
	char* pos     = U2G(argv[3]);
	char* value   = U2G(argv[4]);
    int nRow = pListCtrl->InsertItem(0, name);
    pListCtrl->SetItemText(nRow, 1, country);
    pListCtrl->SetItemText(nRow, 2, club);
    pListCtrl->SetItemText(nRow, 3, pos);
    pListCtrl->SetItemText(nRow, 4, value);

    pPlayerLibHandler->m_player_list.push_back(make_pair(name, club));

	delete [] name;
	delete [] country;
	delete [] club;
	delete [] pos;
	delete [] value;
    return 0;
}

//
// 查询球员详细资料回调函数
//
static int _player_detail_callback(void * param, int argc, char ** argv, char ** szColName)
{
    CPlayerLibHandler* pPlayerLibHandler = (CPlayerLibHandler*)param;
    HWND playerLibHwnd = pPlayerLibHandler->m_playerLibHwnd;
    CStatic* pPictureCtrl = pPlayerLibHandler->m_pPictureCtrl;

	string picture_path = CUtilHandler::GetInstance()->GetAppPath() + "\\face\\";
    picture_path += argv[0];
    //
    // 如果球员头像不存在则加载默认头像
    //
    if (!file_exists(picture_path.c_str()))
    {
        picture_path =  CUtilHandler::GetInstance()->GetAppPath() + "\\face\\default";
    }

    //
    // 加载球员头像
    //
    CImage img; 
    HRESULT ret = img.Load(picture_path.c_str()); 
    HBITMAP bitmap = img.Detach(); 
    HBITMAP preBitmap = pPictureCtrl->SetBitmap(bitmap);
	if (preBitmap)
	{
		DeleteObject(preBitmap);
	}
	img.Destroy();

	char* c_name		 = U2G(argv[2]);
	char* c_country		 = U2G(argv[8]);
	char* c_country_team = U2G(argv[11]);
	char* c_club		 = U2G(argv[12]);
	char* c_birth		 = U2G(argv[13]);
	char* c_cons		 = U2G(argv[14]);
	char* c_side		 = U2G(argv[18]);
	char* c_foot		 = U2G(argv[19]);
	char* c_spec		 = U2G(argv[50]);

    string name                     = c_name;
    string default_position         = argv[3];
    string default_complex_value    = argv[4];
    string we_name                  = argv[5];
    string country_position         = argv[6];
    string country_complex_value    = argv[7];
    string country                  = c_country;
    string club_position            = argv[9];
    string club_complex_value       = argv[10];
    string country_team             = c_country_team;
    string club                     = c_club;
    string birth                    = c_birth;
    string constellation            = c_cons;
    string age                      = argv[15];
    string hight                    = argv[16];
    string weight                   = argv[17];
    string favoured_side			= c_side;
    string foot						= c_foot;
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
    string special_ability			= c_spec;

    //
    // 加载球员具体属性
    //
    SetDlgItemText(playerLibHwnd, IDC_STATIC_1, name.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_2, country.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_3, country_team.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_4, club.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_5, we_name.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_6, age.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_7, hight.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_8, weight.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_9, birth.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_10, constellation.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_11, default_position.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_12, default_complex_value.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_13, favoured_side.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_14, foot.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_15, attack.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_16, defend.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_17, balance.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_18, physical.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_19, speed.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_20, speed_up.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_21, reaction.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_22, agile.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_23, precision_ball.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_24, ball_speed.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_25, short_pass_accuracy.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_26, short_pass_speed.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_27, long_pass_accuracy.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_28, long_pass_speed.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_29, shot_accuracy.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_30, shot_power.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_31, shot_skill.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_32, free_kick_accuracy.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_33, radian.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_34, header.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_35, bounce.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_36, skill.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_37, offensive.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_38, spirit.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_39, gk_skill.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_40, assort.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_41, state_stability.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_42, weak_foot_accuracy.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_43, weak_foot_frequency.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_44, injured.c_str());
    SetDlgItemText(playerLibHwnd, IDC_STATIC_45, special_ability.c_str());

	pPlayerLibHandler->m_pToolTipCtrl->AddTool(CWnd::FromHandle(::GetDlgItem(playerLibHwnd, IDC_STATIC_1)), name.c_str());
	pPlayerLibHandler->m_pToolTipCtrl->AddTool(CWnd::FromHandle(::GetDlgItem(playerLibHwnd, IDC_STATIC_5)), we_name.c_str());
	pPlayerLibHandler->m_pToolTipCtrl->AddTool(CWnd::FromHandle(::GetDlgItem(playerLibHwnd, IDC_STATIC_45)), special_ability.c_str());

	delete [] c_name;
	delete [] c_country;
	delete [] c_country_team;
	delete [] c_club;
	delete [] c_birth;
	delete [] c_cons;
	delete [] c_side;
	delete [] c_foot;
	delete [] c_spec;
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

	m_pTreeCtrl->InsertItem(_T("自定义搜索"), 0, 1, m_pSubItem, m_pSubItem);

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
    const char* sql = "select * from teams where continent_id = ";
	CString strSql;

    for (int i = 0; i < m_continent_list.size(); i++)
    {
        // 查询数据表
		strSql.Format("%s%d", sql, m_continent_list[i].first);
        sqlite3_exec( m_pDb, strSql.GetBuffer(), _teams_callback, this, &pErrMsg);
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
	
	char* team_name = G2U(team);

    string sql = "select * from players where ";
    sql = sql + team_type + " = \"" + team_name + "\";";

    // 查询数据表
    sqlite3_exec( m_pDb, sql.c_str(), _players_callback, this, &pErrMsg);

	delete [] team_name;

    return true;
}

bool CPlayerLibHandler::getPlayerDetail(const char* name, const char* club)
{
    if (!initDB())
    {
        return false;
    }

    char * pErrMsg = 0;

	char* player_name = G2U(name);
	char* player_club = G2U(club);

    string sql = "select * from players where name = \"";
	sql += player_name;
	sql += "\" and club = \"";
	sql += player_club;
	sql += "\";";

    // 查询数据表
    sqlite3_exec( m_pDb, sql.c_str(), _player_detail_callback, this, &pErrMsg);

	delete [] player_name;
	delete [] player_club;

    return true;
}

bool CPlayerLibHandler::getPlayerListByCustom(const char* name = NULL,
											  const char* we_name = NULL,
											  const char* country = NULL,
											  const char* club = NULL,
											  const char* pos = NULL,
											  const char* birth = NULL,
											  const char* cons = NULL,
											  const char* foot = NULL,
											  const char* side = NULL,
											  int age_min = 0,
											  int age_max = 0,
											  int height_min = 0,
											  int height_max = 0,
											  int weight_min = 0,
											  int weight_max = 0,
											  int value_min = 0,
											  int value_max = 0)
{
	if (!initDB())
	{
		return false;
	}

	m_pListCtrl->DeleteAllItems();
	m_player_list.clear();
	char * pErrMsg = 0;

	char* c_name	= G2U(name);
	char* c_we_name = G2U(we_name);
	char* c_country = G2U(country);
	char* c_club	= G2U(club);
	char* c_pos		= G2U(pos);
	char* c_birth	= G2U(birth);
	char* c_cons	= G2U(cons);
	char* c_foot	= G2U(foot);
	char* c_side	= G2U(side);

	string condition = "";
	if (name)
	{
		condition += "name = \"";
		condition += c_name;
		condition += "\"";
	}

	if (we_name)
	{
		if (condition != "")
		{
			condition += " and ";
		}
		condition += "we_name = \"";
		condition += c_we_name;
		condition += "\"";
	}

	if (country)
	{
		if (condition != "")
		{
			condition += " and ";
		}
		condition += "country = \"";
		condition += c_country;
		condition += "\"";
	}

	if (club)
	{
		if (condition != "")
		{
			condition += " and ";
		}
		condition += "club = \"";
		condition += c_club;
		condition += "\"";
	}

	if (pos)
	{
		if (condition != "")
		{
			condition += " and ";
		}
		condition += "club_position = \"";
		condition += c_pos;
		condition += "\"";
	}

	if (birth)
	{
		if (condition != "")
		{
			condition += " and ";
		}
		condition += "birth = \"";
		condition += c_birth;
		condition += "\"";
	}

	if (cons)
	{
		if (condition != "")
		{
			condition += " and ";
		}
		condition += "constellation = \"";
		condition += c_cons;
		condition += "\"";
	}

	if (foot)
	{
		if (condition != "")
		{
			condition += " and ";
		}
		condition += "foot = \"";
		condition += c_foot;
		condition += "\"";
	}

	if (side)
	{
		if (condition != "")
		{
			condition += " and ";
		}
		condition += "favoured_side = \"";
		condition += c_side;
		condition += "\"";
	}

	if (age_min > 0 && age_max > 0 && age_min <= age_max)
	{
		if (condition != "")
		{
			condition += " and ";
		}
		CString strCondition;
		strCondition.Format("age >= %d and age <= %d", age_min, age_max);
		condition += strCondition;
	}

	if (height_min > 0 && height_max > 0 && height_min <= height_max)
	{
		if (condition != "")
		{
			condition += " and ";
		}
		CString strCondition;
		strCondition.Format("hight >= %d and hight <= %d", height_min, height_max);
		condition += strCondition;
	}

	if (weight_min > 0 && weight_max > 0 && weight_min <= weight_max)
	{
		if (condition != "")
		{
			condition += " and ";
		}
		CString strCondition;
		strCondition.Format("weight >= %d and weight <= %d", weight_min, weight_max);
		condition += strCondition;
	}

	if (value_min > 0 && value_max > 0 && value_min <= value_max)
	{
		if (condition != "")
		{
			condition += " and ";
		}
		CString strCondition;
		strCondition.Format("default_complex_value >= %d and default_complex_value <= %d", value_min, value_max);
		condition += strCondition;
	}

	string sql = "select * from players where ";
	sql += condition;


	// 查询数据表
	sqlite3_exec( m_pDb, sql.c_str(), _players_callback, this, &pErrMsg);

	delete c_name;
	delete c_we_name;
	delete c_country;
	delete c_club;
	delete c_pos;
	delete c_birth;
	delete c_cons;
	delete c_foot;
	delete c_side;

	return true;
}
