/*
 * CommandPrepare.cpp
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#include "Connector/ConnectorGit.h"

#include "CommandPrepare.h"

CommandPrepare::CommandPrepare() : AbstractPackageCommand("prepare")
{

}

CommandPrepare::~CommandPrepare()
{

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

	QDir dirSrcPackage = getSourcePackageDir();

	// Load formula
	QSharedPointer<Formula> pFormula;
	bRes = loadFormula(m_szPackageName, pFormula);

	// Get sources
	if(bRes){
		bRes = prepareSources(pFormula, dirSrcPackage);
	}

	if(bRes && !getConfigureVersion().isEmpty()){
		bRes = configureVersion(pFormula, dirSrcPackage);
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
