/*
 * FormulaOptions.cpp
 *
 *  Created on: 11 juin 2020
 *      Author: ebeuque
 */

#include "FormulaOptions.h"

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

void FormulaOption::setDefaultModes(const QStringList& listModes)
{
	m_listDefaultModes = listModes;
}

const QStringList& FormulaOption::getDefaultModes() const
{
	return m_listDefaultModes;
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

	// Check if a rule match with the requested mode
	for(iter = m_listRules.constBegin(); iter != m_listRules.constEnd(); ++iter)
	{
		const FormulaOptionRules& formulaOptionRule = (*iter);
		if(!listOptionModes.empty()){
			if (formulaOptionRule.matchModes(listOptionModes, false)) {
				return formulaOptionRule.getDependenciesSearchMode();
			}
		}
	}

	// Check if a rule match with the default modes
	for(iter = m_listRules.constBegin(); iter != m_listRules.constEnd(); ++iter)
	{
		const FormulaOptionRules &formulaOptionRule = (*iter);
		if(!m_listDefaultModes.isEmpty()){
			if (formulaOptionRule.matchModes(m_listDefaultModes, false)) {
				return formulaOptionRule.getDependenciesSearchMode();
			}
		}
	}

	return PackageSearchMode::Environment;
}

FormulaVariableList FormulaOption::getVariableListForState(bool bState, const QStringList& listModes) const
{
	FormulaVariableList listVars;
	FormulaOptionRuleList::const_iterator iter;

	QStringList listModesUsed = (listModes.isEmpty() ? m_listDefaultModes : listModes);

	for(iter = m_listRules.constBegin(); iter != m_listRules.constEnd(); ++iter)
	{
		const FormulaOptionRules& formulaOptionRule = (*iter);
		bool bAccept = formulaOptionRule.matchState(bState);
		bAccept = bAccept && formulaOptionRule.matchModes(listModesUsed);
		if(bAccept)
		{
			listVars.addVariableList(formulaOptionRule.getVariableList());
		}
	}

	return listVars;
}

void FormulaOption::addOptionRule(const FormulaOptionRules& formulaOptionRule)
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
