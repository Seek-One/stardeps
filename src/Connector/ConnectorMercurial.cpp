//
// Created by ebeuque on 11/12/2020.
//

#include "ConnectorMercurial.h"

ConnectorMercurial::ConnectorMercurial(const Environment& env) : AbstractConnector(env)
{

}

ConnectorMercurial::~ConnectorMercurial()
{

}

bool ConnectorMercurial::hg_clone(const QString& szURL, const QDir& dirWorkingDirectory)
{
	QStringList listArgs;
	qDebug("[mercurial] Getting sources: %s to %s", qPrintable(szURL), qPrintable(dirWorkingDirectory.path()));
	listArgs.append("clone");
	listArgs.append(szURL);
	listArgs.append(dirWorkingDirectory.path());
	return m_shell.runCommand(m_env.getHgExe(), listArgs);
}

bool ConnectorMercurial::hg_update(const QDir& dirWorkingDirectory)
{
	QStringList listArgs;
	qDebug("[mercurial] Updating sources: %s", qPrintable(dirWorkingDirectory.path()));
	listArgs.append("update");
	return m_shell.runCommand(m_env.getHgExe(), listArgs, dirWorkingDirectory);
}

bool ConnectorMercurial::hg_checkout(const QString& szVersion, const QDir& dirWorkingDirectory)
{
	QStringList listArgs;
	qDebug("[mercurial] Update sources to version %s", qPrintable(szVersion));
	listArgs.append("checkout");
	listArgs.append(szVersion);
	return m_shell.runCommand(m_env.getHgExe(), listArgs, dirWorkingDirectory);
}