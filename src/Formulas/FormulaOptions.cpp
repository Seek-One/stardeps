/*
 * FormulaOptions.cpp
 *
 *  Created on: 11 juin 2020
 *      Author: ebeuque
 */

#include "FormulaOptions.h"

FormulaOption::FormulaOption()
{

}

FormulaOption::~FormulaOption()
{

}

void FormulaOption::setOptionName(const QString& szName)
{
	m_szOptionName = szName;
}

const QString& FormulaOption::getOptionName() const
{
	return m_szOptionName;
}

void FormulaOption::setDependenciesList(const FormulaDependenciesList& listDependencies)
{
	m_listDependencies = listDependencies;
}

const FormulaDependenciesList& FormulaOption::getDependenciesList() const
{
	return m_listDependencies;
}

void FormulaOption::addVariable(const QString& szVarName, const QString& szVarValue)
{
	m_listVars.insert(szVarName, szVarValue);
}

QString FormulaOption::getVariable(const QString& szVarName) const
{
	return m_listVars.value(szVarName, QString());
}

void FormulaOption::setVariableList(const FormulaVariableList& listVariables)
{
	m_listVars = listVariables;
}

const FormulaVariableList& FormulaOption::getVariableList() const
{
	return m_listVars;
}

FormulaOptionList::FormulaOptionList()
{

}

FormulaOptionList::~FormulaOptionList()
{

}

