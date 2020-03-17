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

class ShellExecutor : public QObject
{
	Q_OBJECT
public:
	ShellExecutor();
	virtual ~ShellExecutor();

	bool runCommand(const QString& szCommand, const QStringList& listArgs, const QDir& dirWorkingDirectory = QDir());

private slots:
	void readCommandAllStandardOutput();
	void readCommandAllStandardError();

private:
	void printCommandLines(const QString& szDomain, const QString& szMsg);
};

#endif /* SRC_SHELL_SHELLEXECUTOR_H_ */
