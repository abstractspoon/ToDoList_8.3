// ToolTipCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "ToolTipCtrlEx.h"
#include "DialogHelper.h"

#include "..\3rdParty\MemDC.h"

/////////////////////////////////////////////////////////////////////////////

const UINT WM_SYSKEYFIRST = WM_SYSKEYDOWN;
const UINT WM_SYSKEYLAST = WM_SYSDEADCHAR;

const UINT WM_NCMOUSEFIRST = WM_NCMOUSEMOVE;
const UINT WM_NCMOUSELAST = WM_NCMBUTTONDBLCLK;

/////////////////////////////////////////////////////////////////////////////

//const int TOOLINFO_SIZE = 40; // sizeof(AFX_OLDTOOLINFO)
const int TOOLINFO_SIZE = sizeof(TOOLINFO);

/////////////////////////////////////////////////////////////////////////////

#ifndef TTM_ADJUSTRECT
#	define TTM_ADJUSTRECT (WM_USER + 31)
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CToolTipCtrlEx, CToolTipCtrl)

/////////////////////////////////////////////////////////////////////////////

CToolTipCtrlEx::CToolTipCtrlEx() 
	: 
	m_bUsingRelayEvent(-1), 
	m_nLastHit(-1)
{
	InitToolInfo(m_tiLast, FALSE);
}

CToolTipCtrlEx::~CToolTipCtrlEx()
{
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CToolTipCtrlEx, CToolTipCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

void CToolTipCtrlEx::EnableTracking(BOOL bTracking, int nXOffset, int nYOffset)
{
	ASSERT(m_bUsingRelayEvent <= 0);

	if (bTracking)
	{
		m_nFlags |= WF_TRACKINGTOOLTIPS;

		m_ptTrackingOffset.x = nXOffset;
		m_ptTrackingOffset.y = nYOffset;
	}
	else
	{
		m_nFlags &= ~WF_TRACKINGTOOLTIPS;
	}
}

BOOL CToolTipCtrlEx::IsTracking() const
{
	return (m_nFlags & WF_TRACKINGTOOLTIPS);
}

void CToolTipCtrlEx::RelayEvent(LPMSG lpMsg)
{
	ASSERT(GetSafeHwnd());
	ASSERT((m_bUsingRelayEvent == -1) || (m_bUsingRelayEvent));

	if (m_bUsingRelayEvent == -1)
	{
		m_bUsingRelayEvent = TRUE;
	}
	else if (!m_bUsingRelayEvent)
	{
		return;
	}

	CToolTipCtrl::RelayEvent(lpMsg);
}

void CToolTipCtrlEx::FilterToolTipMessage(MSG* pMsg)
{
	ASSERT(GetSafeHwnd());
	ASSERT((m_bUsingRelayEvent == -1) || (m_bUsingRelayEvent == FALSE));

	if (m_bUsingRelayEvent == -1)
	{
		m_bUsingRelayEvent = FALSE;
	}
	else if (m_bUsingRelayEvent)
	{
		return;
	}

	// Adapted from CWnd::FilterToolTipMessage()
	UINT message = pMsg->message;

	if ((message == WM_MOUSELEAVE) || (message == WM_NCMOUSELEAVE))
	{
		Activate(FALSE);
	}
	else if (((message == WM_MOUSEMOVE) || 
			  (message == WM_NCMOUSEMOVE) ||
			  (message == WM_LBUTTONUP) || 
			  (message == WM_RBUTTONUP) || 
			  (message == WM_MBUTTONUP)) &&
			((GetKeyState(VK_LBUTTON) >= 0) && 
			 (GetKeyState(VK_RBUTTON) >= 0) &&
			 (GetKeyState(VK_MBUTTON) >= 0)))
	{
		// Check it's within our owner's rect
		CWnd* pOwner = GetOwner();
		ASSERT(pOwner);

		CRect rOwner;
		pOwner->GetWindowRect(rOwner);

		if (!rOwner.PtInRect(pMsg->pt))
			return;

		// determine which tool was hit
		CPoint point = pMsg->pt;
		pOwner->ScreenToClient(&point);

		TOOLINFO tiHit;
		InitToolInfo(tiHit, TRUE);

		int nHit = DoToolHitTest(pOwner, point, tiHit);
		
		if (m_nLastHit != nHit)
		{
			//TRACE(_T("CToolTipCtrlEx::FilterToolTipMessage(%d -> %d)\n"), m_nLastHit, nHit);

			// Delete the old tool
			if ((m_nLastHit != -1) && m_tiLast.cbSize)
			{
 				Activate(FALSE);
			}
			ASSERT(GetToolCount() == 0);

			if (nHit != -1)
			{
				// add new tool and activate the tip
				TOOLINFO ti = tiHit;

//				ti.uFlags &= ~(TTF_NOTBUTTON|TTF_ALWAYSTIP);

 				if (IsTracking())
 					ti.uFlags |= TTF_TRACK | TTF_ABSOLUTE | TTF_NOTBUTTON;

				VERIFY(SendMessage(TTM_ADDTOOL, 0, (LPARAM)&ti));

				if ((ti.uFlags & TTF_ALWAYSTIP) || IsTopParentActive(pOwner))
				{
					// allow the tooltip to popup when it should
					Activate(TRUE);
					//TRACE(_T("CToolTipCtrlEx::Activate(TRUE, \"%s\")\n"), tiHit.lpszText);

 					if (IsTracking())
 						SendMessage(TTM_TRACKACTIVATE, TRUE, (LPARAM)&ti);

					// bring the tooltip window above other popup windows
					SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0,
									SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER);
				}

				m_tiLast = tiHit;
				m_nLastHit = nHit;
			}
			else
			{
				Activate(FALSE);
			}

			CToolTipCtrl::RelayEvent(pMsg);
		}
		else // m_nLastHit == nHit
		{
			if (IsTracking())
			{
				CPoint ptTip(pMsg->pt);
				ptTip.Offset(m_ptTrackingOffset);

				SendMessage(TTM_TRACKPOSITION, 0, MAKELPARAM(ptTip.x, ptTip.y));
				SendMessage(TTM_UPDATETIPTEXT, 0, (LPARAM)&tiHit);
			}
		}

		// Cleanup
		if ((tiHit.lpszText != LPSTR_TEXTCALLBACK) && (tiHit.hinst == 0))
			free(tiHit.lpszText);
	}
	else if (m_nFlags & (WF_TOOLTIPS|WF_TRACKINGTOOLTIPS))
	{
		// make sure that tooltips are not already being handled
		CWnd* pWnd = CWnd::FromHandle(pMsg->hwnd);

		while (pWnd != NULL && pWnd != this && !(pWnd->m_nFlags & (WF_TOOLTIPS|WF_TRACKINGTOOLTIPS)))
			pWnd = pWnd->GetParent();

		if (pWnd != this)
			return;
		
		if (!IsTracking() && (IsKeypress(message) || IsMouseDown(message)))
		{
			Activate(FALSE);
		}
	}
}

BOOL CToolTipCtrlEx::IsMouseDown(UINT nMsgID)
{
	switch (nMsgID)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONDBLCLK:
	case WM_NCLBUTTONDOWN:
	case WM_NCLBUTTONDBLCLK:
	case WM_NCRBUTTONDOWN:
	case WM_NCRBUTTONDBLCLK:
	case WM_NCMBUTTONDOWN:
	case WM_NCMBUTTONDBLCLK:
		return TRUE;
	}

	return FALSE;
}

BOOL CToolTipCtrlEx::IsKeypress(UINT nMsgID)
{
	return ((nMsgID >= WM_KEYFIRST && nMsgID <= WM_KEYLAST) ||
			(nMsgID >= WM_SYSKEYFIRST && nMsgID <= WM_SYSKEYLAST));
}

int CToolTipCtrlEx::DoToolHitTest(CWnd* pOwner, CPoint point, TOOLINFO& ti)
{
	ASSERT(pOwner);

	if (CWnd::FromHandlePermanent(*pOwner) != NULL)
		return pOwner->OnToolHitTest(point, &ti);

	// Send message
	return pOwner->SendMessage(WM_TTC_TOOLHITTEST, MAKEWPARAM(point.x, point.y), (LPARAM)&ti);
}

int CToolTipCtrlEx::SetToolInfo(TOOLINFO& ti, const CWnd* pWnd, const CString sTooltip, int nID, const CRect& rBounds, UINT nFlags)
{
	ASSERT(pWnd);
	ASSERT(!sTooltip.IsEmpty());
	ASSERT(nID > 0);
	ASSERT(!rBounds.IsRectEmpty());

	ti.hwnd = pWnd->GetSafeHwnd();
	ti.uId = nID;
	ti.lpszText = _tcsdup(sTooltip); // MFC will free the duplicated string
	ti.rect = rBounds;
	ti.uFlags = nFlags;

	return nID;
}

BOOL CToolTipCtrlEx::IsTopParentActive(CWnd* pOwner)
{
	ASSERT(pOwner);
	
	if (CWnd::FromHandlePermanent(*pOwner) != NULL)
		return pOwner->IsTopParentActive();
	
	// From CWnd::GetTopLevelParent
	HWND hWndParent = *pOwner;
	HWND hWndT;
	while ((hWndT = GetParentOwner(hWndParent)) != NULL)
		hWndParent = hWndT;

	return (::GetForegroundWindow() == ::GetLastActivePopup(hWndParent));
}

HWND CToolTipCtrlEx::GetParentOwner(HWND hWnd)
{
	// From AfxGetParentOwner
	if (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD)
		return ::GetParent(hWnd);
	
	// else
	return ::GetWindow(hWnd, GW_OWNER);
}

BOOL CToolTipCtrlEx::WantMessage(UINT nMsgID)
{
	switch (nMsgID)
	{
	case WM_MOUSELEAVE:
	case WM_NCMOUSELEAVE:
	case WM_MOUSEMOVE:
	case WM_NCMOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		return TRUE;
	}

	// else
	return (IsKeypress(nMsgID) || IsMouseDown(nMsgID));
}

void CToolTipCtrlEx::Activate(BOOL bActivate)
{
	CToolTipCtrl::Activate(bActivate);

	if (!bActivate)
	{
		SendMessage(TTM_DELTOOL, 0, (LPARAM)&m_tiLast);
		
		InitToolInfo(m_tiLast, FALSE);
		m_nLastHit = -1;
	}
	else
	{
		CDialogHelper::TrackMouseLeave(::GetParent(m_hWnd));
	}
}

void CToolTipCtrlEx::InitToolInfo(TOOLINFO& ti, BOOL bInitSize)
{
	ZeroMemory(&ti, TOOLINFO_SIZE);

	if (bInitSize)
		ti.cbSize = TOOLINFO_SIZE;
}

const TOOLINFO& CToolTipCtrlEx::GetLastHitToolInfo() const 
{ 
	return m_tiLast; 
}

BOOL CToolTipCtrlEx::AdjustRect(LPRECT lprc, BOOL bLarger /*= TRUE*/) const
{ 
	ASSERT(::IsWindow(m_hWnd));  
	
	return (BOOL)::SendMessage(m_hWnd, TTM_ADJUSTRECT, bLarger, (LPARAM)lprc); 
}

void CToolTipCtrlEx::OnPaint()
{
	// Prevent flicker
	CPaintDC dc(this); 
	CMemDC dcMem(&dc);

// 	CRect rClient;
// 	GetClientRect(rClient);
// 
// 	dcMem.FillSolidRect(rClient, GetSysColor(COLOR_INFOBK));

	// default draw to temp dc
	DefWindowProc(WM_PRINTCLIENT, (WPARAM)(HDC)dcMem, 0);
}
