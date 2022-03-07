/*
 * ShellExecutor.cpp
 *
 *  Created on: 17 mars 2020
 *      Author: ebeuque
 */

#include <QProcess>
#include <QEventLoop>
#include <Global/QApplicationSettings.h>

#include "ShellExecutor.h"

ShellExecutor::ShellExecutor()
{

}

ShellExecutor::~ShellExecutor()
{

}

void ShellExecutor::setEnvironmentVariableList(const VariableList& listVars)
{
    m_listEnvVars = listVars;
}

bool ShellExecutor::runCommand(const QString& szCommand, const QStringList& listArgs, const QDir& dirWorkingDirectory)
{
	return runCommand(szCommand, listArgs, QStringList(), dirWorkingDirectory);
}

bool ShellExecutor::runCommand(const QString& szCommand, const QStringList& listArgs, const QStringList& listCmdEnvVars, const QDir& dirWorkingDirectory)
{
    bool bRes = false;

    QProcess process;

    if (dirWorkingDirectory != QDir()) {
        process.setWorkingDirectory(dirWorkingDirectory.path());
    }

    // Setup env variable
    QProcessEnvironment processEnvironment = QProcessEnvironment::systemEnvironment();
    VariableList::const_iterator iter_var;
    for(iter_var = m_listEnvVars.constBegin(); iter_var != m_listEnvVars.constEnd(); ++iter_var){
        processEnvironment.insert(iter_var->getName(), iter_var->getName());
    }

	QStringList::const_iterator iter_cmd_var;
	for(iter_cmd_var = listCmdEnvVars.constBegin(); iter_cmd_var != listCmdEnvVars.constEnd(); ++iter_cmd_var){
		const QString& szTmp = (*iter_cmd_var);
		int iIdx = szTmp.indexOf("=");
		if(iIdx != -1){
			QString szVarName = szTmp.left(iIdx);
			QString szVarValue = szTmp.mid(iIdx+1);
			qDebug("[shell] Using command defined variable %s=%s", qPrintable(szVarName), qPrintable(szVarValue));
			processEnvironment.insert(szVarName, szVarValue);
		}
	}
    process.setProcessEnvironment(processEnvironment);

    QStringList listProcessEnv = processEnvironment.toStringList();
    QStringList::const_iterator iter;
    for(iter = listProcessEnv.constBegin(); iter != listProcessEnv.constEnd(); ++iter) {
        //qDebug("%s", qPrintable(*iter));
    }

    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readCommandAllStandardOutput()));
    connect(&process, SIGNAL(readyReadStandardError()), this, SLOT(readCommandAllStandardError()));
	connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));
	connect(&process, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(processErrorOccurred(QProcess::ProcessError)));

	printCommand(szCommand, listArgs);
	process.start(szCommand, listArgs);

	m_eventLoop.exec();

	if(process.exitCode() == 0){
		bRes = true;
	}

	return bRes;
}

void ShellExecutor::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	m_eventLoop.quit();
}

void ShellExecutor::processErrorOccurred(QProcess::ProcessError error)
{
	qDebug("[shell] Error to execute process: %d", error);
	m_eventLoop.quit();
}

void ShellExecutor::readCommandAllStandardOutput()
{
	QProcess* pProcess = (QProcess*)sender();
	QByteArray buf = pProcess->readAllStandardOutput();
    if (QApplicationSettings::applicationVerboseMode() == 1) {
        printCommandLines("stdout", QString::fromUtf8(buf));
    }
}

void ShellExecutor::readCommandAllStandardError()
{
	QProcess* pProcess = (QProcess*)sender();
	QByteArray buf = pProcess->readAllStandardError();
    if (QApplicationSettings::applicationVerboseMode() == 1) {
        printCommandLines("stderr", QString::fromUtf8(buf));
    }
}

void ShellExecutor::printCommand(const QString& szCommand, const QStringList& listArgs)
{
	if(listArgs.empty()){
		qDebug("[shell] %s", qPrintable(szCommand));
	}else{
		qDebug("[shell] %s %s", qPrintable(szCommand), qPrintable(listArgs.join(' ')));
	}
}

void ShellExecutor::printCommandLines(const QString& szDomain, const QString& szMsg)
{
	QStringList listLine = szMsg.split('\n');
	QStringList::const_iterator iter;
	for(iter = listLine.constBegin(); iter != listLine.constEnd(); ++iter)
	{
		qDebug("[%s] %s", qPrintable(szDomain), qPrintable((*iter)));
	}
}
