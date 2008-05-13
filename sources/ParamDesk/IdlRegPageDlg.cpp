 /****************************************************************
 *       SECU-3  - An open source, free engine control unit
 *    Designed by Alexey A. Shabelnikov. Ukraine, Gorlovka 2007.
 *       Microprocessors systems - design & programming.
 *    contacts:
 *              http://secu-3.narod.ru
 *              ICQ: 405-791-931
 ****************************************************************/

#include "stdafx.h"
#include "IdlRegPageDlg.h"
#include "ui-core/ddx_helpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CIdlRegPageDlg::CIdlRegPageDlg(CWnd* pParent /*=NULL*/)
	: CTabDialog(CIdlRegPageDlg::IDD, pParent)
	, m_enabled(FALSE)
{
	m_params.ifac1 = 1.0f;
	m_params.ifac2 = 1.0f;
	m_params.MINEFR = 10;
	m_params.idl_turns = 850;
	m_params.idl_regul = 0;
	//{{AFX_DATA_INIT(CIdlRegPageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

LPCTSTR CIdlRegPageDlg::GetDialogID(void) const
{
	return (LPCTSTR)IDD; 
}

void CIdlRegPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIdlRegPageDlg)
	DDX_Control(pDX, IDC_PD_IDLREG_USE_REGULATOR, m_use_regulator);
	DDX_Control(pDX, IDC_PD_IDLREG_GOAL_RPM_SPIN, m_goal_rpm_spin);
	DDX_Control(pDX, IDC_PD_IDLREG_GOAL_RPM_EDIT, m_goal_rpm_edit);
	DDX_Control(pDX, IDC_PD_IDLREG_FACTOR_POS_SPIN, m_factor_pos_spin);
	DDX_Control(pDX, IDC_PD_IDLREG_FACTOR_POS_EDIT, m_factor_pos_edit);
	DDX_Control(pDX, IDC_PD_IDLREG_FACTOR_NEG_SPIN, m_factor_neg_spin);
	DDX_Control(pDX, IDC_PD_IDLREG_FACTOR_NEG_EDIT, m_factor_neg_edit);
	DDX_Control(pDX, IDC_PD_IDLREG_DEAD_BAND_RPM_SPIN, m_dead_band_rpm_spin);
	DDX_Control(pDX, IDC_PD_IDLREG_DEAD_BAND_RPM_EDIT, m_dead_band_rpm_edit);
	//}}AFX_DATA_MAP

    m_factor_pos_edit.DDX_Value(pDX, IDC_PD_IDLREG_FACTOR_POS_EDIT, m_params.ifac1);
	m_factor_neg_edit.DDX_Value(pDX, IDC_PD_IDLREG_FACTOR_NEG_EDIT, m_params.ifac2);   
	DDX_Text(pDX, IDC_PD_IDLREG_GOAL_RPM_EDIT, m_params.idl_turns);
	DDX_Text(pDX, IDC_PD_IDLREG_DEAD_BAND_RPM_EDIT, m_params.MINEFR);
	DDX_Check_UCHAR(pDX, IDC_PD_IDLREG_USE_REGULATOR, m_params.idl_regul);
}


BEGIN_MESSAGE_MAP(CIdlRegPageDlg, CDialog)
	//{{AFX_MSG_MAP(CIdlRegPageDlg)
	ON_EN_CHANGE(IDC_PD_IDLREG_DEAD_BAND_RPM_EDIT, OnChangePdIdlregDeadBandRpmEdit)
	ON_EN_CHANGE(IDC_PD_IDLREG_FACTOR_NEG_EDIT, OnChangePdIdlregFactorNegEdit)
	ON_EN_CHANGE(IDC_PD_IDLREG_FACTOR_POS_EDIT, OnChangePdIdlregFactorPosEdit)
	ON_EN_CHANGE(IDC_PD_IDLREG_GOAL_RPM_EDIT, OnChangePdIdlregGoalRpmEdit)
	ON_BN_CLICKED(IDC_PD_IDLREG_USE_REGULATOR, OnPdIdlregUseRegulator)

	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_FACTORS_CAPTION,OnUpdateControls)

	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_FACTOR_POS_EDIT,OnUpdateControls)
	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_FACTOR_POS_SPIN,OnUpdateControls)
	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_FACTOR_POS_CAPTION,OnUpdateControls)

	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_FACTOR_NEG_EDIT,OnUpdateControls)
	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_FACTOR_NEG_SPIN,OnUpdateControls)
	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_FACTOR_NEG_CAPTION,OnUpdateControls)

	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_GOAL_RPM_EDIT,OnUpdateControls)
	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_GOAL_RPM_SPIN,OnUpdateControls)
	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_GOAL_RPM_CAPTION,OnUpdateControls)
	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_GOAL_RPM_UNIT,OnUpdateControls)

	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_DEAD_BAND_RPM_EDIT,OnUpdateControls)
	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_DEAD_BAND_RPM_SPIN,OnUpdateControls)
	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_DEAD_BAND_RPM_CAPTION,OnUpdateControls)
	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_DEAD_BAND_RPM_UNIT,OnUpdateControls)

	ON_UPDATE_COMMAND_UI(IDC_PD_IDLREG_USE_REGULATOR,OnUpdateControls)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIdlRegPageDlg message handlers

//���� ���� ��������� ��������� ���������, �� ���� ����� ������� �������
void CIdlRegPageDlg::OnUpdateControls(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(m_enabled);
}

BOOL CIdlRegPageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_factor_pos_spin.SetBuddy(&m_factor_pos_edit);
	m_factor_pos_edit.SetLimitText(5);
    m_factor_pos_edit.SetDecimalPlaces(2);
    m_factor_pos_edit.SetMode(CEditEx::MODE_FLOAT);
    m_factor_pos_spin.SetRangeAndDelta(0.0f,10.0f,0.01f);

	m_factor_neg_spin.SetBuddy(&m_factor_neg_edit);
	m_factor_neg_edit.SetLimitText(5);
    m_factor_neg_edit.SetDecimalPlaces(2);
    m_factor_neg_edit.SetMode(CEditEx::MODE_FLOAT);
    m_factor_neg_spin.SetRangeAndDelta(0.0f,10.0f,0.01f);

	m_dead_band_rpm_edit.SetLimitText(3);
	m_dead_band_rpm_spin.SetBuddy(&m_dead_band_rpm_edit);
	m_dead_band_rpm_spin.SetRangeAndDelta(0,500,1);

	m_goal_rpm_edit.SetLimitText(3);
	m_goal_rpm_spin.SetBuddy(&m_goal_rpm_edit);
    m_goal_rpm_spin.SetRangeAndDelta(250,1800,5);
	
	UpdateData(FALSE);
    UpdateDialogControls(this,TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIdlRegPageDlg::OnChangePdIdlregDeadBandRpmEdit() 
{
  UpdateData();	
  OnChangeNotify(); //notify event receiver about change of view content(see class ParamPageEvents)  		  
}

void CIdlRegPageDlg::OnChangePdIdlregFactorNegEdit() 
{
  UpdateData();	
  OnChangeNotify();   		  
}

void CIdlRegPageDlg::OnChangePdIdlregFactorPosEdit() 
{
  UpdateData();		
  OnChangeNotify();   		  
}

void CIdlRegPageDlg::OnChangePdIdlregGoalRpmEdit() 
{
  UpdateData();			
  OnChangeNotify();   		  
}

void CIdlRegPageDlg::OnPdIdlregUseRegulator() 
{
  UpdateData();				
  OnChangeNotify();   		  
}

//����������/���������� ���������� (���� ���������)
void CIdlRegPageDlg::Enable(bool enable)
{
  m_enabled = (enable) ? TRUE : FALSE;  
  if (::IsWindow(m_hWnd))
    UpdateDialogControls(this,TRUE);
}

//��� � �����������?
bool CIdlRegPageDlg::IsEnabled(void)
{
  return (m_enabled) ? true : false;
}

//��� ������� ���������� ������������ ����� ���� �������� ������ �� �������
void CIdlRegPageDlg::GetValues(SECU3IO::IdlRegPar* o_values)
{
  ASSERT(o_values);
  UpdateData(TRUE); //�������� ������ �� ������� � ����������
  memcpy(o_values,&m_params,sizeof(SECU3IO::IdlRegPar));
}

//��� ������� ���������� ������������ ����� ���� ������� ������ � ������
void CIdlRegPageDlg::SetValues(const SECU3IO::IdlRegPar* i_values)
{
  ASSERT(i_values);
  memcpy(&m_params,i_values,sizeof(SECU3IO::IdlRegPar));
  UpdateData(FALSE); //�������� ������ �� ���������� � ������
}