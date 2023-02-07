/*
 * FormulaOptions.cpp
 *
 *  Created on: 11 juin 2020
 *      Author: ebeuque
 */

#include "Package/PackageSearchMode.h"

#include "FormulaOptions.h"

FormulaOptionRule::FormulaOptionRule()
{
	m_iState = StateAll;
	m_iDependenciesSearchMode = PackageSearchMode::Environment;
}

FormulaOptionRule::~FormulaOptionRule()
{

}

void FormulaOptionRule::setRuleState(State iState)
{
	m_iState = iState;
}

FormulaOptionRule::State FormulaOptionRule::getRuleState() const
{
	return m_iState;
}

void FormulaOptionRule::setRuleMode(const QString& szMode)
{
	m_szMode = szMode;
}

const QString& FormulaOptionRule::getRuleMode() const
{
	return m_szMode;
}

void FormulaOptionRule::setDependenciesSearchMode(const PackageSearchMode& iDependenciesSearchMode)
{
	 m_iDependenciesSearchMode = iDependenciesSearchMode;
}

const PackageSearchMode& FormulaOptionRule::getDependenciesSearchMode() const
{
	return m_iDependenciesSearchMode;
}

void FormulaOptionRule::setVariableList(const FormulaVariableList& listVariables)
{
	m_listVars = listVariables;
}

const FormulaVariableList& FormulaOptionRule::getVariableList() const
{
	return m_listVars;
}

bool FormulaOptionRule::matchState(bool bState) const
{
	if(m_iState == StateEnabled){
		return bState;
	}
	if(m_iState == StateDisabled){
		return !bState;
	}
	return true;
}


bool FormulaOptionRule::matchModes(const QStringList& listModes, bool bAcceptNoMode) const
{
	if(m_szMode.isEmpty()){
		return bAcceptNoMode;
	}
	return listModes.contains(m_szMode);
}

FormulaOption::FormulaOption()
{
	m_bDefaultState = false;
}

FormulaOption::~FormulaOption()
{

}

bool FormulaOption::isNull() const
{
	return m_szOptionName.isEmpty();
}

void FormulaOption::setOptionName(const QString& szName)
{
	m_szOptionName = szName;
}

const QString& FormulaOption::getOptionName() const
{
	return m_szOptionName;
}

void FormulaOption::setDefaultState(bool bDefaultState)
{
	m_bDefaultState = bDefaultState;
}

bool FormulaOption::getDefaultState() const
{
	return m_bDefaultState;
}

void FormulaOption::setDefaultModes(const QString& szModes)
{
	m_szDefaultModes = szModes;
}

const QString& FormulaOption::getDefaultModes() const
{
	return m_szDefaultModes;
}

void FormulaOption::setDependenciesList(const FormulaDependenciesList& listDependencies)
{
	m_listDependencies = listDependencies;
}

const FormulaDependenciesList& FormulaOption::getDependenciesList() const
{
	return m_listDependencies;
}

PackageSearchMode FormulaOption::getDependenciesSearchMode(const QStringList& listOptionModes) const
{
	FormulaVariableList listVars;

	FormulaOptionRuleList::const_iterator iter;

	for(iter = m_listRules.constBegin(); iter != m_listRules.constEnd(); ++iter)
	{
		const FormulaOptionRule& formulaOptionRule = (*iter);
		if(formulaOptionRule.matchModes(listOptionModes, false)){
			return formulaOptionRule.getDependenciesSearchMode();
		}
	}

	return PackageSearchMode::Environment;
}

FormulaVariableList FormulaOption::getVariableListForState(bool bState, const QStringList& listModes) const
{
	FormulaVariableList listVars;

	FormulaOptionRuleList::const_iterator iter;

	for(iter = m_listRules.constBegin(); iter != m_listRules.constEnd(); ++iter)
	{
		const FormulaOptionRule& formulaOptionRule = (*iter);
		bool bAccept = formulaOptionRule.matchState(bState);
		bAccept = bAccept && formulaOptionRule.matchModes(listModes);
		if(bAccept)
		{
			listVars.addVariableList(formulaOptionRule.getVariableList());
		}
	}

	return listVars;
}

void FormulaOption::addOptionRule(const FormulaOptionRule& formulaOptionRule)
{
	m_listRules.append(formulaOptionRule);
}

const FormulaOptionRuleList& FormulaOption::getOptionRuleList() const
{
	return m_listRules;
}

FormulaOptionList::FormulaOptionList()
{

}

FormulaOptionList::~FormulaOptionList()
{

}

const FormulaOption& FormulaOptionList::getOptionByName(const QString& szOptionName, const FormulaOption& defaultOption) const
{
	FormulaOptionList::const_iterator iter;
	for(iter = constBegin(); iter != constEnd(); ++iter)
	{
		if((*iter).getOptionName() == szOptionName){
			return (*iter);
		}
	}
	return defaultOption;
}
