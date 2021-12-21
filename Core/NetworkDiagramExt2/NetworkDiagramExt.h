// GanttChartExt.h: interface for the CGanttChartExtApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORKDIAGRAMEXT_H__DEE73DE1_C6EC_4648_9151_0FC2C75A806D__INCLUDED_)
#define AFX_NETWORKDIAGRAMEXT_H__DEE73DE1_C6EC_4648_9151_0FC2C75A806D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////

#include "..\shared\Icon.h"

#include "..\Interfaces\IUIExtension.h"

//////////////////////////////////////////////////////////////////////

const LPCTSTR NETWORKDIAGRAM_TYPEID = _T("83F6CBD3-5F3C-4567-9BA8-9544B899F9BB");

//////////////////////////////////////////////////////////////////////

class CNetworkDiagramExtApp : public IUIExtension, public CWinApp
{
public:
	CNetworkDiagramExtApp();
	virtual ~CNetworkDiagramExtApp();

    void Release(); // releases the interface
	void SetLocalizer(ITransText* pTT);

	LPCTSTR GetMenuText() const { return _T("Network Diagram"); }
	HICON GetIcon() const { return m_icon; }
	LPCTSTR GetTypeID() const { return NETWORKDIAGRAM_TYPEID; }

	IUIExtensionWindow* CreateExtWindow(UINT nCtrlID, DWORD nStyle, 
										long nLeft, long nTop, long nWidth, long nHeight, 
										HWND hwndParent);
	
	void SavePreferences(IPreferences* pPrefs, LPCWSTR szKey) const;
	void LoadPreferences(const IPreferences* pPrefs, LPCWSTR szKey);

protected:
	CIcon m_icon;

protected:
	BOOL InitInstance();
};

#endif // !defined(AFX_NETWORKDIAGRAMEXT_H__DEE73DE1_C6EC_4648_9151_0FC2C75A806D__INCLUDED_)
