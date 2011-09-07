// PlayerSearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PesXp.h"
#include "PlayerSearchDlg.h"


// CPlayerSearchDlg dialog

IMPLEMENT_DYNAMIC(CPlayerSearchDlg, CDialog)

CPlayerSearchDlg::CPlayerSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayerSearchDlg::IDD, pParent)
{
	m_pPlayerLibHandler = NULL;
}

CPlayerSearchDlg::~CPlayerSearchDlg()
{
}

void CPlayerSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_NAME, m_chkName);
	DDX_Control(pDX, IDC_CHECK_WE_NAME, m_chkWeName);
	DDX_Control(pDX, IDC_CHECK_COUNTRY, m_chkCountry);
	DDX_Control(pDX, IDC_CHECK_CLUB, m_chkClub);
	DDX_Control(pDX, IDC_CHECK_POS, m_chkPos);
	DDX_Control(pDX, IDC_CHECK_HEIGHT, m_chkHeight);
	DDX_Control(pDX, IDC_CHECK_WEIGHT, m_chkWeight);
	DDX_Control(pDX, IDC_CHECK_BIRTH, m_chkBirth);
	DDX_Control(pDX, IDC_CHECK_CONS, m_chkCons);
	DDX_Control(pDX, IDC_CHECK_AGE, m_chkAge);
	DDX_Control(pDX, IDC_CHECK_FOOT, m_chkFoot);
	DDX_Control(pDX, IDC_CHECK_VALUE, m_chkValue);
	DDX_Control(pDX, IDC_EDIT_NAME, m_textName);
	DDX_Control(pDX, IDC_EDIT_WE_NAME, m_textWeName);
	DDX_Control(pDX, IDC_COMBO_CONTINET, m_cmbContinet);
	DDX_Control(pDX, IDC_COMBO_COUNTRY, m_cmbCountry);
	DDX_Control(pDX, IDC_COMBO_CONTIENT_CLUB, m_cmbContinetClub);
	DDX_Control(pDX, IDC_COMBO_CLUB, m_cmbClub);
	DDX_Control(pDX, IDC_COMBO_POS, m_cmbPos);
	DDX_Control(pDX, IDC_COMBO_FOOT_SIDE, m_cmbSide);
	DDX_Control(pDX, IDC_SPIN_HEIGHT_MIN, m_spHeightMin);
	DDX_Control(pDX, IDC_SPIN_HEIGHT_MAX, m_spHeightMax);
	DDX_Control(pDX, IDC_SPIN_WEIGHT_MIN, m_spWeightMin);
	DDX_Control(pDX, IDC_SPIN_WEIGHT_MAX, m_spWeightMax);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BIRTH, m_dateBirth);
	DDX_Control(pDX, IDC_COMBO_CONS, m_cmbCons);
	DDX_Control(pDX, IDC_SPIN_AGE_MIN, m_spAgeMin);
	DDX_Control(pDX, IDC_SPIN_AGE_MAX, m_spAgeMax);
	DDX_Control(pDX, IDC_COMBO_FOOT, m_cmbFoot);
	DDX_Control(pDX, IDC_SPIN_VALUE_MIN, m_spValueMin);
	DDX_Control(pDX, IDC_SPIN_VALUE_MAX, m_spValueMax);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_MIN, m_textHeightMin);
	DDX_Control(pDX, IDC_EDIT_HEIGHT_MAX, m_textHeightMax);
	DDX_Control(pDX, IDC_EDIT_WEIGHT_MIN, m_textWeightMin);
	DDX_Control(pDX, IDC_EDITIDC_EDIT_WEIGHT_MAX, m_textWeightMax);
	DDX_Control(pDX, IDC_EDITIDC_EDIT_AGE_MIN, m_textAgeMin);
	DDX_Control(pDX, IDC_EDITIDC_EDITIDC_EDIT_AGE_MAX, m_textAgeMax);
	DDX_Control(pDX, IDC_EDITIDC_EDITIDC_EDIT_VALUE_MIN, m_textValueMin);
	DDX_Control(pDX, IDC_EDITIDC_EDITIDC_EDIT_VALUE_MAX, m_textValueMax);
	DDX_Control(pDX, IDC_CHECK_SIDE, m_chkSide);
}


BEGIN_MESSAGE_MAP(CPlayerSearchDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_NAME, &CPlayerSearchDlg::OnBnClickedCheckName)
	ON_BN_CLICKED(IDC_CHECK_WE_NAME, &CPlayerSearchDlg::OnBnClickedCheckWeName)
	ON_BN_CLICKED(IDC_CHECK_COUNTRY, &CPlayerSearchDlg::OnBnClickedCheckCountry)
	ON_BN_CLICKED(IDC_CHECK_CLUB, &CPlayerSearchDlg::OnBnClickedCheckClub)
	ON_BN_CLICKED(IDC_CHECK_POS, &CPlayerSearchDlg::OnBnClickedCheckPos)
	ON_BN_CLICKED(IDC_CHECK_HEIGHT, &CPlayerSearchDlg::OnBnClickedCheckHeight)
	ON_BN_CLICKED(IDC_CHECK_WEIGHT, &CPlayerSearchDlg::OnBnClickedCheckWeight)
	ON_BN_CLICKED(IDC_CHECK_BIRTH, &CPlayerSearchDlg::OnBnClickedCheckBirth)
	ON_BN_CLICKED(IDC_CHECK_CONS, &CPlayerSearchDlg::OnBnClickedCheckCons)
	ON_BN_CLICKED(IDC_CHECK_AGE, &CPlayerSearchDlg::OnBnClickedCheckAge)
	ON_BN_CLICKED(IDC_CHECK_FOOT, &CPlayerSearchDlg::OnBnClickedCheckFoot)
	ON_BN_CLICKED(IDC_CHECK_VALUE, &CPlayerSearchDlg::OnBnClickedCheckValue)
	ON_BN_CLICKED(IDC_CHECK_SIDE, &CPlayerSearchDlg::OnBnClickedCheckSide)
	ON_CBN_SELCHANGE(IDC_COMBO_CONTINET, &CPlayerSearchDlg::OnCbnSelchangeComboContinet)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CPlayerSearchDlg::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// CPlayerSearchDlg message handlers

BOOL CPlayerSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_textName.EnableWindow(FALSE);
	m_textWeName.EnableWindow(FALSE);
	m_cmbContinet.EnableWindow(FALSE);
	m_cmbCountry.EnableWindow(FALSE);
	m_cmbContinetClub.EnableWindow(FALSE);
	m_cmbClub.EnableWindow(FALSE);
	m_cmbPos.EnableWindow(FALSE);
	m_spHeightMin.EnableWindow(FALSE);
	m_spHeightMax.EnableWindow(FALSE);
	m_spWeightMin.EnableWindow(FALSE);
	m_spWeightMax.EnableWindow(FALSE);
	m_dateBirth.EnableWindow(FALSE);
	m_cmbCons.EnableWindow(FALSE);
	m_cmbSide.EnableWindow(FALSE);
	m_spAgeMin.EnableWindow(FALSE);
	m_spAgeMax.EnableWindow(FALSE);
	m_cmbFoot.EnableWindow(FALSE);
	m_spValueMin.EnableWindow(FALSE);
	m_spValueMax.EnableWindow(FALSE);
	m_textHeightMin.EnableWindow(FALSE);
	m_textHeightMax.EnableWindow(FALSE);
	m_textWeightMin.EnableWindow(FALSE);
	m_textWeightMax.EnableWindow(FALSE);
	m_textAgeMin.EnableWindow(FALSE);
	m_textAgeMax.EnableWindow(FALSE);
	m_textValueMin.EnableWindow(FALSE);
	m_textValueMax.EnableWindow(FALSE);

	m_cmbContinet.SetWindowText(_T("请选择"));
	m_cmbCountry.SetWindowText(_T("请选择"));
	m_cmbContinetClub.SetWindowText(_T("请选择"));
	m_cmbClub.SetWindowText(_T("请选择"));
	m_cmbPos.SetWindowText(_T("请选择"));
	m_cmbCons.SetWindowText(_T("请选择"));
	m_cmbFoot.SetWindowText(_T("请选择"));
	m_cmbSide.SetWindowText(_T("请选择"));

	m_textAgeMin.SetWindowText(_T("15"));
	m_textAgeMax.SetWindowText(_T("50"));
	m_spAgeMin.SetRange(15, 50);
	m_spAgeMax.SetRange(15, 50);
	
	m_textHeightMin.SetWindowText(_T("140"));
	m_textHeightMax.SetWindowText(_T("230"));
	m_spHeightMin.SetRange(140, 230);
	m_spHeightMax.SetRange(140, 230);
	
	m_textWeightMin.SetWindowText(_T("40"));
	m_textWeightMax.SetWindowText(_T("120"));
	m_spWeightMin.SetRange(40, 120);
	m_spWeightMax.SetRange(40, 120);
	
	m_textValueMin.SetWindowText(_T("1"));
	m_textValueMax.SetWindowText(_T("100"));
	m_spValueMin.SetRange(1, 100);
	m_spValueMax.SetRange(1, 100);

	initCmbContinetCountry();
	initCmbContinetClub();
	initCmbCountry();
	initCmbClub();
	initCmbPos();
	initCmbFoot();
	initCmbSide();
	initCmbCons();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPlayerSearchDlg::initCmbContinetCountry()
{
	m_cmbContinet.InsertString(0, _T("欧洲"));
	m_cmbContinet.InsertString(1, _T("非洲"));
	m_cmbContinet.InsertString(2, _T("北、中、南美洲"));
	m_cmbContinet.InsertString(3, _T("亚洲、大洋洲"));
}

void CPlayerSearchDlg::initCmbContinetClub()
{
	m_cmbContinetClub.InsertString(0, _T("英超联赛"));
	m_cmbContinetClub.InsertString(1, _T("法甲联赛"));
	m_cmbContinetClub.InsertString(2, _T("意甲联赛"));
	m_cmbContinetClub.InsertString(3, _T("荷甲联赛"));
	m_cmbContinetClub.InsertString(4, _T("西甲联赛"));
	m_cmbContinetClub.InsertString(5, _T("其他联赛"));
	m_cmbContinetClub.InsertString(6, _T("解放者杯"));
}

void CPlayerSearchDlg::initCmbCountry()
{
}

void CPlayerSearchDlg::initCmbClub()
{

}

void CPlayerSearchDlg::initCmbPos()
{
	m_cmbPos.InsertString(0, _T("GK"));
	m_cmbPos.InsertString(1, _T("SB"));
	m_cmbPos.InsertString(2, _T("CB"));
	m_cmbPos.InsertString(3, _T("LB"));
	m_cmbPos.InsertString(4, _T("RB"));
	m_cmbPos.InsertString(5, _T("CWP"));
	m_cmbPos.InsertString(6, _T("AMF"));
	m_cmbPos.InsertString(7, _T("SMF"));
	m_cmbPos.InsertString(8, _T("CMF"));
	m_cmbPos.InsertString(9, _T("WB"));
	m_cmbPos.InsertString(10, _T("DMF"));
	m_cmbPos.InsertString(11, _T("LMF"));
	m_cmbPos.InsertString(12, _T("RMF"));
	m_cmbPos.InsertString(13, _T("LWB"));
	m_cmbPos.InsertString(14, _T("RWB"));
	m_cmbPos.InsertString(15, _T("LWF"));
	m_cmbPos.InsertString(16, _T("RWF"));
	m_cmbPos.InsertString(17, _T("CF"));
	m_cmbPos.InsertString(18, _T("WF"));
	m_cmbPos.InsertString(19, _T("SS"));
}

void CPlayerSearchDlg::initCmbFoot()
{
	m_cmbFoot.InsertString(0, _T("左脚"));
	m_cmbFoot.InsertString(1, _T("右脚"));
}

void CPlayerSearchDlg::initCmbSide()
{
	m_cmbSide.InsertString(0, _T("两边"));
	m_cmbSide.InsertString(1, _T("左边"));
	m_cmbSide.InsertString(2, _T("右边"));
}

void CPlayerSearchDlg::initCmbCons()
{
	m_cmbCons.InsertString(0, _T("白羊座"));
	m_cmbCons.InsertString(1, _T("金牛座"));
	m_cmbCons.InsertString(2, _T("双子座"));
	m_cmbCons.InsertString(3, _T("巨蟹座"));
	m_cmbCons.InsertString(4, _T("狮子座"));
	m_cmbCons.InsertString(5, _T("处女座"));
	m_cmbCons.InsertString(6, _T("天秤座"));
	m_cmbCons.InsertString(7, _T("天蝎座"));
	m_cmbCons.InsertString(8, _T("射手座"));
	m_cmbCons.InsertString(9, _T("摩羯座"));
	m_cmbCons.InsertString(10, _T("水瓶座"));
	m_cmbCons.InsertString(11, _T("双鱼座"));
}

void CPlayerSearchDlg::OnBnClickedCheckName()
{
	// TODO: Add your control notification handler code here
	if (m_chkName.GetCheck())
	{
		m_textName.EnableWindow(TRUE);
	}
	else {
		m_textName.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::OnBnClickedCheckWeName()
{
	// TODO: Add your control notification handler code here
	if (m_chkWeName.GetCheck())
	{
		m_textWeName.EnableWindow(TRUE);
	}
	else {
		m_textWeName.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::OnBnClickedCheckCountry()
{
	// TODO: Add your control notification handler code here
	if (m_chkCountry.GetCheck())
	{
		m_cmbContinet.EnableWindow(TRUE);
		m_cmbCountry.EnableWindow(TRUE);
	}
	else {
		m_cmbContinet.EnableWindow(FALSE);
		m_cmbCountry.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::OnBnClickedCheckClub()
{
	// TODO: Add your control notification handler code here
	if (m_chkClub.GetCheck())
	{
		m_cmbContinetClub.EnableWindow(TRUE);
		m_cmbClub.EnableWindow(TRUE);
	}
	else {
		m_cmbContinetClub.EnableWindow(FALSE);
		m_cmbClub.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::OnBnClickedCheckPos()
{
	// TODO: Add your control notification handler code here
	if (m_chkPos.GetCheck())
	{
		m_cmbPos.EnableWindow(TRUE);
	}
	else {
		m_cmbPos.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::OnBnClickedCheckHeight()
{
	// TODO: Add your control notification handler code here
	if (m_chkHeight.GetCheck())
	{
		m_textHeightMin.EnableWindow(TRUE);
		m_spHeightMin.EnableWindow(TRUE);
		m_textHeightMax.EnableWindow(TRUE);
		m_spHeightMax.EnableWindow(TRUE);
	}
	else {
		m_textHeightMin.EnableWindow(FALSE);
		m_spHeightMin.EnableWindow(FALSE);
		m_textHeightMax.EnableWindow(FALSE);
		m_spHeightMax.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::OnBnClickedCheckWeight()
{
	// TODO: Add your control notification handler code here
	if (m_chkWeight.GetCheck())
	{
		m_textWeightMin.EnableWindow(TRUE);
		m_spWeightMin.EnableWindow(TRUE);
		m_textWeightMax.EnableWindow(TRUE);
		m_spWeightMax.EnableWindow(TRUE);
	}
	else {
		m_textWeightMin.EnableWindow(FALSE);
		m_spWeightMin.EnableWindow(FALSE);
		m_textWeightMax.EnableWindow(FALSE);
		m_spWeightMax.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::OnBnClickedCheckBirth()
{
	// TODO: Add your control notification handler code here
	if (m_chkBirth.GetCheck())
	{
		m_dateBirth.EnableWindow(TRUE);
	}
	else {
		m_dateBirth.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::OnBnClickedCheckCons()
{
	// TODO: Add your control notification handler code here
	if (m_chkCons.GetCheck())
	{
		m_cmbCons.EnableWindow(TRUE);
	}
	else {
		m_cmbCons.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::OnBnClickedCheckAge()
{
	// TODO: Add your control notification handler code here
	if (m_chkAge.GetCheck())
	{
		m_textAgeMin.EnableWindow(TRUE);
		m_spAgeMin.EnableWindow(TRUE);
		m_textAgeMax.EnableWindow(TRUE);
		m_spAgeMax.EnableWindow(TRUE);
	}
	else {
		m_textAgeMin.EnableWindow(FALSE);
		m_spAgeMin.EnableWindow(FALSE);
		m_textAgeMax.EnableWindow(FALSE);
		m_spAgeMax.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::OnBnClickedCheckFoot()
{
	// TODO: Add your control notification handler code here
	if (m_chkFoot.GetCheck())
	{
		m_cmbFoot.EnableWindow(TRUE);
	}
	else {
		m_cmbFoot.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::OnBnClickedCheckValue()
{
	// TODO: Add your control notification handler code here
	if (m_chkValue.GetCheck())
	{
		m_textValueMin.EnableWindow(TRUE);
		m_spValueMin.EnableWindow(TRUE);
		m_textValueMax.EnableWindow(TRUE);
		m_spValueMax.EnableWindow(TRUE);
	}
	else {
		m_textValueMin.EnableWindow(FALSE);
		m_spValueMin.EnableWindow(FALSE);
		m_textValueMax.EnableWindow(FALSE);
		m_spValueMax.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::OnBnClickedCheckSide()
{
	// TODO: Add your control notification handler code here
	if (m_chkSide.GetCheck())
	{
		m_cmbSide.EnableWindow(TRUE);
	}
	else {
		m_cmbSide.EnableWindow(FALSE);
	}
}

void CPlayerSearchDlg::setPlayerLibHandler(CPlayerLibHandler* pPlayerLibHandler)
{
	m_pPlayerLibHandler = pPlayerLibHandler;
}
void CPlayerSearchDlg::OnCbnSelchangeComboContinet()
{
	// TODO: Add your control notification handler code here
	m_cmbCountry.ResetContent();
	m_cmbCountry.SetWindowText(_T("请选择"));

	CString continet_name;
	m_cmbContinet.GetLBText(m_cmbContinet.GetCurSel(), continet_name);
	map<string, vector<string> >::iterator it = m_pPlayerLibHandler->m_team_dict.find(continet_name.GetBuffer());
	int team_count = it->second.size();

	for (int i = 0; i < team_count; i++)
	{
		m_cmbCountry.InsertString(i, (it->second)[i].c_str());
	}
}

void CPlayerSearchDlg::OnBnClickedButtonSearch()
{
	// TODO: Add your control notification handler code here
	const char* name	= NULL;
	const char* we_name = NULL;
	const char* country = NULL;
	const char* club	= NULL;
	const char* pos		= NULL;
	const char* birth	= NULL;
	const char* cons	= NULL;
	const char* foot	= NULL;
	const char* side	= NULL;
	int age_min			= 0;
	int age_max			= 0;
	int height_min		= 0;
	int height_max		= 0;
	int weight_min		= 0;
	int weight_max		= 0;
	int value_min		= 0;
	int value_max		= 0;

	CString strName;
	CString strWeName;
	CString strCountry;
	CString strClub;
	CString strBirth;
	CString strPos;
	CString strCons;
	CString strFoot;
	CString strSide;

	if (m_chkName.GetCheck())
	{
		m_textName.GetWindowText(strName);
		name = strName.GetBuffer();
	}

	if (m_chkWeName.GetCheck())
	{
		m_textWeName.GetWindowText(strWeName);
		we_name = strWeName.GetBuffer();
	}

	if (m_chkCountry.GetCheck())
	{
		m_cmbCountry.GetLBText(m_cmbCountry.GetCurSel(), strCountry);
		country = strCountry.GetBuffer();
	}

	if (m_chkClub.GetCheck())
	{
		m_cmbClub.GetLBText(m_cmbClub.GetCurSel(), strClub);
		club = strClub.GetBuffer();
	}

	if (m_chkPos.GetCheck())
	{
		m_cmbPos.GetLBText(m_cmbPos.GetCurSel(), strPos);
		pos = strPos.GetBuffer();
	}

	if (m_chkBirth.GetCheck())
	{
		CTime timeBirth;
		m_dateBirth.GetTime(timeBirth);
		int month = timeBirth.GetMonth();
		int day = timeBirth.GetDay();
		strBirth.Format(_T("%d月%d日"), month, day);
		birth = strBirth.GetBuffer();
	}

	if (m_chkCons.GetCheck())
	{
		m_cmbCons.GetLBText(m_cmbCons.GetCurSel(), strCons);
		cons = strCons.GetBuffer();
	}

	if (m_chkFoot.GetCheck())
	{
		m_cmbFoot.GetLBText(m_cmbFoot.GetCurSel(), strFoot);
		foot = strFoot.GetBuffer();
	}

	if (m_chkSide.GetCheck())
	{
		m_cmbSide.GetLBText(m_cmbSide.GetCurSel(), strSide);
		side = strSide.GetBuffer();
	}

	if (m_chkAge.GetCheck())
	{
		age_min = m_spAgeMin.GetPos();
		age_max = m_spAgeMax.GetPos();

		//
		// 不合法
		//
		if (age_min > age_max)
		{
			return;
		}
	}

	if (m_chkHeight.GetCheck())
	{
		height_min = m_spHeightMin.GetPos();
		height_max = m_spHeightMax.GetPos();

		//
		// 不合法
		//
		if (height_min > height_max)
		{
			return;
		}
	}

	if (m_chkWeight.GetCheck())
	{
		weight_min = m_spWeightMin.GetPos();
		weight_max = m_spWeightMax.GetPos();

		//
		// 不合法
		//
		if (weight_min > weight_max)
		{
			return;
		}
	}

	if (m_chkValue.GetCheck())
	{
		value_min = m_spValueMin.GetPos();
		value_max = m_spValueMax.GetPos();

		//
		// 不合法
		//
		if (value_min > value_max)
		{
			return;
		}
	}

	m_pPlayerLibHandler->getPlayerListByCustom(name = name,
											   we_name = we_name,
											   country = country,
											   club = club,
											   pos = pos,
											   birth = birth,
											   cons = cons,
											   foot = foot,
											   side = side,
											   age_min = age_min,
											   age_max = age_max,
											   height_min = height_min,
											   height_max = height_max,
											   weight_min = weight_min,
											   weight_max = weight_max,
											   value_min = value_min,
											   value_max = value_max);
	OnOK();
}
