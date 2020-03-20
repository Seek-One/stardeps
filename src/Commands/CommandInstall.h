/*
 * CommandInstall.h
 *
 *  Created on: 11 mars 2020
 *      Author: ebeuque
 */

#ifndef SRC_COMMANDS_COMMANDINSTALL_H_
#define SRC_COMMANDS_COMMANDINSTALL_H_

#include "AbstractPackageCommand.h"

class CommandInstall : public AbstractPackageCommand {
public:
	CommandInstall();
	virtual ~CommandInstall();

protected:
	bool doExecute();
};

#endif /* SRC_COMMANDS_COMMANDINSTALL_H_ */
