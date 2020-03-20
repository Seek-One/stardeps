/*
 * AbstractPackageCommand.cpp
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#include "AbstractPackageCommand.h"

AbstractPackageCommand::AbstractPackageCommand(const QString& szLabel) : AbstractCommand(szLabel)
{

}

AbstractPackageCommand::~AbstractPackageCommand()
{

}

void AbstractPackageCommand::setPackageName(const QString& szPackageName)
{
	m_szPackageName = szPackageName;
}

void AbstractPackageCommand::setVersion(const QString& szVersion)
{
	m_szVersion = szVersion;
}

QDir AbstractPackageCommand::getSourcePackageDir() const
{
	QString szDirName = m_szPackageName;
	if(!m_szVersion.isEmpty()){
		szDirName += "-" + m_szVersion;
	}
	return m_env.getVirtualEnvironmentSourceDir().filePath(szDirName);
}

QDir AbstractPackageCommand::getBuildPackageDir() const
{
	QString szDirName = m_szPackageName;
	if(!m_szVersion.isEmpty()){
		szDirName += "-" + m_szVersion;
	}
	return m_env.getVirtualEnvironmentBuildDir().filePath(szDirName);
}

QDir AbstractPackageCommand::getReleasePackageDir() const
{
	QString szDirName = m_szPackageName;
	if(!m_szVersion.isEmpty()){
		szDirName += "-" + m_szVersion;
	}
	return m_env.getVirtualEnvironmentReleaseDir().filePath(szDirName);
}
