/* SECU-3  - An open source, free engine control unit
   Copyright (C) 2007 Alexey A. Shabelnikov. Ukraine, Kiev

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   contacts:
              http://secu-3.org
              email: shabelnikov@secu-3.org
*/

/** \file PMMonitorController.h
 * \author Alexey A. Shabelnikov
 */

#pragma once

#include <vector>
#include "PMControllerBase.h"

class CCommunicationManager;
class CCEDeskDlg;
class CMIDeskDlg;
class CRSDeskDlg;
class CStatusBarManager;
class ISettingsData;
class ITablesDeskView;

class CPMMonitorController : public CPMControllerBase<CMIDeskDlg>
{
  typedef CPMControllerBase<VIEW> Super;
  typedef CRSDeskDlg RSDVIEW;
  typedef CCEDeskDlg CEDVIEW;
  typedef ITablesDeskView TDVIEW;
 public:
  CPMMonitorController(VIEW* ip_view, RSDVIEW* ip_rsdview, CEDVIEW* ip_cedview, TDVIEW* ip_tdview, CCommunicationManager* ip_comm, CStatusBarManager* ip_sbar, ISettingsData* ip_settings);
  virtual ~CPMMonitorController();

  //��������� ��������� ����������
  void OnSettingsChanged(void);

  //������ ������ �����������
  virtual void OnActivate(void);

  //����� ������ �����������
  virtual void OnDeactivate(void);

  virtual void Enable(bool state);

  virtual void StartDataCollection(void);

  //������ ���� ����������� ������ ����� �������� (�������� �������)
  //���������� true ����� ��� ������ ���������  
  virtual bool CollectData(const BYTE i_descriptor, const void* i_packet_data);

  virtual void ShowRawSensors(bool show);

  void ApplyFWOptions(DWORD opt);

 private:
  CRSDeskDlg* mp_rsdview;
  CCEDeskDlg* mp_cedview;
  TDVIEW* mp_tdview;
  CCommunicationManager* mp_comm;
  CStatusBarManager* mp_sbar;
  ISettingsData* mp_settings;
  bool m_show_raw_sensors;
};
