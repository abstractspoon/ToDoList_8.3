// EditPrompt.h: interface for the CWndPrompt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDPROMPT_H__485A738F_5BCB_4D7E_9B3E_6E9382AC62D8__INCLUDED_)
#define AFX_WNDPROMPT_H__485A738F_5BCB_4D7E_9B3E_6E9382AC62D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Subclass.h"
#include <afxtempl.h>

class CWndPrompt : public CSubclassWnd  
{
public:
	CWndPrompt();
	virtual ~CWndPrompt();

	BOOL Initialize(HWND hWnd, LPCTSTR szPrompt, UINT nCheckMsg, LRESULT lCheckRes = 0, BOOL bCentred = FALSE, BOOL bIncReadonlyEdit = FALSE);
	void SetPrompt(LPCTSTR szPrompt, BOOL bCentred = -1);

	static void DrawPrompt(HWND hWnd, LPCTSTR szPrompt, HDC hdc = NULL, BOOL bCentred = FALSE, LPCTSTR szClass = NULL);

protected:
	CString m_sPrompt;
	UINT m_nCheckMsg;
	LRESULT m_lCheckResult;
	int m_bCentred;
	BOOL m_bIncReadonlyEdit;
	CString m_sClass; // for some tweaking

protected:
	virtual LRESULT WindowProc(HWND hRealWnd, UINT msg, WPARAM wp, LPARAM lp);
	BOOL WantPrompt(BOOL bCheckFocus = TRUE);
	void DrawPrompt(HDC hdc);

	static COLORREF GetTextColor(HWND hWnd);
};

class CWndPromptManager
{
public:
	CWndPromptManager();
	virtual ~CWndPromptManager();

	BOOL SetPrompt(UINT nIDCtrl, HWND hwndParent, LPCTSTR szPrompt, 
					UINT nCheckMsg, LRESULT lCheckRes = 0, BOOL bCentred = FALSE, BOOL bIncReadonlyEdit = FALSE);
	BOOL SetPrompt(HWND hWnd, LPCTSTR szPrompt, 
					UINT nCheckMsg, LRESULT lCheckRes = 0, BOOL bCentred = FALSE, BOOL bIncReadonlyEdit = FALSE);

	BOOL SetPrompt(UINT nIDCtrl, HWND hwndParent, UINT nIDPrompt, 
					UINT nCheckMsg, LRESULT lCheckRes = 0, BOOL bCentred = FALSE, BOOL bIncReadonlyEdit = FALSE);
	BOOL SetPrompt(HWND hWnd, UINT nIDPrompt, 
					UINT nCheckMsg, LRESULT lCheckRes = 0, BOOL bCentred = FALSE, BOOL bIncReadonlyEdit = FALSE);

	// special cases
	BOOL SetEditPrompt(UINT nIDEdit, HWND hwndParent, LPCTSTR szPrompt, BOOL bIncReadonly = FALSE);
	BOOL SetEditPrompt(HWND hwndEdit, LPCTSTR szPrompt, BOOL bIncReadonly = FALSE);
	BOOL SetComboPrompt(UINT nIDCombo, HWND hwndParent, LPCTSTR szPrompt, BOOL bIncReadonlyEdit = FALSE);
	BOOL SetComboPrompt(HWND hwndCombo, LPCTSTR szPrompt, BOOL bIncReadonlyEdit = FALSE);
	BOOL SetComboEditPrompt(UINT nIDCombo, HWND hwndParent, LPCTSTR szPrompt, BOOL bIncReadonly = FALSE);
	BOOL SetComboEditPrompt(HWND hwndCombo, LPCTSTR szPrompt, BOOL bIncReadonly = FALSE);

	BOOL SetEditPrompt(UINT nIDEdit, HWND hwndParent, UINT nIDPrompt, BOOL bIncReadonly = FALSE);
	BOOL SetEditPrompt(HWND hwndEdit, UINT nIDPrompt, BOOL bIncReadonly = FALSE);
	BOOL SetComboPrompt(UINT nIDCombo, HWND hwndParent, UINT nIDPrompt, BOOL bIncReadonlyEdit = FALSE);
	BOOL SetComboPrompt(HWND hwndCombo, UINT nIDPrompt, BOOL bIncReadonly = FALSE);
	BOOL SetComboEditPrompt(UINT nIDCombo, HWND hwndParent, UINT nIDPrompt, BOOL bIncReadonlyEdit = FALSE);
	BOOL SetComboEditPrompt(HWND hwndCombo, UINT nIDPrompt, BOOL bIncReadonly = FALSE);

protected:
	CMap<HWND, HWND, CWndPrompt*, CWndPrompt*&> m_mapWnds;

};

#endif // !defined(AFX_WNDPROMPT_H__485A738F_5BCB_4D7E_9B3E_6E9382AC62D8__INCLUDED_)
