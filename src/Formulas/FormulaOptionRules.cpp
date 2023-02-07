//
// Created by ebeuque on 07/02/23.
//

#include "FormulaOptionRules.h"

FormulaOptionRules::FormulaOptionRules()
{
	m_iState = StateAll;
	m_iDependenciesSearchMode = PackageSearchMode::Environment;
}

FormulaOptionRules::~FormulaOptionRules()
{

}

void FormulaOptionRules::setRuleState(State iState)
{
	m_iState = iState;
}

FormulaOptionRules::State FormulaOptionRules::getRuleState() const
{
	return m_iState;
}

void FormulaOptionRules::setRuleMode(const QString& szMode)
{
	m_szMode = szMode;
}

const QString& FormulaOptionRules::getRuleMode() const
{
	return m_szMode;
}

void FormulaOptionRules::setDependenciesSearchMode(const PackageSearchMode& iDependenciesSearchMode)
{
	m_iDependenciesSearchMode = iDependenciesSearchMode;
}

const PackageSearchMode& FormulaOptionRules::getDependenciesSearchMode() const
{
	return m_iDependenciesSearchMode;
}

void FormulaOptionRules::setVariableList(const FormulaVariableList& listVariables)
{
	m_listVars = listVariables;
}

const FormulaVariableList& FormulaOptionRules::getVariableList() const
{
	return m_listVars;
}

bool FormulaOptionRules::matchState(bool bState) const
{
	if(m_iState == StateEnabled){
		return bState;
	}
	if(m_iState == StateDisabled){
		return !bState;
	}
	return true;
}


bool FormulaOptionRules::matchModes(const QStringList& listModes, bool bAcceptNoMode) const
{
	if(m_szMode.isEmpty()){
		return bAcceptNoMode;
	}
	return listModes.contains(m_szMode);
}