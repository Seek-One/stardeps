/*
 * CommandPrepare.cpp
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#include <QProcess>

#include "Global/QApplicationSettings.h"

#include "Connector/ConnectorGit.h"

#include "Formulas/Formula.h"
#include "Formulas/FormulaParser.h"

#include "CommandPrepare.h"

CommandPrepare::CommandPrepare()
{

}

CommandPrepare::~CommandPrepare()
{

}

void CommandPrepare::setPackageName(const QString& szPackageName)
{
	m_szPackageName = szPackageName;
}

bool CommandPrepare::execute()
{
	bool bRes = true;

	QDir dir = QApplicationSettings::applicationFormulasPath().filePath(m_szPackageName);
	QString szFilePath = dir.filePath(QString("%0.json").arg(m_szPackageName));

	qDebug("[prepare] Loading formula from file %s", qPrintable(szFilePath));

	QSharedPointer<Formula> pFormula;

	// Load formula
	FormulaParser parser;
	bRes = parser.parse(szFilePath);
	if(bRes){
		pFormula = parser.getFormula();
	}

	// Get sources
	if(bRes){
		bRes = prepareSources(pFormula);
	}

	return bRes;
}

bool CommandPrepare::prepareSources(const QSharedPointer<Formula>& pFormula)
{
	bool bRes = true;

	QDir dirSrcDstPath = m_szVEPath + "/src/" + m_szPackageName;

	if(pFormula->getTypeSCM() == Formula::SCM_Git)
	{
		ConnectorGit connector;
		if(dirSrcDstPath.exists()){
			bRes = connector.git_pull(dirSrcDstPath);
		}else{
			bRes = connector.git_clone(pFormula->getSCMURL(), dirSrcDstPath);
		}
	}

	return bRes;
}
