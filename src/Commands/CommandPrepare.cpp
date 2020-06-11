/*
 * CommandPrepare.cpp
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#include "Version/VersionHelper.h"
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

	// Check dependencies
	if(bRes){
		bRes = checkDependencies(pFormula, dirSrcPackage);
	}

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

bool CommandPrepare::checkDependencies(const QSharedPointer<Formula>& pFormula, const QDir& dirWorkingCopy)
{
	bool bRes = true;

	qDebug("[prepare] checking dependencies");

	QString szVersion = getPackageNameVersion();
	const QStringList& listOptions = getOptions();
	FormulaDependenciesList listDependencies = pFormula->getDependenciesListForOptions(listOptions);

	QString szDepsVersion = listDependencies.getBestDependenciesVersion(szVersion);

	if(!szDepsVersion.isEmpty()){
		qDebug("[prepare] using dependencies rules for version '%s'", qPrintable(szDepsVersion));

		const FormulaDependencies& deps = listDependencies.value(szDepsVersion);

		const PackageDependencyList& depsList = deps.getList();
		PackageDependencyList::const_iterator iter;

		for(iter = depsList.constBegin(); iter != depsList.constEnd(); ++iter)
		{
			const PackageDependency& dependency = (*iter);
			qWarning("[prepare] checking dependency %s", qPrintable(dependency.toString()));

			QString szFoundVersion;
			bRes = checkDependencyPresent(dependency, szFoundVersion);
			if(bRes){
				qDebug("[prepare] required dependency is found %s", qPrintable(szFoundVersion));
			}else{
				qWarning("[prepare] required dependency is not found");
			}

			if(!bRes){
				break;
			}
		}

		return bRes;
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

bool CommandPrepare::checkDependencyPresent(const PackageDependency& dependency, QString& szOutVersion)
{
	bool bRes = false;

	QDir releaseDir = m_env.getVirtualEnvironmentReleaseDir();

	QStringList listFilters;
	listFilters << QString("%0*").arg(dependency.getPackage());
	QFileInfoList listFiles = releaseDir.entryInfoList(listFilters, QDir::Dirs, QDir::Name);

	QFileInfoList::const_iterator iter;
	for(iter = listFiles.constBegin(); iter != listFiles.constEnd(); ++iter)
	{
		const QFileInfo& fileInfo = (*iter);
		QString szVersion = fileInfo.fileName().remove(dependency.getPackage() + "-");
		if(VersionHelper::checkVersion(szVersion, dependency.getVersionMin(), dependency.getVersionMax())){
			bRes = true;
			szOutVersion = szVersion;
		}
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
