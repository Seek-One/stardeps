/*
 * CommandConfigure.h
 *
 *  Created on: 18 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_COMMANDCONFIGURE_H_
#define SRC_COMMANDS_COMMANDCONFIGURE_H_

#include "AbstractPackageCommand.h"

class CommandConfigure : public AbstractPackageCommand {
public:
	CommandConfigure();
	virtual ~CommandConfigure();

protected:
	bool doExecute();

private:
	bool runCommand(const QString& szCmd);

	bool doPrepareCommand(const QString& szCmd, QString& szCmdOut);
};

#endif /* SRC_COMMANDS_COMMANDCONFIGURE_H_ */
