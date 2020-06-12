/*
 * CommandsExecutor.h
 *
 *  Created on: 11 juin 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_COMMANDSEXECUTOR_H_
#define SRC_COMMANDS_COMMANDSEXECUTOR_H_

#include <QString>
#include <QList>

#include "Commands/AbstractCommand.h"

class CommandsExecutor
{
public:
	CommandsExecutor();
	virtual ~CommandsExecutor();

	bool prepareCommands(const QString& szCommand, int argc, char** argv);

	bool executeCommands();

private:
	QList<AbstractCommand*> m_listCommands;

	AbstractCommandEnvironment* m_pCommandEnv;

	// For package commands
	QString m_szPackageName;
	QString m_szPackageVersion;
};

#endif /* SRC_COMMANDS_COMMANDSEXECUTOR_H_ */
