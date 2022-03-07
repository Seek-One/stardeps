/*
 * FormulaVariable.h
 *
 *  Created on: 11 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_FORMULAS_FORMULAVARIABLELIST_H_
#define SRC_FORMULAS_FORMULAVARIABLELIST_H_

#include <QString>
#include <QList>

#include "Variable/VariableList.h"

class FormulaVariableList : public VariableList {
public:
	FormulaVariableList();
	virtual ~FormulaVariableList();
};

#endif /* SRC_FORMULAS_FORMULAVARIABLELIST_H_ */
