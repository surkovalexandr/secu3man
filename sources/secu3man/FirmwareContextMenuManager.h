
#pragma once

class CFirmwareModeContextMenuManager  
{
public:
	CWnd* m_pWnd;        //Identifies the window that owns the pop-up menu
    CMenu m_ParentMenu;  //Top level menu

	std::vector<UINT> m_bl_menu_items_IDs;

	void Attach(CWnd* pWnd);
	void CreateContent(void);
	void TrackPopupMenu(int x, int y);

	CFirmwareModeContextMenuManager(CWnd* pWnd = NULL);
	virtual ~CFirmwareModeContextMenuManager();

    void OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu);

};
