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

void CommandPrepare::setVersion(const QString& szVersion)
{
	m_szVersion = szVersion;
}

void CommandPrepare::setScmBranchVersion(const QString& szVersion)
{
	m_szScmBranchVersion = szVersion;
}

void CommandPrepare::setScmTagVersion(const QString& szVersion)
{
	m_szScmBranchVersion = szVersion;
}

bool CommandPrepare::doExecute()
{
	bool bRes = true;

	QDir dir = QApplicationSettings::applicationFormulasPath().filePath(m_szPackageName);
	QString szFilePath = dir.filePath(QString("%0.json").arg(m_szPackageName));

	qDebug("[prepare] Loading formula from file %s", qPrintable(szFilePath));

	QSharedPointer<Formula> pFormula;

	QString szDirName = m_szPackageName;
	if(!m_szVersion.isEmpty()){
		szDirName += "-" + m_szVersion;
	}
	QDir dirSrcDstPath = getVirtualEnvironmentPath().path() + "/src/" + szDirName;

	// Load formula
	FormulaParser parser;
	bRes = parser.parse(szFilePath);
	if(bRes){
		pFormula = parser.getFormula();
	}

	// Get sources
	if(bRes){
		bRes = prepareSources(pFormula, dirSrcDstPath);
	}

	if(bRes && !getConfigureVersion().isEmpty()){
		bRes = configureVersion(pFormula, dirSrcDstPath);
	}

	return bRes;
}

bool CommandPrepare::prepareSources(const QSharedPointer<Formula>& pFormula, const QDir& dirWorkingCopy)
{
	bool bRes = true;

	if(pFormula->getTypeSCM() == Formula::SCM_Git)
	{
		ConnectorGit connector(m_env);
		if(dirWorkingCopy.exists()){
			bRes = connector.git_checkout("master", dirWorkingCopy);
			bRes = connector.git_pull(dirWorkingCopy);
		}else{
			bRes = connector.git_clone(pFormula->getSCMURL(), dirWorkingCopy);
		}
	}

	return bRes;
}

bool CommandPrepare::configureVersion(const QSharedPointer<Formula>& pFormula, const QDir& dirWorkingCopy)
{
	bool bRes = true;

	if(pFormula->getTypeSCM() == Formula::SCM_Git)
	{
		ConnectorGit connector(m_env);
		bRes = connector.git_checkout(getConfigureVersion(), dirWorkingCopy);
	}

	return bRes;
}

const QString& CommandPrepare::getConfigureVersion() const
{
	if(!m_szScmTagVersion.isEmpty()){
		return m_szScmTagVersion;
	}
	if(!m_szScmBranchVersion.isEmpty()){
		return m_szScmBranchVersion;
	}
	return m_szVersion;
}
