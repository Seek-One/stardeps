/*
 * AbstractCommand.h
 *
 *  Created on: 13 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_ABSTRACTCOMMAND_H_
#define SRC_COMMANDS_ABSTRACTCOMMAND_H_

#include <QObject>
#include <QDir>

class AbstractCommand : public QObject
{
	Q_OBJECT
public:
	AbstractCommand();
	virtual ~AbstractCommand();

	void setVirtualEnvironmentPath(const QString& szPath);

	bool runCommand(const QString& szCommand, const QStringList& listArgs, const QDir& dirWorkingDirectory = QDir());

private slots:
	void readCommandAllStandardOutput();
	void readCommandAllStandardError();

private:
	void printCommandLines(const QString& szDomain, const QString& szMsg);

protected:
	QString m_szVEPath;
};

#endif /* SRC_COMMANDS_ABSTRACTCOMMAND_H_ */
