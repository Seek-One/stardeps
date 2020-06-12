/*
 * VariableList.cpp
 *
 *  Created on: 12 juin 2020
 *      Author: ebeuque
 */

#include "VariableList.h"

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
		qDebug("%s=%s", qPrintable(iter.key()), qPrintable(iter.value()));
	}
}
