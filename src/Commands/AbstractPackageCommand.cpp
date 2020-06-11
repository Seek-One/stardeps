/*
 * AbstractPackageCommand.cpp
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#include "Environment/EnvironmentDefs.h"

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

void AbstractPackageCommand::addOption(const QString& szOption)
{
	m_listOptions.append(szOption);
}

const QStringList& AbstractPackageCommand::getOptions() const
{
	return m_listOptions;
}

QString AbstractPackageCommand::getPackageNameVersion() const
{
	QString szVersionName = m_szPackageName;
	if(!m_szVersion.isEmpty()){
		szVersionName += "-" + m_szVersion;
	}
	return szVersionName;
}

QDir AbstractPackageCommand::getRootPackageDir() const
{
	return m_env.getVirtualEnvironmentPath().filePath(getPackageNameVersion());
}

QDir AbstractPackageCommand::getSourcePackageDir() const
{
	if(m_env.isPerPackageMode()){
		return getRootPackageDir().filePath("src");
	}else{
		return m_env.getVirtualEnvironmentSourceDir().filePath(getPackageNameVersion());
	}
}

QDir AbstractPackageCommand::getBuildPackageDir() const
{
	if(m_env.isPerPackageMode()){
		return getRootPackageDir().filePath("build");
	}else{
		return m_env.getVirtualEnvironmentBuildDir().filePath(getPackageNameVersion());
	}
}

QDir AbstractPackageCommand::getReleasePackageDir() const
{
	if(m_env.isPerPackageMode()){
		return getRootPackageDir().filePath("release");
	}else{
		return m_env.getVirtualEnvironmentReleaseDir().filePath(getPackageNameVersion());
	}
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

	QMap<QString, QString> dictVars;

	// Tools
	dictVars.insert("${TOOL::GIT}", m_env.getEnvVar(VE_VAR_GIT));
	dictVars.insert("${TOOL::MAKE}", m_env.getEnvVar(VE_VAR_MAKE));
	dictVars.insert("${TOOL::RSYNC}", m_env.getEnvVar(VE_VAR_RSYNC));
	dictVars.insert("${TOOL::COMPILER}", m_env.getEnvVar(VE_VAR_COMPILER));

	// Package infos
	dictVars.insert("${PACKAGE_VERSION}", getPackageNameVersion());
	dictVars.insert("${PACKAGE_SRC_PATH}", getSourcePackageDir().absolutePath());
	dictVars.insert("${PACKAGE_BUILD_PATH}", getBuildPackageDir().absolutePath());
	dictVars.insert("${PACKAGE_PREFIX_PATH}", getReleasePackageDir().absolutePath());

	// Configure
	dictVars.insert("${CONFIGURE_OPTIONS}", QString());

	QMap<QString, QString>::const_iterator iter;
	for(iter = dictVars.constBegin(); iter != dictVars.constEnd(); ++iter)
	{
		szCmdOut = szCmdOut.replace(iter.key(), iter.value());
	}

	return true;
}

bool AbstractPackageCommand::doProcessArgument(int i, const QString& szArg)
{
	if(i == 0){
		setPackageName(szArg);
		return true;
	}

	if(szArg.startsWith("--version=")){
		setVersion(szArg.mid(10));
		return true;
	}

	if(szArg.startsWith("--option=")){
		addOption(szArg.mid(9));
		return true;
	}

	return AbstractCommand::doProcessArgument(i, szArg);
}
