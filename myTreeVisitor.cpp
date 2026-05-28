#include "MyTreeVisitor.h"

A3DStatus MyTreeVisitor::visitEnter(const A3DProductOccurrenceConnector& sConnector)
{
	A3DStatus iRet = A3DTreeVisitor::visitEnter(sConnector);

	// My processes

	return iRet;
}

A3DStatus MyTreeVisitor::visitLeave(const A3DProductOccurrenceConnector& sConnector)
{
	A3DStatus iRet = A3D_SUCCESS;

	// My processes

	iRet = A3DTreeVisitor::visitLeave(sConnector);
	return iRet;
}