 /****************************************************************
 *       SECU-3  - An open source, free engine control unit
 *    Designed by Alexey A. Shabelnikov. Ukraine, Gorlovka 2007.
 *       Microprocessors systems - design & programming.
 *    contacts:
 *              http://secu-3.narod.ru
 *              ICQ: 405-791-931
 ****************************************************************/

#include "stdafx.h"
#include "MITemperature.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMITemperature::CMITemperature()
{

}

CMITemperature::~CMITemperature()
{

}

void CMITemperature::Create(void)
{
  m_meter.SetRange (-40.0, 120.0) ;
  m_meter.SetLabelsDecimals(1) ;
  m_meter.SetValueDecimals(1) ;
  m_meter.SetTitle("�����������") ;
  m_meter.SetFontScale(80);    
  m_meter.SetColor(meter_value,RGB(10,80,255));
  m_meter.SetUnit("�C");
  m_meter.SetTickNumber(16);
  m_meter.AddAlertZone(-40,50,RGB(130,130,180));
  m_meter.AddAlertZone(50,100,RGB(120,120,120));
  m_meter.AddAlertZone(100,120,RGB(230,130,130));
  m_meter.UpdateNeedle(-40.0);
}


//--------------------interface-----------------------
void CMITemperature::SetValue(float value)
{
  m_meter.UpdateNeedle((double)value);
}

float CMITemperature::GetValue(void)
{
  return (float)m_meter.GetNeedlePos();
}
	
void CMITemperature::Show(bool show)
{
  m_meter.ShowWindow((show) ? SW_SHOW : SW_HIDE);
}
	
void CMITemperature::Enable(bool enable)
{
  m_meter.SetState(meter_needle, enable);
  m_meter.SetState(meter_value, enable);
  m_meter.SetState(meter_grid, enable);
  m_meter.SetState(meter_labels, enable);
  m_meter.SetState(meter_unit, enable);

  m_meter.Redraw();
}
	
bool CMITemperature::IsVisible(void)
{
  return (m_meter.IsWindowVisible()) ? true : false;
}
	
bool CMITemperature::IsEnabled(void)
{
  bool State = false;
  m_meter.GetState(meter_needle, &State);
  return State;
}	
	
void CMITemperature::SetLimits(float loLimit, float upLimit)
{
  m_meter.SetRange(loLimit, upLimit);
}
	
void CMITemperature::SetTicks(int number)
{
  m_meter.SetTickNumber(number);
}
//----------------------------------------------------