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
	m_listVars.insert(szName, szValue);
}


QString Environment::getEnvVar(const QString& szName, const QString& szDefaultValue) const
{
	return m_listVars.value(szName, szDefaultValue);
}

const EnvironmentVars& Environment::getVars() const
{
	return m_listVars;
}

QString Environment::getGitExe() const
{
	return getEnvVar(VE_VAR_GIT, "git");
}

void Environment::print()
{
	qDebug("[env] virtual environement path is: %s", qPrintable(m_dirVE.path()));
	EnvironmentVars::const_iterator iter;
	for(iter = m_listVars.constBegin(); iter != m_listVars.constEnd(); ++iter)
	{
		qDebug("[env] %s=%s", qPrintable(iter.key()), qPrintable(iter.value()));
	}
}