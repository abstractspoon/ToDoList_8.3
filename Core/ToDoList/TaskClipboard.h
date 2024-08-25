// TaskClipboard.h: interface for the CTaskClipboard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKCLIPBOARD_H__7724479D_9E23_42B2_816F_40FE2B24B9C2__INCLUDED_)
#define AFX_TASKCLIPBOARD_H__7724479D_9E23_42B2_816F_40FE2B24B9C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////

#include "taskfile.h"

//////////////////////////////////////////////////////////////////////

class CDWordSet;

//////////////////////////////////////////////////////////////////////

class CTaskClipboard  
{
public:
	static void Reset();
	static BOOL IsEmpty();
	static BOOL ClipIDMatches(const CString& sID);
	static BOOL SetTasks(const CTaskFile& tasks, const CString& sID, const CDWordArray& aSelTaskIDs, const CString& sTaskTitles);

	static int GetTasks(CTaskFile& tasks, const CString& sID);
	static int GetTasks(CTaskFile& tasks, const CString& sID, CDWordArray& aSelTaskIDs);
	static int GetTaskCount(const CString& sID = _T(""));

protected:
	static CDWordArray s_aSelTaskIDs;

protected:
	static CString GetClipID();
	static UINT GetTaskClipFmt();
	static UINT GetIDClipFmt();
	static HWND GetMainWnd();
	static void RemoveTaskReferences(CTaskFile& tasks, HTASKITEM hTask, BOOL bAndSiblings, CDWordSet& mapSelTaskIDs);
};

#endif // !defined(AFX_TASKCLIPBOARD_H__7724479D_9E23_42B2_816F_40FE2B24B9C2__INCLUDED_)
