/*
 * Environment.cpp
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#include "EnvironmentDefs.h"

#include "Environment.h"

Environment::Environment()
{
	m_iPlatformType = Platform::Unknown;
}

Environment::~Environment()
{

}

void Environment::setVirtualEnvironmentPath(const QDir& dir)
{
	m_dirVE = dir;
}

const QDir& Environment::getVirtualEnvironmentPath() const
{
	return m_dirVE;
}

bool Environment::isPerPackageMode() const
{
	return true;
}

QDir Environment::getVirtualEnvironmentSourceDir() const
{
	return m_dirVE.filePath("src");
}

QDir Environment::getVirtualEnvironmentBuildDir() const
{
	return m_dirVE.filePath("build");
}

QDir Environment::getVirtualEnvironmentReleaseDir() const
{
	return m_dirVE.filePath("release");
}

void Environment::setPlatformType(Platform::Type iPlatformType)
{
	m_iPlatformType = iPlatformType;
}

Platform::Type Environment::getPlatformType() const
{
	return m_iPlatformType;
}

QString Environment::getPlatformTypeName() const
{
	return Platform::toString(m_iPlatformType);
}

void Environment::setEnvVar(const QString& szName, const QString& szValue)
{
	m_listVars.addVariable(szName, szValue);
}

QString Environment::getEnvVar(const QString& szName, const QString& szDefaultValue) const
{
	return m_listVars.getValue(szName, szDefaultValue);
}

void Environment::removeEnvVar(const QString& szName)
{
	if(m_listVars.hasVariable(szName)){
		m_listVars.removeVariable(szName);
	}
}

const EnvironmentVars& Environment::getVars() const
{
	return m_listVars;
}

QString Environment::getGitExe() const
{
	return getEnvVar(VE_VAR_GIT, "git");
}

QString Environment::getHgExe() const
{
	return getEnvVar(VE_VAR_HG, "hg");
}

QString Environment::getSVNExe() const
{
    return getEnvVar(VE_VAR_SVN, "svn");
}

void Environment::print()
{
	qDebug("[env] virtual environement path is: %s", qPrintable(m_dirVE.path()));
	EnvironmentVars::const_iterator iter;
	for(iter = m_listVars.constBegin(); iter != m_listVars.constEnd(); ++iter)
	{
		qDebug("[env] %s=%s", qPrintable(iter->getName()), qPrintable(iter->getValue()));
	}
}
