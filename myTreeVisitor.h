#pragma once
#include "visitor/VisitorTree.h"
class myTreeVisitor :
    public A3DTreeVisitor
{
public:
	myTreeVisitor(A3DVisitorContainer* psContainer = NULL) : A3DTreeVisitor(psContainer) {};
	~myTreeVisitor() {};

	virtual A3DStatus visitEnter(const A3DProductOccurrenceConnector& sConnector) override;
	virtual A3DStatus visitLeave(const A3DProductOccurrenceConnector& sConnector) override;

};

