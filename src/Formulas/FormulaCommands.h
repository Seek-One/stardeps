/*
 * FormulaCommands.h
 *
 *  Created on: 20 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_FORMULAS_FORMULACOMMANDS_H_
#define SRC_FORMULAS_FORMULACOMMANDS_H_

#include <QString>
#include <QList>

class FormulaCommands : public QList<QString>
{
public:
	FormulaCommands();
	virtual ~FormulaCommands();
};

#endif /* SRC_FORMULAS_FORMULACOMMANDS_H_ */
