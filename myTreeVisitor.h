#pragma once
#include "visitor/VisitorTree.h"
class MyTreeVisitor :
    public A3DTreeVisitor
{
public:
	MyTreeVisitor(A3DVisitorContainer* psContainer = nullptr) : A3DTreeVisitor(psContainer) {};
	~MyTreeVisitor() = default;

	virtual A3DStatus visitEnter(const A3DProductOccurrenceConnector& sConnector) override;
	virtual A3DStatus visitEnter(const A3DPartConnector& sConnector) override;
	virtual A3DStatus visitLeave(const A3DProductOccurrenceConnector& sConnector) override;

private:
	int m_iLevel = 0;

};

