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

bool AbstractPackageCommand::doRunCommand(const QString& szCmd, const QDir& dirWorkingDirectory)
{
	bool bRes;

	QString szCmdBind;
	bRes = doPrepareCommand(szCmd, szCmdBind);

	if(bRes){
		qDebug("[%s] %s", qPrintable(m_szLabel), qPrintable(szCmdBind));
		QStringList tokens = szCmdBind.split(' ');
		QString szCommand = tokens[0];

		// Rebuild cmd
		int i = 0;
		QStringList listArgs;
		QStringList::const_iterator iter;
		for(iter = tokens.constBegin(); iter != tokens.constEnd(); ++iter)
		{
			const QString& szArg = (*iter);
			if(i > 0 && !szArg.isEmpty()){
				listArgs.append(szArg);
			}
			i++;
		}

		if(!dirWorkingDirectory.exists()){
			qDebug("[%s] create directory: %s", qPrintable(m_szLabel), qPrintable(dirWorkingDirectory.path()));
			bRes = dirWorkingDirectory.mkpath(".");
		}
		bRes = m_shell.runCommand(tokens[0], listArgs, dirWorkingDirectory);
	}

	return bRes;
}

bool AbstractPackageCommand::doPrepareCommand(const QString& szCmd, QString& szCmdOut)
{
	szCmdOut = szCmd;

	QDir dirSrcPackage = getSourcePackageDir();
	szCmdOut = szCmdOut.replace("${PACKAGE_SRC_PATH}", dirSrcPackage.absolutePath());

	QDir dirReleasePackage = getReleasePackageDir();
	szCmdOut = szCmdOut.replace("${PACKAGE_PREFIX_PATH}", dirReleasePackage.absolutePath());

	szCmdOut = szCmdOut.replace("${CONFIGURE_OPTIONS}", QString());

	return true;
}
