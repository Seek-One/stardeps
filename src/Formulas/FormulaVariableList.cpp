/*
 * FormulaVariable.cpp
 *
 *  Created on: 11 juin 2020
 *      Author: ebeuque
 */

#include "FormulaVariableList.h"

FormulaVariableList::FormulaVariableList()
{

}

FormulaVariableList::~FormulaVariableList()
{

}

void FormulaVariableList::addVariableList(const FormulaVariableList& listVars)
{
	FormulaVariableList::const_iterator iter;
	for(iter = listVars.constBegin(); iter != listVars.constEnd(); ++iter)
	{
		insert(iter.key(), iter.value());
	}
}