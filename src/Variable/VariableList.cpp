/*
 * VariableList.cpp
 *
 *  Created on: 12 juin 2020
 *      Author: ebeuque
 */

#include "VariableList.h"

Variable::Variable()
{

}

Variable::Variable(const QString& szName, const QString& szValue)
{
	m_szName = szName;
	m_szValue = szValue;
}

Variable::~Variable()
{

}

const QString& Variable::getName() const
{
	return m_szName;
}

const QString& Variable::getValue() const
{
	return m_szValue;
}

VariableList::VariableList()
{

}

VariableList::~VariableList()
{

}

void VariableList::print() const
{
	const_iterator iter;

	for(iter = constBegin(); iter != constEnd(); ++iter){
		qDebug("%s=%s", qPrintable(iter->getName()), qPrintable(iter->getValue()));
	}
}

void VariableList::addVariable(const QString& szKey, const QString& szValue)
{
	qDebug("%s=%s", qPrintable(szKey), qPrintable(szValue));
	append(Variable(szKey, szValue));
}

void VariableList::addVariableList(const VariableList& listVars)
{
	VariableList::const_iterator iter;
	for(iter = listVars.constBegin(); iter != listVars.constEnd(); ++iter)
	{
		append(*iter);
	}
}

const QString& VariableList::getValue(const QString& szName, const QString& szDefaultValue) const
{
	VariableList::const_iterator iter;
	for(iter = constBegin(); iter != constEnd(); ++iter)
	{
		if(iter->getName() == szName){
			return iter->getValue();
		}
	}
	return szDefaultValue;
}