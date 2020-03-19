/*
 * FormulaParser.h
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_FORMULAS_FORMULAPARSER_H_
#define SRC_FORMULAS_FORMULAPARSER_H_

#include <QString>
#include <QSharedPointer>

class Formula;

class FormulaParser
{
public:
	FormulaParser();
	virtual ~FormulaParser();

	const QSharedPointer<Formula>& getFormula() const;

	bool parse(const QString& szFilePath);

private:
	QSharedPointer<Formula> m_pFormula;
};

#endif /* SRC_FORMULAS_FORMULAPARSER_H_ */
