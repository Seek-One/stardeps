/*
 * FormulaOptions.cpp
 *
 *  Created on: 11 juin 2020
 *      Author: ebeuque
 */

#include "FormulaOptions.h"

FormulaOptionRule::FormulaOptionRule()
{
	m_iState = StateAll;
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

void FormulaOption::setDependenciesList(const FormulaDependenciesList& listDependencies)
{
	m_listDependencies = listDependencies;
}

const FormulaDependenciesList& FormulaOption::getDependenciesList() const
{
	return m_listDependencies;
}

FormulaVariableList FormulaOption::getVariableListForState(bool bState) const
{
	FormulaVariableList listVars;

	FormulaOptionRuleList::const_iterator iter;

	qDebug("%s : %d", qPrintable(m_szOptionName), bState);

	for(iter = m_listRules.constBegin(); iter != m_listRules.constEnd(); ++iter)
	{
		const FormulaOptionRule& formulaOptionRule = (*iter);
		qDebug("  rule: %d", formulaOptionRule.getRuleState());
		if(formulaOptionRule.matchState(bState))
		{
			qDebug("match");
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
