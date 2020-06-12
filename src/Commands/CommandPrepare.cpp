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

bool CommandPrepare::doProcessArgument(int i, const QString& szArg)
{
	if(szArg.startsWith("--scm-branch-version=")){
		setScmBranchVersion(szArg.mid(21));
		return true;
	}
	if(szArg.startsWith("--scm-tag-version=")){
		setScmTagVersion(szArg.mid(18));
		return true;
	}
	return AbstractPackageCommand::doProcessArgument(i, szArg);
}

bool CommandPrepare::doExecute()
{
	bool bRes = true;

	QDir dirSrcPackage = getSourcePackageDir();

	const QSharedPointer<Formula>& pFormula = getFormula();

	// Get sources
	if(bRes){
		bRes = prepareSources(pFormula, dirSrcPackage);
	}

	// Configure the version
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
		ConnectorGit connector(getEnv());
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
		ConnectorGit connector(getEnv());
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
	return getPackageVersion();
}
