// TDLContentMgr.cpp: implementation of the CTDLContentMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TDLContentMgr.h"
#include "TDCSimpleTextContent.h"

#include "..\Shared\Localizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTDLContentMgr::CTDLContentMgr() 
{
}

CTDLContentMgr::~CTDLContentMgr()
{
}

void CTDLContentMgr::Initialize() const
{
	if (!m_bInitialized)
	{
		CContentMgr::Initialize();

		// we need a non-const pointer to update the array
		CTDLContentMgr* pMgr = const_cast<CTDLContentMgr*>(this);

		IContent* pSimpleText = new CTDCSimpleTextContent;

		pMgr->m_aContent.InsertAt(0, pSimpleText);
		pMgr->m_mapFormatToDescription[pSimpleText->GetTypeID()] = CLocalizer::TranslateText(pSimpleText->GetTypeDescription());
	}
}

CONTENTFORMAT CTDLContentMgr::GetSimpleTextContentFormat() const
{
	Initialize();

	return GetContentFormat(0);
}
