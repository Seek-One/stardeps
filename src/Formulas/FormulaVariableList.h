/*
 * FormulaVariable.h
 *
 *  Created on: 11 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_FORMULAS_FORMULAVARIABLELIST_H_
#define SRC_FORMULAS_FORMULAVARIABLELIST_H_

#include <QString>
#include <QMap>

class FormulaVariableList : public QMap<QString, QString> {
public:
	FormulaVariableList();
	virtual ~FormulaVariableList();
};

#endif /* SRC_FORMULAS_FORMULAVARIABLELIST_H_ */
