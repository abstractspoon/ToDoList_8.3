// TaskFileTest.cpp: implementation of the CTaskFileTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TDLTest.h"
#include "TaskFileTest.h"

#include "..\todolist\tdcstruct.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////

int CTaskFileTest::NUM_TESTLEVELS = 5;
int CTaskFileTest::MAX_TESTLEVELS = 5;

//////////////////////////////////////////////////////////////////////

const int MAX_GLOBAL_STRINGS = 100;
const int MAX_TASK_STRINGS = 10;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskFileTest::CTaskFileTest(const CTestUtils& utils) : CTDLTestBase(utils)
{
	CoInitialize(NULL);
}

CTaskFileTest::~CTaskFileTest()
{

}

TESTRESULT CTaskFileTest::Run()
{
	ClearTotals();

	TestHierarchyConstructionPerformance();
	TestFlatListConstructionPerformance();

	return GetTotals();
}

void CTaskFileTest::TestHierarchyConstructionPerformance()
{
	if (!m_utils.HasCommandlineFlag('p'))
	{
		_tprintf(_T("Add '-p' to run CTaskFileTest::HierarchyConstructionPerformance\n"));
		return;
	}

	BOOL bNoAttrib = m_utils.HasCommandlineFlag('n');

	BeginTest(_T("CTaskFileTest::HierarchyConstructionPerformance"));

	for (int nNumLevels = 2; nNumLevels <= max(NUM_TESTLEVELS, MAX_TESTLEVELS); nNumLevels++)
	{
		DWORD dwTickStart = GetTickCount();

		CTaskFile tasks;
		PopulateHierarchy(tasks, nNumLevels, ((bNoAttrib || (nNumLevels > 4)) ? TDCA_NONE : TDCA_ALL));
		
		DWORD dwDuration = (GetTickCount() - dwTickStart);
		_tprintf(_T("Test took %ld ms to build a tasklist with %d nested tasks (%.1f ms/100)\n"), 
				 dwDuration, 
				 tasks.GetTaskCount(),
				 (dwDuration * 100.0) / tasks.GetTaskCount());

		// -----------------------------------------------------------------

		CString sFilePath = Misc::Format(_T("TestTasklist_Tree_%d.tdl"), tasks.GetTaskCount());

		TestSaveTasklist(tasks, sFilePath, _T("nested"));
		TestLoadTasklist(sFilePath, _T("nested"));
	}
	
	EndTest();
}

void CTaskFileTest::TestFlatListConstructionPerformance()
{
	if (!m_utils.HasCommandlineFlag('p'))
	{
		_tprintf(_T("Add '-p' to run CTaskFileTest::FlatListConstructionPerformance\n"));
		return;
	}

	BOOL bNoAttrib = m_utils.HasCommandlineFlag('n');

	BeginTest(_T("CTaskFileTest::FlatListConstructionPerformance"));

	for (int nNumLevels = 2, nNumTasks = 10; nNumLevels <= max(NUM_TESTLEVELS, MAX_TESTLEVELS); nNumLevels++)
	{
		DWORD dwTickStart = GetTickCount();

		// Numbers to match hierarchical test
		nNumTasks += (int)pow(10, nNumLevels);

		CTaskFile tasks;
		PopulateFlatList(tasks, nNumTasks, ((bNoAttrib || (nNumLevels > 4)) ? TDCA_NONE : TDCA_ALL));

		DWORD dwDuration = (GetTickCount() - dwTickStart);
		_tprintf(_T("Test took %ld ms to build a tasklist with %d flat tasks (%.1f ms/100)\n"), 
				 dwDuration, 
				 tasks.GetTaskCount(),
				 (dwDuration * 100.0) / tasks.GetTaskCount());

		// -----------------------------------------------------------------

		CString sFilePath = Misc::Format(_T("TestTasklist_Flat_%d.tdl"), tasks.GetTaskCount());

		TestSaveTasklist(tasks, sFilePath, _T("flat"));
		TestLoadTasklist(sFilePath, _T("flat"));
	}

	EndTest();
}

void CTaskFileTest::TestSaveTasklist(CTaskFile& tasks, LPCTSTR szFilePath, LPCTSTR szType)
{
	DWORD dwTickStart = GetTickCount();
	
	tasks.SetXmlHeader(DEFAULT_UNICODE_HEADER);
	tasks.Save(szFilePath, SFEF_UTF16);
	
	DWORD dwDuration = (GetTickCount() - dwTickStart);

	_tprintf(_T("Test took %ld ms to save a tasklist with %d %s tasks (%.1f ms/100)\n"), 
			dwDuration, 
			tasks.GetTaskCount(),
			szType,
			(dwDuration * 100.0) / tasks.GetTaskCount());

}

void CTaskFileTest::TestLoadTasklist(LPCTSTR szFilePath, LPCTSTR szType)
{
	DWORD dwTickStart = GetTickCount();
	
	CTaskFile tasks;
	tasks.Load(szFilePath);
				
	DWORD dwDuration = (GetTickCount() - dwTickStart);

	_tprintf(_T("Test took %ld ms to load a tasklist with %d %s tasks (%.1f ms/100)\n"), 
			dwDuration, 
			tasks.GetTaskCount(),
			szType,
			(dwDuration * 100.0) / tasks.GetTaskCount());
}

void CTaskFileTest::PopulateHierarchy(CTaskFile& tasks, int nNumLevels, const CTDCAttributeMap& mapAttrib) const
{
	ASSERT(nNumLevels > 0 && nNumLevels <= MAX_TESTLEVELS);

	tasks.Reset();
	AddGlobalsToTasklist(tasks, mapAttrib);
	
	Add10TasksToHierarchy(tasks, NULL, 1, nNumLevels, mapAttrib);
}

void CTaskFileTest::Add10TasksToHierarchy(CTaskFile& tasks, HTASKITEM hParentTask, int nLevel, int nNumLevels, const CTDCAttributeMap& mapAttrib)
{
	if (nLevel > nNumLevels)
		return;

	HTASKITEM hPrevSiblingTask = NULL, hTask = NULL;

	for (int i = 0; i < 10; i++)
	{
		if (hPrevSiblingTask == NULL)
			hTask = tasks.NewTask(Misc::Format(_T("Task_%d"), i), NULL, 0, 0, TRUE);
		else
			hTask = tasks.NewSiblingTask(Misc::Format(_T("Task_%d"), i), hPrevSiblingTask, 0, TRUE);

		PopulateNumericTaskAttributes(tasks, hTask, mapAttrib);
		PopulateStringTaskAttributes(tasks, hTask, MAX_TASK_STRINGS, mapAttrib);

		// Add next level of tasks
		Add10TasksToHierarchy(tasks, hTask, nLevel + 1, nNumLevels, mapAttrib);

		hPrevSiblingTask = hTask;
	}
}

void CTaskFileTest::PopulateFlatList(CTaskFile& tasks, int nNumTasks, const CTDCAttributeMap& mapAttrib) const
{
	tasks.Reset();
	AddGlobalsToTasklist(tasks, mapAttrib);
	
	// Create tasks
	HTASKITEM hPrevSiblingTask = NULL, hTask = NULL;

	for (int i = 0; i < nNumTasks; i++)
	{
		if (hPrevSiblingTask == NULL)
			hTask = tasks.NewTask(Misc::Format(_T("Task_%d"), i), NULL, 0, 0, TRUE);
		else
			hTask = tasks.NewSiblingTask(Misc::Format(_T("Task_%d"), i), hPrevSiblingTask, 0, TRUE);

		PopulateNumericTaskAttributes(tasks, hTask, mapAttrib);
		PopulateStringTaskAttributes(tasks, hTask, MAX_TASK_STRINGS, mapAttrib);

		hPrevSiblingTask = hTask;
	}
}

BOOL CTaskFileTest::HasAttribute(const CTDCAttributeMap& mapAttrib, TDC_ATTRIBUTE nAttribID)
{
	return (mapAttrib.Has(TDCA_ALL) || mapAttrib.Has(nAttribID));
}

void CTaskFileTest::AddGlobalsToTasklist(CTaskFile& tasks, const CTDCAttributeMap& mapAttrib)
{
	if (mapAttrib.Has(TDCA_NONE))
		return;

	TDCAUTOLISTDATA tld;

	if (HasAttribute(mapAttrib, TDCA_ALLOCBY))
	{
		tld.aAllocBy.SetSize(MAX_GLOBAL_STRINGS);

		for (int i = 0; i < MAX_GLOBAL_STRINGS; i++)
			tld.aAllocBy[i] = Misc::Format(_T("AllocBy_%d"), i + 1);
	}

	if (HasAttribute(mapAttrib, TDCA_ALLOCTO))
	{
		tld.aAllocTo.SetSize(MAX_GLOBAL_STRINGS);

		for (int i = 0; i < MAX_GLOBAL_STRINGS; i++)
			tld.aAllocTo[i] = Misc::Format(_T("AllocTo_%d"), i + 1);
	}

	if (HasAttribute(mapAttrib, TDCA_CATEGORY))
	{
		tld.aCategory.SetSize(MAX_GLOBAL_STRINGS);

		for (int i = 0; i < MAX_GLOBAL_STRINGS; i++)
			tld.aCategory[i] = Misc::Format(_T("Category_%d"), i + 1);
	}

	if (HasAttribute(mapAttrib, TDCA_STATUS))
	{
		tld.aStatus.SetSize(MAX_GLOBAL_STRINGS);

		for (int i = 0; i < MAX_GLOBAL_STRINGS; i++)
			tld.aStatus[i] = Misc::Format(_T("Status_%d"), i + 1);
	}

	if (HasAttribute(mapAttrib, TDCA_TAGS))
	{
		tld.aTags.SetSize(MAX_GLOBAL_STRINGS);

		for (int i = 0; i < MAX_GLOBAL_STRINGS; i++)
			tld.aTags[i] = Misc::Format(_T("Tag_%d"), i + 1);
	}

	if (HasAttribute(mapAttrib, TDCA_VERSION))
	{
		tld.aVersion.SetSize(MAX_GLOBAL_STRINGS);

		for (int i = 0; i < MAX_GLOBAL_STRINGS; i++)
			tld.aVersion[i] = Misc::Format(_T("Version_%d"), i + 1);
	}

	tasks.SetAutoListData(tld);
}

void CTaskFileTest::PopulateNumericTaskAttributes(CTaskFile& tasks, HTASKITEM hTask, const CTDCAttributeMap& mapAttrib)
{
	if (mapAttrib.Has(TDCA_NONE))
		return;
	
	COleDateTime dtNow = COleDateTime::GetCurrentTime();

	if (HasAttribute(mapAttrib, TDCA_PERCENT))
		tasks.SetTaskPercentDone(hTask, rand() % 100);
		
	if (HasAttribute(mapAttrib, TDCA_PRIORITY))
		tasks.SetTaskPriority(hTask, rand() % 10);
	
	if (HasAttribute(mapAttrib, TDCA_RISK))
		tasks.SetTaskRisk(hTask, rand() % 10);
	
	if (HasAttribute(mapAttrib, TDCA_COST))
		tasks.SetTaskCost(hTask, rand() / 1000.0);
	
	if (HasAttribute(mapAttrib, TDCA_DUEDATE))
		tasks.SetTaskDueDate(hTask, COleDateTime(dtNow.m_dt + (rand() % 100)));
	
	if (HasAttribute(mapAttrib, TDCA_STARTDATE))
		tasks.SetTaskStartDate(hTask, COleDateTime(dtNow.m_dt + (rand() % 100)));
	
	if (HasAttribute(mapAttrib, TDCA_LASTMODDATE))
		tasks.SetTaskLastModified(hTask, COleDateTime(dtNow.m_dt + (rand() % 100)), _T(""));
	
	if (HasAttribute(mapAttrib, TDCA_TIMEESTIMATE))
		tasks.SetTaskTimeEstimate(hTask, rand() % 20, TDCU_DAYS);
	
	if (HasAttribute(mapAttrib, TDCA_TIMESPENT))
		tasks.SetTaskTimeSpent(hTask, rand() % 20, TDCU_DAYS);

	if (HasAttribute(mapAttrib, TDCA_DONEDATE) && ((rand() % 10) == 0))
		tasks.SetTaskDoneDate(hTask, COleDateTime(dtNow.m_dt + (rand() % 100)));
}

void CTaskFileTest::PopulateStringTaskAttributes(CTaskFile& tasks, HTASKITEM hTask, int nNumMultiAttrib, const CTDCAttributeMap& mapAttrib)
{
	if (HasAttribute(mapAttrib, TDCA_ALLOCTO))
	{
		CStringArray aValues;
		PopulateArrayWithRandomStrings(aValues, nNumMultiAttrib, _T("AllocTo_%d"));
		tasks.SetTaskAllocatedTo(hTask, aValues);
	}

	if (HasAttribute(mapAttrib, TDCA_CATEGORY))
	{
		CStringArray aValues;
		PopulateArrayWithRandomStrings(aValues, nNumMultiAttrib, _T("Category_%d"));
		tasks.SetTaskCategories(hTask, aValues);
	}

	if (HasAttribute(mapAttrib, TDCA_TAGS))
	{
		CStringArray aValues;
		PopulateArrayWithRandomStrings(aValues, nNumMultiAttrib, _T("Tags_%d"));
		tasks.SetTaskTags(hTask, aValues);
	}

	int i = (rand() % MAX_GLOBAL_STRINGS);

	if (HasAttribute(mapAttrib, TDCA_ALLOCBY))
		tasks.SetTaskAllocatedBy(hTask, Misc::Format(_T("AllocBy_%d"), i + 1));
	
	if (HasAttribute(mapAttrib, TDCA_STATUS))
		tasks.SetTaskStatus(hTask, Misc::Format(_T("Status_%d"), i + 1));

	if (HasAttribute(mapAttrib, TDCA_VERSION))
		tasks.SetTaskVersion(hTask, Misc::Format(_T("Version_%d"), i + 1));

	if (HasAttribute(mapAttrib, TDCA_LASTMODBY))
		tasks.SetTaskLastModifiedBy(hTask, Misc::Format(_T("LastModBy_%d"), i + 1));
}

void CTaskFileTest::PopulateArrayWithRandomStrings(CStringArray& aValues, int nCount, LPCTSTR szFormat)
{
	aValues.SetSize(nCount);

	while (nCount--)
	{
		int i = (rand() % MAX_GLOBAL_STRINGS);
		aValues[nCount] = Misc::Format(szFormat, i + 1);
	}
}

