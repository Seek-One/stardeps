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

#include "AbstractCommand.h"

class CommandsExecutor
{
public:
	CommandsExecutor();
	virtual ~CommandsExecutor();

	bool prepareCommands(const QString& szCommand, int argc, char** argv);

	bool executeCommands();

private:
	QList<AbstractCommand*> m_listCommands;
};

#endif /* SRC_COMMANDS_COMMANDSEXECUTOR_H_ */
