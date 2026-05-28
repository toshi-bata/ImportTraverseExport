#include "MyTreeVisitor.h"

A3DStatus MyTreeVisitor::visitEnter(const A3DProductOccurrenceConnector& sConnector)
{
	A3DStatus iRet = A3DTreeVisitor::visitEnter(sConnector);

	// Increment level
	m_iLevel++;

	// Get the ProductOccurrence (PO)
	const A3DEntity* pEntity = sConnector.GetA3DEntity();
	A3DAsmProductOccurrence* pPO = (A3DAsmProductOccurrence*)pEntity;

	// Get RootBaseData of the PO
	A3DRootBaseData sRootBaseData;
	A3D_INITIALIZE_DATA(A3DRootBaseData, sRootBaseData);
	A3DRootBaseGet(pPO, &sRootBaseData);

	// Get the PO name  
	A3DUniChar acName[256];
	if (sRootBaseData.m_pcName)
		A3DMiscUTF8ToUTF16(sRootBaseData.m_pcName, acName);
	else
		wcscpy_s(acName, _T("NO_NAME"));

	// Show the PO name with level 
	for (int i = 0; i < m_iLevel; i++)
		_tprintf(_T("+ "));

	_tprintf(_T("%s\n"), acName);

	return iRet;
}

A3DStatus MyTreeVisitor::visitLeave(const A3DProductOccurrenceConnector& sConnector)
{
	A3DStatus iRet = A3D_SUCCESS;

		// Decrement level
		m_iLevel--;

	iRet = A3DTreeVisitor::visitLeave(sConnector);
	return iRet;
}