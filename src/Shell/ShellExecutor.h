/*
 * ShellExecutor.h
 *
 *  Created on: 17 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_SHELL_SHELLEXECUTOR_H_
#define SRC_SHELL_SHELLEXECUTOR_H_

#include <QObject>
#include <QDir>
#include <QEventLoop>
#include <QProcess>

#include "Variable/VariableList.h"

class ShellExecutor : public QObject
{
	Q_OBJECT
public:
	ShellExecutor();
	virtual ~ShellExecutor();

	void setEnvironmentVariableList(const VariableList& listVars);

	bool runCommand(const QString& szCommand, const QStringList& listArgs, const QDir& dirWorkingDirectory = QDir());
	bool runCommand(const QString& szCommand, const QStringList& listArgs, const QStringList& listCmdEnvVars, const QDir& dirWorkingDirectory = QDir());

private slots:
	void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
	void processErrorOccurred(QProcess::ProcessError error);
	void readCommandAllStandardOutput();
	void readCommandAllStandardError();

private:
	void printCommand(const QString& szCommand, const QStringList& listArgs);
	void printCommandLines(const QString& szDomain, const QString& szMsg);

	QEventLoop m_eventLoop;
	VariableList m_listEnvVars;
};

#endif /* SRC_SHELL_SHELLEXECUTOR_H_ */
