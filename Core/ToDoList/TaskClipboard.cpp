// TaskClipboard.cpp: implementation of the CTaskClipboard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskClipboard.h"

#include "..\shared\misc.h"
#include "..\shared\clipboard.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////

const LPCTSTR TDLCF_TASKS = _T("CF_TODOLIST_TASKS");
const LPCTSTR TDLCF_ID = _T("CF_TODOLIST_ID");
const LPCTSTR DEF_CLIPID = _T("_emptyID_");
//////////////////////////////////////////////////////////////////////

CDWordArray CTaskClipboard::s_aSelTaskIDs;

//////////////////////////////////////////////////////////////////////

void CTaskClipboard::Reset()
{
	if (!IsEmpty())
		::EmptyClipboard();

	s_aSelTaskIDs.RemoveAll();
}

BOOL CTaskClipboard::IsEmpty()
{
	return !CClipboard::HasFormat(GetIDClipFmt());
}

BOOL CTaskClipboard::SetTasks(const CTaskFile& tasks, const CString& sID, const CDWordArray& aSelTaskIDs, const CString& sTaskTitles)
{
	ASSERT(tasks.GetTaskCount());
	ASSERT(!sTaskTitles.IsEmpty());
	
	CString sXML; 
	CString sClipID = (sID.IsEmpty() ? DEF_CLIPID : sID);
	
	if (tasks.Export(sXML) && !sXML.IsEmpty())
	{
		sClipID.MakeUpper();

		CClipboard cb(GetMainWnd());
		if (cb.SetText(sXML, GetTaskClipFmt()) && 
			cb.SetText(Misc::ToUpper(sID), GetIDClipFmt()) &&
			cb.SetText(sTaskTitles))
		{
			s_aSelTaskIDs.Copy(aSelTaskIDs);
			return TRUE;
		}
	}
	
	// else
	return FALSE;
}

BOOL CTaskClipboard::ClipIDMatches(const CString& sID)
{
	return (!sID.IsEmpty() && (sID.CompareNoCase(GetClipID()) == 0));
}

int CTaskClipboard::GetTasks(CTaskFile& tasks, const CString& sID)
{
	return GetTasks(tasks, sID, CDWordArray());
}

int CTaskClipboard::GetTasks(CTaskFile& tasks, const CString& sID, CDWordArray& aSelTaskIDs)
{
	if (IsEmpty())
		return 0;

	CClipboard cb;
	CString sXML = cb.GetText(GetTaskClipFmt()); 
	
	if (!tasks.LoadContent(sXML) || !tasks.GetTaskCount())
		return 0;

	aSelTaskIDs.Copy(s_aSelTaskIDs);

	// Remove task references if the clip IDs do not match
	CString sClipID = (sID.IsEmpty() ? DEF_CLIPID : sID);

	if (sClipID.CompareNoCase(GetClipID()) != 0)
	{
		CDWordSet mapSelTaskIDs;
		mapSelTaskIDs.CopyFrom(aSelTaskIDs);

		RemoveTaskReferences(tasks, tasks.GetFirstTask(), TRUE, mapSelTaskIDs);

		// Sync returned task IDs
		int nID = aSelTaskIDs.GetSize();

		while (nID--)
		{
			if (!mapSelTaskIDs.Has(aSelTaskIDs[nID]))
				aSelTaskIDs.RemoveAt(nID);
		}
	}

	return tasks.GetTaskCount();
}

int CTaskClipboard::GetTaskCount(const CString& sID)
{
	if (IsEmpty())
		return 0;

	CTaskFile unused;
	return GetTasks(unused, sID);
}

void CTaskClipboard::RemoveTaskReferences(CTaskFile& tasks, HTASKITEM hTask, BOOL bAndSiblings, CDWordSet& mapSelTaskIDs)
{
	if (!hTask)
		return;

	// process children first before their parent is potentially removed
	RemoveTaskReferences(tasks, tasks.GetFirstTask(hTask), TRUE, mapSelTaskIDs);

	// Handle siblings WITHOUT RECURSION
	if (bAndSiblings)
	{
		HTASKITEM hSibling = tasks.GetNextTask(hTask);
		
		while (hSibling)
		{
			// Grab next sibling before we potentially delete this one
			HTASKITEM hNextSibling = tasks.GetNextTask(hSibling);

			// FALSE == don't recurse on siblings
			RemoveTaskReferences(tasks, hSibling, FALSE, mapSelTaskIDs);
			
			hSibling = hNextSibling;
		}
	}

	// delete if reference
	if (tasks.GetTaskReferenceID(hTask) > 0)
	{
		mapSelTaskIDs.Remove(tasks.GetTaskID(hTask));
		tasks.DeleteTask(hTask);
	}
}

CString CTaskClipboard::GetClipID()
{
	return CClipboard().GetText(GetIDClipFmt()); 
}

UINT CTaskClipboard::GetTaskClipFmt()
{
	static UINT nClip = ::RegisterClipboardFormat(TDLCF_TASKS);
	return nClip;
}

UINT CTaskClipboard::GetIDClipFmt()
{
	static UINT nClip = ::RegisterClipboardFormat(TDLCF_ID);
	return nClip;
}

HWND CTaskClipboard::GetMainWnd()
{
	return (*AfxGetMainWnd());
}
