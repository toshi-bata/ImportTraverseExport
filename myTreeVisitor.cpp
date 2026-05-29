#include "MyTreeVisitor.h"
#include "visitor/VisitorTree.h"
#include "visitor/VisitorCascadedAttribute.h"
#include "visitor/CascadedAttributeConnector.h"
#include "visitor/VisitorTransfo.h"
#include "visitor/TransfoConnector.h"
#include <memory>

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
	CHECK_RET(A3DRootBaseGet(pPO, &sRootBaseData));

	// Get the PO name  
	A3DUniChar acName[256];
	if (sRootBaseData.m_pcName)
		A3DMiscUTF8ToUTF16(sRootBaseData.m_pcName, acName);
	else
		wcscpy_s(acName, _T("NO_NAME"));

	// Show the PO name with level 
	for (int i = 0; i < m_iLevel; i++)
		_tprintf(_T("+ "));

	_tprintf(_T("%s"), acName);

	A3DRootBaseGet(nullptr, &sRootBaseData);

	A3DVisitorColorMaterials* pA3DCascadedVisitor = static_cast<A3DVisitorColorMaterials*>(m_psContainer->GetVisitorByName("CascadedAttribute"));
	if (pA3DCascadedVisitor)
	{
		ColorMaterialsConnector sColorConnector(nullptr);
		pA3DCascadedVisitor->GetColorMaterialConnector(sColorConnector);

		if (sColorConnector.IsShow())
			_tprintf(_T("\n"));
		else
			_tprintf(_T(" (Hidden)\n"));
	}

	return iRet;
}

A3DStatus MyTreeVisitor::visitEnter(const A3DPartConnector& sConnector)
{
	A3DStatus iRet = A3DTreeVisitor::visitEnter(sConnector);

	// Get transform connector via transform visitor
	A3DVisitorTransfo* psVisitorTransfo = static_cast<A3DVisitorTransfo*>(m_psContainer->GetVisitorByName("Transformation"));
	if (psVisitorTransfo)
	{
		std::unique_ptr<A3DTransfoConnector> pConnector(psVisitorTransfo->GetTransfoConnector());
		A3DMatrix4x4 sTransfo;
		pConnector->GetGlobalTransfo(sTransfo);

		for (unsigned int i = 0; i < m_iLevel; i++)
			_tprintf(_T("+ "));

		_tprintf(_T(" (%.3f, %.3f, %.3f)\n"), sTransfo.m_adM[12], sTransfo.m_adM[13], sTransfo.m_adM[14]);
	}

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