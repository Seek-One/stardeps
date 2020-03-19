/*
 * AbstractCommand.cpp
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#include "Global/QApplicationSettings.h"

#include "Environment/EnvironmentLoader.h"
#include "Formulas/FormulaParser.h"

#include "AbstractCommand.h"

AbstractCommand::AbstractCommand(const QString& szLabel)
{
	m_szLabel = szLabel;
	m_bNeedEnvVars = true;
}

AbstractCommand::~AbstractCommand()
{

}

void AbstractCommand::setVirtualEnvironmentPath(const QDir& dir)
{
	m_env.setVirtualEnvironmentPath(dir);
}

const QDir& AbstractCommand::getVirtualEnvironmentPath() const
{
	return m_env.getVirtualEnvironmentPath();
}

bool AbstractCommand::doInitEnv()
{
	bool bRes = true;
	EnvironmentLoader envLoader;
	if(m_bNeedEnvVars){
		bRes = envLoader.loadEnvironmentVars(m_env);
		m_env.print();
	}
	return bRes;
}

bool AbstractCommand::execute()
{
	bool bRes;

	bRes = doInitEnv();
	if(bRes){
		bRes = doExecute();
	}

	return bRes;
}

bool AbstractCommand::loadFormula(const QString& szPackageName, QSharedPointer<Formula>& pFormula)
{
	bool bRes;

	QDir dir = QApplicationSettings::applicationFormulasPath().filePath(szPackageName);
	QString szFilePath = dir.filePath(QString("%0.json").arg(szPackageName));
	qDebug("[%s] Loading formula from file %s", qPrintable(m_szLabel), qPrintable(szFilePath));

	FormulaParser parser;
	bRes = parser.parse(szFilePath);
	if(bRes){
		pFormula = parser.getFormula();
	}

	return bRes;
}
