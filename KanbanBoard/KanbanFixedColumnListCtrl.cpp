// KanbanFixedColumnListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "KanbanFixedColumnListCtrl.h"

#include "..\shared\misc.h"
#include "..\shared\graphicsmisc.h"
#include "..\shared\dialoghelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

enum
{
	KFCL_TITLECOL,
	KFCL_VALUECOL,
//	KFCL_MAXNUMCOL,
	KFCL_COLORCOL,
};

const UINT IDC_VALUES = 5000;

/////////////////////////////////////////////////////////////////////////////
// CKanbanFixedColumnListCtrl

CKanbanFixedColumnListCtrl::CKanbanFixedColumnListCtrl()
{
	//m_cbValues.SetMinDLUHeight(9);
}

CKanbanFixedColumnListCtrl::~CKanbanFixedColumnListCtrl()
{
}


BEGIN_MESSAGE_MAP(CKanbanFixedColumnListCtrl, CInputListCtrl)
	//{{AFX_MSG_MAP(CKanbanFixedColumnListCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_CBN_CLOSEUP(IDC_VALUES, OnValueEditCancel)
	ON_CBN_SELENDCANCEL(IDC_VALUES, OnValueEditCancel)
	ON_CBN_SELCHANGE(IDC_VALUES, OnValueEditOK)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKanbanFixedColumnListCtrl message handlers

BOOL CKanbanFixedColumnListCtrl::SetColumnDefinitions(const CKanbanColumnArray& aColumnDefs)
{
	if (!GetSafeHwnd())
	{
		ASSERT(0);
		return FALSE;
	}

	// fill column defs
	DeleteAllItems(FALSE);
	int nNumDefs = aColumnDefs.GetSize();
	
	for (int nDef = 0; nDef < nNumDefs; nDef++)
	{
		const KANBANCOLUMN& colDef = aColumnDefs.GetData()[nDef];
		
		int nItem = InsertItem(nDef, colDef.sTitle);
		
		SetItemText(nItem, KFCL_VALUECOL, Misc::FormatArray(colDef.aAttribValues));
		
// 		if (colDef.nMaxTaskCount > 0)
// 			SetItemText(nItem, KFCL_MAXNUMCOL, Misc::Format(colDef.nMaxTaskCount));

		SetItemData(nItem, colDef.crBackground);
	}

	return TRUE;
}

int CKanbanFixedColumnListCtrl::GetColumnDefinitions(CKanbanColumnArray& aColumnDefs) const
{
	aColumnDefs.RemoveAll();
	
	int nNumDefs = (GetItemCount() - 1);
	
	for (int nDef = 0; nDef < nNumDefs; nDef++)
	{
		KANBANCOLUMN colDef;
		
		colDef.sTitle = GetItemText(nDef, KFCL_TITLECOL);
// 		colDef.nMaxTaskCount = _ttoi(GetItemText(nDef, KFCL_MAXNUMCOL));
		colDef.crBackground = GetItemData(nDef);
		
		CString sValues(GetItemText(nDef, KFCL_VALUECOL));

		if (sValues.IsEmpty())
			colDef.aAttribValues.Add(sValues);
		else
			Misc::Split(sValues, colDef.aAttribValues);

		aColumnDefs.Add(colDef);
	}

	return nNumDefs;
}

void CKanbanFixedColumnListCtrl::PreSubclassWindow()
{
	// create child controls 
	// we need combo to be created first
	CreateControl(m_cbValues, IDC_VALUES);

	CInputListCtrl::PreSubclassWindow();

	CRect rClient;
	GetClientRect(rClient);
	
	AddCol(CEnString(IDS_COLUMNTITLE),	((rClient.Width() * 3) / 10));
	AddCol(CEnString(IDS_ATTRIBVALUES),	((rClient.Width() * 3) / 10));
//	AddCol(CEnString(IDS_MAXTASKCOUNT),	((rClient.Width() * 2) / 10));
	AddCol(CEnString(IDS_BKGNDCOLOR),	((rClient.Width() * 2) / 10));
	
	SetColumnType(KFCL_VALUECOL, ILCT_DROPLIST);
	SetColumnType(KFCL_COLORCOL, ILCT_BROWSE);

	SetAutoRowPrompt(CEnString(IDS_NEWCOLUMN));
	AutoAdd(TRUE, FALSE);
	ShowGrid(TRUE, TRUE);
	EnableHeaderTracking(FALSE);
	
	CRect rCombo;
	m_cbValues.GetWindowRect(rCombo);
	
	SetMinItemHeight(rCombo.Height());
}

void CKanbanFixedColumnListCtrl::SetAttributeValues(const CStringArray& aValues)
{
	ASSERT(GetSafeHwnd());

	CDialogHelper::SetComboBoxItems(m_cbValues, aValues);
}

void CKanbanFixedColumnListCtrl::InitState()
{
	CInputListCtrl::InitState();
}

void CKanbanFixedColumnListCtrl::EditCell(int nItem, int nCol)
{
	switch (nCol)
	{
	case KFCL_VALUECOL:
		PrepareEdit(nItem, nCol);
		ShowControl(m_cbValues, nItem, nCol); 
		break;

	case KFCL_COLORCOL:
		{
			CColorDialog dialog(GetItemData(nItem));

			if (dialog.DoModal() == IDOK)
			{
				COLORREF color = dialog.GetColor();

				if (color == GetSysColor(COLOR_WINDOW))
					color = CLR_NONE;

				SetItemData(nItem, color);
			}
		}
		break;

	case KFCL_TITLECOL:
	default:
		CInputListCtrl::EditCell(nItem, nCol);
		break;
	}
}

BOOL CKanbanFixedColumnListCtrl::IsEditing() const 
{
	return (CInputListCtrl::IsEditing() || m_cbValues.IsWindowVisible());
}

BOOL CKanbanFixedColumnListCtrl::CanEditSelectedCell() const 
{
	return CInputListCtrl::CanEditSelectedCell();
}

void CKanbanFixedColumnListCtrl::PrepareEdit(int nRow, int nCol)
{
	if (nCol == KFCL_VALUECOL)
	{
		CStringArray aValues;
		Misc::Split(GetItemText(nRow, nCol), aValues);

		m_cbValues.SetChecked(aValues);
	}		
}

void CKanbanFixedColumnListCtrl::OnValueEditCancel()
{
	HideControl(m_cbValues);
}

void CKanbanFixedColumnListCtrl::OnValueEditOK()
{
	HideControl(m_cbValues);

	CStringArray aValues;
	m_cbValues.GetChecked(aValues);

	SetCellText(GetCurSel(), KFCL_VALUECOL, Misc::FormatArray(aValues));
}

void CKanbanFixedColumnListCtrl::PostDrawContent(CDC* pDC, int nRow, int nCol, const CRect& rContent)
{
	if (nCol == KFCL_COLORCOL)
	{
		COLORREF color = GetItemData(nRow);

		if (color != CLR_NONE)
		{
			CRect rColor(rContent);
			rColor.DeflateRect(4, 3);

			GraphicsMisc::DrawRect(pDC, rColor, color, GraphicsMisc::Darker(color, 0.4));
		}
	}
}
