 /****************************************************************
 *       SECU-3  - An open source, free engine control unit
 *    Designed by Alexey A. Shabelnikov. Ukraine, Gorlovka 2007.
 *       Microprocessors systems - design & programming.
 *    contacts:
 *              http://secu-3.narod.ru
 *              ICQ: 405-791-931
 ****************************************************************/

#include "stdafx.h"
#include "ui-core\AnalogMeterCtrl.h"
#include "MIDeskDlg.h"
#include "resource.h"
#include "io-core/NumericConv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMIDeskDlg dialog


CMIDeskDlg::CMIDeskDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMIDeskDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMIDeskDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMIDeskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMIDeskDlg)

	//���������� �������
	DDX_Control(pDX, IDC_MI_TACHOMETER, m_tachometer.m_meter);
	DDX_Control(pDX, IDC_MI_MAP, m_pressure.m_meter);
	DDX_Control(pDX, IDC_MI_VOLTMETER, m_voltmeter.m_meter);
	DDX_Control(pDX, IDC_MI_DWELL_ANGLE, m_dwell_angle.m_meter);
	DDX_Control(pDX, IDC_MI_TEMPERATURE, m_temperature.m_meter);

	//��������� ������� (��������)
	m_gas_valve.DDX_Controls(pDX,IDC_MI_GAS_VALVE,IDC_MI_GAS_VALVE_CAPTION);
	m_throttle_gate.DDX_Controls(pDX, IDC_MI_THROTTLE_GATE, IDC_MI_THROTTLE_GATE_CAPTION);
	m_shutoff_valve.DDX_Controls(pDX, IDC_MI_SHUTOFF_VALVE, IDC_MI_SHUTOFF_VALVE_CAPTION);

	//������ �������
	m_air_flow.DDX_Controls(pDX, IDC_MI_AIR_FLOW, IDC_MI_AIR_FLOW_NUM, IDC_MI_AIR_FLOW_CAPTION);
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMIDeskDlg, CDialog)
	//{{AFX_MSG_MAP(CMIDeskDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMIDeskDlg message handlers

BOOL CMIDeskDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//������� ������� (������� ������)
    m_tachometer.Create();
	m_pressure.Create();
	m_voltmeter.Create();
	m_dwell_angle.Create();
	m_gas_valve.Create();
	m_shutoff_valve.Create();
	m_throttle_gate.Create();
	m_air_flow.Create();
	m_temperature.Create();

    Enable(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//����������/���������� ��������
void CMIDeskDlg::Enable(bool enable)
{
  m_tachometer.Enable(enable);
  m_pressure.Enable(enable);
  m_voltmeter.Enable(enable);
  m_dwell_angle.Enable(enable);
  m_gas_valve.Enable(enable);
  m_shutoff_valve.Enable(enable);
  m_throttle_gate.Enable(enable);
  m_air_flow.Enable(enable);
  m_temperature.Enable(enable);
}

void CMIDeskDlg::Show(bool show)
{
  m_tachometer.Show(show);
  m_pressure.Show(show);
  m_voltmeter.Show(show);
  m_dwell_angle.Show(show);
  m_gas_valve.Show(show);
  m_shutoff_valve.Show(show);
  m_throttle_gate.Show(show);
  m_air_flow.Show(show);
  m_temperature.Show(show);
}

using namespace SECU3IO;

void CMIDeskDlg::SetValues(const SensorDat* i_values)
{
  m_tachometer.SetValue((float)i_values->frequen);
  m_pressure.SetValue(i_values->pressure);
  m_voltmeter.SetValue(i_values->voltage);
  m_dwell_angle.SetValue(i_values->adv_angle);
  m_gas_valve.SetValue(i_values->gas);
  m_shutoff_valve.SetValue(i_values->ephh_valve);
  m_throttle_gate.SetValue(i_values->carb);
  m_air_flow.SetValue(i_values->air_flow);
  m_temperature.SetValue(i_values->temperat);
}

void CMIDeskDlg::GetValues(SensorDat* o_values)
{
  o_values->frequen = CNumericConv::Round(m_tachometer.GetValue());
  o_values->pressure = m_pressure.GetValue();
  o_values->voltage = m_voltmeter.GetValue();
  o_values->adv_angle = m_dwell_angle.GetValue();
  o_values->gas = (unsigned char)m_gas_valve.GetValue();
  o_values->ephh_valve = (unsigned char)m_shutoff_valve.GetValue();
  o_values->carb = (unsigned char)m_throttle_gate.GetValue();
  o_values->air_flow = (unsigned char)m_air_flow.GetValue();
  o_values->temperat = m_temperature.GetValue();
}