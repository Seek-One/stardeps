/*
 * ConnectorGit.cpp
 *
 *  Created on: 17 mars 2020
 *      Author: ebeuque
 */

#include "ConnectorGit.h"

ConnectorGit::ConnectorGit()
{

}

ConnectorGit::~ConnectorGit()
{

}

bool ConnectorGit::git_clone(const QString& szURL, const QDir& dirWorkingDirectory)
{
	QStringList listArgs;
	qDebug("[git] Getting sources: %s to %s", qPrintable(szURL), qPrintable(dirWorkingDirectory.path()));
	listArgs.append("clone");
	listArgs.append(szURL);
	listArgs.append(dirWorkingDirectory.path());
	return m_shell.runCommand("git", listArgs);
}

bool ConnectorGit::git_pull(const QDir& dirWorkingDirectory)
{
	QStringList listArgs;
	qDebug("[git] Updating sources: %s", qPrintable(dirWorkingDirectory.path()));
	listArgs.append("pull");
	return m_shell.runCommand("git", listArgs, dirWorkingDirectory);
}

bool ConnectorGit::git_checkout(const QString& szVersion, const QDir& dirWorkingDirectory)
{
	QStringList listArgs;
	qDebug("[git] Checkout sources to version %s", qPrintable(szVersion));
	listArgs.append("checkout");
	listArgs.append(szVersion);
	return m_shell.runCommand("git", listArgs, dirWorkingDirectory);
}
