/* SECU-3  - An open source, free engine control unit
   Copyright (C) 2007 Alexey A. Shabelnikov. Ukraine, Gorlovka

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

#pragma once

#include "common/FastDelegate.h"
#include "ui-core/TabDialog.h"

class CDevDiagnostTabDlg : public CTabDialog
{
  typedef CTabDialog Super;
  typedef fastdelegate::FastDelegate1<bool> EventToggle;
  typedef fastdelegate::FastDelegate2<int, bool> EventOutputToggle;

 public:
  CDevDiagnostTabDlg(CWnd* pParent = NULL);
  static const UINT IDD;
  virtual LPCTSTR GetDialogID(void) const;

  //��������� ������������ ������� �� ��������� ����������
  void setOnOutputToggle(EventOutputToggle OnFunction);
  void setOnEnterButton(EventToggle OnFunction);

  void EnableDiagControls(bool i_enable);
  void EnableEnterButton(bool i_enable);

  //IDs for outputs
  enum 
  {
   OID_IGN_OUT1 = 0,
   OID_IGN_OUT2,
   OID_IGN_OUT3,
   OID_IGN_OUT4,
   OID_IE,
   OID_FE,
   OID_ECF,
   OID_CE,
   OID_ST_BLOCK,
   OID_ADD_IO1,
   OID_ADD_IO2,
  };

  //IDs for inputs
  enum
  {
   IID_VOLTAGE = 0,
   IID_MAP_S,
   IID_TEMP,
   IID_ADD_IO1,
   IID_ADD_IO2,
   IID_CARB,
   IID_GAS_V,
   IID_CKPS,
   IID_REF_S,
   IID_PS,
   IID_KS_1,
   IID_KS_2
  };

 protected:
  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* pDX);
  afx_msg void OnUpdateDiagControls(CCmdUI* pCmdUI);
  afx_msg void OnUpdateEnterButton(CCmdUI* pCmdUI);
  afx_msg void OnOutputCheckToggle(UINT nID);
  afx_msg void OnEnterButton();
  afx_msg void OnTimer(UINT nIDEvent);
  afx_msg void OnDestroy();
  DECLARE_MESSAGE_MAP()

 private:
  CButton m_enter_button;
  EventOutputToggle m_on_output_check;
  EventToggle m_on_enter_button;

  bool m_enable_diag_controls;
  bool m_enable_enter_button;
};
