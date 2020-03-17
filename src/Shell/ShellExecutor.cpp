/*
 * ShellExecutor.cpp
 *
 *  Created on: 17 mars 2020
 *      Author: ebeuque
 */

#include <QProcess>
#include <QEventLoop>

#include "ShellExecutor.h"

ShellExecutor::ShellExecutor()
{

}

ShellExecutor::~ShellExecutor()
{

}

bool ShellExecutor::runCommand(const QString& szCommand, const QStringList& listArgs, const QDir& dirWorkingDirectory)
{
	bool bRes = false;

	QEventLoop eventLoop;

	QProcess process;

	if(dirWorkingDirectory != QDir()){
		process.setWorkingDirectory(dirWorkingDirectory.path());
	}

	connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readCommandAllStandardOutput()));
	connect(&process, SIGNAL(readyReadStandardError()), this, SLOT(readCommandAllStandardError()));
	connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), &eventLoop, SLOT(quit()));

	process.start(szCommand, listArgs);

	eventLoop.exec();

	if(process.exitCode() == 0){
		bRes = true;
	}

	return bRes;
}

void ShellExecutor::readCommandAllStandardOutput()
{
	QProcess* pProcess = (QProcess*)sender();
	QByteArray buf = pProcess->readAllStandardOutput();
	printCommandLines("stdout", QString::fromUtf8(buf));
}

void ShellExecutor::readCommandAllStandardError()
{
	QProcess* pProcess = (QProcess*)sender();
	QByteArray buf = pProcess->readAllStandardError();
	printCommandLines("stderr", QString::fromUtf8(buf));
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
