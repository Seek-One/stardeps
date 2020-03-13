/*
 * CommandPrepare.cpp
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#include "Global/QApplicationSettings.h"

#include "Formulas/Formula.h"
#include "Formulas/FormulaParser.h"

#include "CommandPrepare.h"

CommandPrepare::CommandPrepare()
{

}

CommandPrepare::~CommandPrepare()
{

}

bool CommandPrepare::execute(const QString& szVEPath, const QString& szPackage)
{
	bool bRes = true;

	QDir dir = QApplicationSettings::applicationFormulasPath().filePath(szPackage);
	QString szFilePath = dir.filePath(QString("%0.json").arg(szPackage));

	qDebug("[prepare] Loading formula from file %s", qPrintable(szFilePath));

	QSharedPointer<Formula> pFormula;

	// Load formula
	FormulaParser parser;
	bRes = parser.parse(szFilePath);
	if(bRes){
		pFormula = parser.getFormula();
	}

	if(bRes){
		qDebug("formula name: %s", qPrintable(pFormula->getName()));
	}

	return bRes;
}
